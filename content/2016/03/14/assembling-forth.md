Assembling Forth
================

The past week, I've been playing around with building a [https://github.com/cthulhuology/forth|64 bit forth] 
for the x86_64 processor.  While I'm not planning on using this experiement for production any time
soon, it has been a lot of fun writing a forth to implement some of the ideas I've had over the
years.

Initial Inspiration
-------------------

The initial inspiration for doing it came out of the [http://github.com/cthulhuology/sdlforth|SDL Forth]
project.  I found myself writing code just about every day that used the inline assembler of
SwiftForth.  For example:

<pre>
	ICODE ~!- ( n add -- a-4 )
	0 [EBP] EAX MOV
	EAX 0 [EBX] MOV
	4 # EBP ADD
	4 # EBX SUB
	RET END-CODE
</pre>

defines a store-and-decrement operation that can be used to copy data from a stack
into a data structure *backwards*.  The usage of this operation allows one to write
values in reverse order without having to juggle the stack at all.

<pre>
	x y w h rect sdl_rect:h ~!- ~!- ~!- ~!- drop
</pre>

This code calculates the last field in the C structure, and then fills them in
reverse order, leaving the next lower address on the top of the stack each time.
Looking at this code, I was thinking of what a shame it was I couldn't do something
like it using the *STOSD* instruction, using *edi* as the destination index, and
using the *direction flag* to copy down rather than copy up. 

In [http://colorforth.com|Chuck Moore's colorforth] he used *lodsd* to pop the 
value off the data stack into eax, and you can then use *stosd* to write it to 
memory. The only issue here is the DF affects both operations, and so one would 
need to rewrite their stack routines to go in the other direction. This made me think
about how much effort it would take to rewrite the whole thing.

Copy Compiler
-------------

Years ago, I wrote a Forth in C that copied instructions out of a block of code using
labels.  As long as the code was written using -fPIC it was a workable solution.  The
idea here is one could use the C complier to generate the body of routines, and then
just copy and paste from within labels.  In the end, having to manually specify 
register allocations and juggle the registers when calling C code, made it not worth
the effort.

Also some years ago, I wrote a prototype of a compiler in Perl that took Forth words
and generated machine code using *pack* to assemble individual sets of opcodes.  
This worked really well to a point that I had an assembler working in a matter of
days.  The downside was that I hadn't worked trough the memory model, and addresses
were stored in a Perl hash which served as a compile time dictionary.  The result
was I could compile Forth-ish code, but none of the symbols were available at runtime.
Making it bootstrapable turned into more work than it was worth.

Once again, I thought about the copy-compiler idea.  The concept behind the copy 
compiler is dirt simple.  Machine code is stored in a table, and the assembler just
copies instructions out of it.  To construct the table in Forth I created a word *opc*:

<pre>
	: opc	parse-word number dup ,
		dup >r		
		0 do parse-word number c, loop
		12 r> - 0 do 0 c, loop 
		; immediate
</pre>

This word takes a count and that number of words and assembles a padded table row
based on the inputs. The table is then assembled by just listing a series of opc
rows in the source code.  I then ususally add a couple comments to the row using
Forth's end of line comments:

<pre>
	opc	1	$c3	\	;	ret
</pre>

This line assembles a return instruction.  It creates an entry that ends up with
one byte of actual instruction, 4 bytes of length, and 11 bytes of padding.  The 
padding is critical to making the table efficient.  As each row is 16 bytes long,
the conversion from integer offset to instruction is simple calculation:

<pre>
	: ins ( n -- )
		16 * opcodes + dup 4+ swap @
		0 do c@+ c,exec loop drop ;
</pre>

The first line simply calculates the address of the row and then fectches the
instruction length.  This could be modified to use a fully counted string, but
12 bytes of instruction has been more than enough so far.  The second line then
simply reads len bytes from the row and saves them to the executable section of 
memory.  It is then possible to list a series of instructions in code and generate
the associated machine code.

In writing that function, I found it necessary to define c@+ which isn't a standard
part of SwiftForth.

<pre>
	ICODE c@+ ( addr -- a+1 n )
		PUSH(EBX)
		0 [EBX] AL MOV
		EAX EBX MOV
		1 # 0 [EBP] ADD
		RET   END-CODE
</pre>

This simply fetches a character at the address, and leaves the address + 1 and the 
character in the top of the stack. This simplified the inner loop and made the code
cleaner.  In fact, these sequential read and write functions are so useful, I made
many of the design decisions behind the new Forth's opcodes around them.

Patching Literals
-----------------

Now one of the obvious downsides of copy-compiler is the problem of literals.  You
need a way to create numbers without needing to have a table the size of all possible
combinations.  The solution lies in a clever bit of code inspired by Chuck Moore's
tail call optimizer.  It turns out the difference between a call imm32 and a jmp imm32
is a single bit in x86 machine code.  Chuck's tail call optimizer looked at the last
instruction compiled, and if it was a call to a word address, he simply flipped the low
bit in the 5th byte from the end of the instruction  stream converting a $e8 call 
instruction to a $e9 jmp instruction. 

This solution of back patching the instruction stream turns out to be incredibly useful
in the x86_64 instruction set.  It turns out the immediate value you most often want
to specialize across instructions is in the last position.  This means you can rewrite
the last 8, 4, or 1 bytes to specialize every instruction that can use a literal. 

<pre>
	: patch1 ( c -- ) exec-here 1 - c! ;
	: patch4 ( addr -- ) exec-here 4 - ! ;
	: patch8 ( high low -- ) exec-here 8 - ~!+ ~!+ ;
</pre>

With these three patch words, we can patch 64bit, 32bit, and 8bit literals.  All of
the jump and call instructions which are not stack relative can be implemented this
way.  And many of the utility and math functions that can be optimized via literals
can be patched this way too.  Using a simple look-back and patch strategy can also
optimize prior code at a very low level.  It becomes possible to elide stack juggling
entirely in some cases by looking at the prior instructions and back patching.

One of the side effects of this how literals are handled.  The way a literal is
compiled is it first pushes a literal 0 instruction, and then patches that literal 0
with the actual value of the literal.  A subsequent math operation may then look
at that last compiled value and decide that it fits within the bounds of the immediate
value of it's patch variant.  It then reassembles the entire instruction to compile
a literal add, sub, multiply, or divide.  All of the stack juggling involved in pushing
a literal and loading it into a register can be avoided entirely.

Segmented Memory Architecture
-----------------------------

Most interestingly this approach can work across words.  It is entirely possible
to have compiling words that assemble an instruction stream, and have the instructions
patched across word boundaries.  The reason this works is another inspiration taken
from [http://colorforth.com|colorforth], a segmented memory model.  Chuck's compiler
allows for definitions to flow from one into the next, all of the dictionary data is
kept out of band in a seprate memory region.  This allows one word to fall through to
the next if no return is specified.  This makes writing vectored code rather easy,
and avoids additional stack juggling.  It also makes it easy to strip all of the
compiling information for producing turn key binaries.

For this forth, I've settled on 3 memory regions: data, exec, lexicon.  The data region
comes first, and holds all of the initialzied an uninitialized memory for use as data.
It is loaded R/W from the product binary and is managed as it's own heap.  The exec 
region is a .text section that is loaded R/X or R/W/X depending on if it is a 
production or development build, and this contains the primary binary.  The goal 
for a production build is to be able to run this on Harvard architectures, and to
lock down the application binary for turnkey solutions.  The lexicon memory region is
another data region loaded R/W in development builds, and it can be left out of 
a production build entirely.  

The segemented architecture helps do three things:

* makes better use of the cache lines with more addressable regions
* avoids dirty pages in instruction cache and CPU stalls due to self-modifying code
* cleanly separates meta-data from data and code

This doesn't mean that the system can't compile code on the fly and execute it,
as in fact it does just that, but rather by segmenting the regions we can be more
certain that we don't inadvertantly modify code when modifying data.  Buffer overflow
bugs are not likely to write data to an executable segment (except in a development
build), and we can limit the attack surface by having no-X flagged on all of the
data segments preventing code from executing tained user data.

When thinking about putting these binaries into an appliance that will be in a 
hostile network environment, these design choices become more self-evident.  While
it may still be possible for the executable to do something undesirable via user
supplied data, the attack surface should be limited to only things that the program
can already do.  Code injection attacks should largely be avoidable in this setup.

Lexicon vs Dictionary
---------------------

In conjunction with the segmented memory architecture, the dictionary architecture
is reworked to merely label the data and exec segments.  The initial format of the
dictionary is a simple table:

<pre>
	+--------+--------------------------------+--------+
	|length  | string                         | addr   |
	+--------+--------------------------------+--------+
	|....... |............................... | ...... |
	+--------+--------------------------------+--------+
</pre>

This table is constructed of a string length, the string, and a address.  The address
is just 32 bits, as that is the largest offset storable in the x86_64 instructions.
Far jumps require computed jumps and can be done via a TOS jump or call, and it is
highly unlikely that any program will ever reach >2GB in executable code anyways!

It is likely that as the tooling develops, I will add additional fields to this 
structure such as file, line number, and an inverted index to all of the references
to the word in the source code, to enable search.  These features can be added on
by simply growing the row-size and appending the associated bits to each entry.

Addresses for both the data and exec segments can be stored in the dictionary, and
the primary difference between the two being the address range.  As all data pointers
are within the data segment, they naturally fall within a given offset range.  All
code pointers fall within the exec segment and as subsequently in a different range.
This allows us to do a simple comparison to determine which segement a given address
falls into.  There's no need to flag this as code and this as data, as it is a 
computable property.

I've not settled on how I want to handle other sorts of flags.  Right now only 
immediate words are a concern.  I may simply add an additional flags field to the
row and make life easy.  Trying to save space in the dictionary seems like a fool's
errand, as it is likely to be omitted entirely for a turnkey solution.  And since
I am more likely to extend it to support an increasing number of useful development
features it seems like a safe bet.

System Calls and ELF
--------------------

In order to support the segmented memory model at the system level, I've implemented
most of the ELF file format specification in Forth.  I can create executables with
multiple segments in memory.  I can generate symbol tables and will soon have 
support for dynamic linking against C libs. This will allow for loading code
on those platforms that have an ELF bootloader or run as a Linux application.

Using my ELF code, I should be able to implement native binaries that run on Linux
without any external support for turnkey applications.  Combined with the 
SDL Forth code, it should be possible to implement fully functional applications
that could be redistributed via Steam / etc.

For system level calls, I wrote a script to extract all of the syscall constants
and have instruction support for making x86_64 ABI calls on Linux (and MacOS X too).
This means most of the functions one needs to make an application do useful 
work on a modern OS are also immediately available.  I've been avoiding linking
against libc in any variety, and this means the OS calls are unmediated.  As a
result, it is often necessary to deal with system specific quirks in Forth code,
and not rely upon higher level abstractions commonly found in C code. 

At the end of the day, I would also like to support bare metal applications for
embedded devices. Towards this end, I've been careful to ensure that system 
level interfaces can be swapped out for hardware specific I/O.  Polling a GPIO
or reading a SPI flash should be just as easy as calling read(2).

Porting to New Architectures
----------------------------

Once I have a working self-hosting x86_64 build, I am planning on porting the code 
base to other architectures.  On my list of chipsets in order of desirability:

* Freescale iMX6 Cortex A9 CPU (64 bit)
* NXP LCP114 Cortex M0 CPU (32 bit)
* Xtensa LX series (32 bit)
* AVR ATmega32U4 (32 bit) 
* MIPS32 (32 bit)
* a softcore running on a FPGA (Lattice ICE40 or Xilinx Spartan6) 

The concept of the copy-compiler means that most of a port is constructing a 
compatable instruction table.  Obviously the optimizing bits will need to be
different for each platform, but many of the concepts work as-is.  As I port
from architecture to architecture I expect the abstract instruction set will
morph to accomodate the differences between platforms.  

Porting between processor architectures is a good way to test your assumptions
about how to best design reliable code.  Simple things like multiplication and
division work differently on each piece of hardware.  Not having hardware
support for basic math can directly impact how you construct code.  Restrictions
on where data and code may live in memory can also impact your design. Many
of the design decisions I've already made attempt to incorporate the
limitations I already know exist in some of my target chipsets.


