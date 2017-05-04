Forgotten Knowledge of Assembly Techniques
==========================================

I have spent my free time for the first two weeks of 2017 reading old Forth implementations.  Nothing says fun like reading x86 assembly and
Forth listings.  The Forth listings I've been reading are in no particular order:

* [https://www.Forth.com/swiftForth/|SwiftForth]
* [http://git.annexia.org/?p=jonesForth.git;a=blob_plain;f=jonesForth.S;hb=HEAD|jonesForth]
* [http://www.exemark.com/FORTH/eForthOverviewv5.pdf|eForth Overview]
* [http://home.iae.nl/users/mhx/eForth.html|eForth]
* [https://github.com/jamesbowman/swapForth|swapForth]
* [https://github.com/nornagon/espForth|espForth]
* [http://www.merlintec.com/download/color.html|colorForth]
* [http://www.greenarraychips.com/home/documents/greg/cf-releases.htm|arrayForth]

When you read enough implementations you end up finding gems of programming in unexpected places.  After years of reading output of
C and C++ compilers, you grow accustomed to the piles of compiler generated goop.  Debugging compiler errors becomes an exercise in
understanding the horrors of how compilers translate language constructs to actual machine code.  While most developers simply assume their
code is wrong, and rewrite it until it works, I find I run into legitimate compiler bugs about every 18 months.  While reading that 
compiler generated shit you rarely see code that makes use of the more esoteric instructions of a given processor.  Rather it is all
very much LCD.  Not so with hand coded Forth implementations!

Take for example how Bill Muench grabs the carry flag for UM+

<pre>
	xor cx,cx
	..
	rcl cx,1
	..
	push cx
</pre>

If you read the Intel instruction manual, you'll find that rcl and rcr include the carry flag in the rotation.  I can't remember the last
time I saw a C program what used this instruction, let alone used it in this way.  In fact, aside from using some GCC directives, it is nearly
impossible to access the carry flag state in C.  In a similar fashion, jonesForth uses the setcc instructions for setting flags, in the 
definition of comparison words like '=':


<pre>
	pop %eax
	pop %ebx
	cmp %ebx,%eax
	sete %al
	movzbl %al,%eax
	pushl %eax 
</pre>
	
This is just a simple example of grabbing the associated flag and making available for calculation.  You won't see this instruction used in
most C programs, as the compiler will typically only use conditionals for branching, in the form of jcc instructions.  On rare occasions when
you have an expert C programming using == to do a conditional calculation the compile a set of branches, or if optimizations a cmovcc operation 
if static analysis can reduce the calcuation to a choice.  But you'd be hard pressed to find a C program that ever generates a setcc instruction.

But the brilliant insights into assembly programming aren't limited to just use of instructions ignored in popular software.  Take Chuck Moore's
tail call optimization code.  The default behavior of the colorForth compiler is to assmble a call to a word:

<pre>
	e8 addr 
</pre>

But Chuck's code for ; looks to see if the last instruction compiled was a call to a function, and if so simply rewrites one bit, changing the 
call to a jump:

<pre>
	e9 addr
</pre>

This look back optimization is incredibly cheap to perform and results code that supports proper tail recursion.  The colorForth code is full of
similar pithy code.  The two branch instruction in color Forth if (0branch in jonesForth) and -if (branch if not signed, aka 0>= 0branch) are
compiled as

<pre>
	74 2, here
	79 2, here
</pre>

These effectively compile

<pre>
	jz 0
	jns 0
</pre>

respectively and place the address of the next instruction on the stack.  The word "then" pops this address off the stack, subtracts 1, and
updates the 8bit jump address.  This compile and patch style is not only clever in its efficiency, but also in how it reduces an open ended
problem to a simpler form.  Since Chuck only allows for a 255 byte offset through his choice of instructions, if/then pairs can not span 
huge amounts of code.  But since Forth by definition is to be highly factored, this limitation is not a practical problem, only a theoretical one.

Similar reasoning can be found in eForth, which requires 31 primitives to be implemented for a processor so that the whole system can be
bootstrapped.  The total lines of assembler to implement these 31 primites is roughly 200.  Probably my favorite of those 31 primitives is the
"!io" word which initializes the serial io hardware such as a UART.  The definition of !io on DOS as:

<pre>
	CODE !IO $NEXT
</pre>

which is essentially a no-op as all of the IO was setup to use the DOS interrupt handler 21h and no setup was necessary.  But if you're porting
this system to an embedded processor, you might have to set some flags here to enable the pins and set a baud rate if configurable.  Once setup,
eForth would read your programs from the serial line and interprgt them.  This is about the simplest tethered development environment one can
imagine.  Loading your code is just copy and pasting into your terminal.

Having spent the better part of the past 3 years developing embedded applications on a wide range or processors and boards ranging from 8bit
processors to massive FPGA packages, I have to say the state of the art in 1983 still beats the pants off most current toolchains.  Reading
a collection of old and modern Forths, I have rekindled my appreciation for the craftsmanship that went into these systems.  The choices made
by each of these craftsmen was based on experience and a deep knowledge of their medium.  And it is this craftmanship that stands in stark 
contrast to most of modern computing, with it's slap dash assume inifinite resources on a generic architecture approach.

Perhaps paradoxically, reading all of these assembly listings has also brought me to the realization that writing a Forth in C or assembly is
an assbackwards idea.  The general argument in favor of writing the initial kernel in C or assembly is you can port it to a new architecture.
But as Bill and Chuck have shown, you can port the kernel of Forth to a new CPU in less Forth code than you would in assembler.  The only 
prerequisite is knowledge of the machine's instruction set.  In the world of mainstream programming, knowledge of your hardware's instruction set
is an anathema.  But every bit of code you ever produce will be reduced to that very medium.  The entire point of writing the program was to
generate that machine code, so that the machine can do useful work. 

Personally, I've decided my next several experiments are going to be writing Forths in Forth for a set of processors that I am currently playing
with.  I would like to adapt many of the techniques I've rediscovered to implement a modern x86_64 Forth.  I would also like a nice ARM 
Forth for my various ARM based computers.  And I'd like a proper Forth for the Xtensa architecture, so all my esp8266 modules would be useful.
The core concepts I'd like to capture:

* separate memory spaces for source, dictionary, code, and data
* direct threaded code with proper tail recursion
* minimal processor dependent kernel, implemented directly in Forth for each CPU
* optional support for both host operating systems and bare metal implementations

For operating systems like Linux, the output should be an ELF program with separate sections for the source code, dictionary, executable code,
and data segment.  Based on all the research I've done, the full system should weigh in at less than 1kloc (~200loc/arch, + 300-400 common code).
This seems like a reasonable goal for 2017 as far as side projects go.

