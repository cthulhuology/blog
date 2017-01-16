Another Virtual Machine
=======================

Six days ago, I started working on [https://github.com/cthulhuology/avm|Another Virtual Machine].
So far I've logged about 10 hours on it and have:

* an Interpreter (in C)
* an Assembler (in C)
* a partial implemenation in verilog

A couple days ago, I got the first assembled program to run on the interpreter, and had
it execute correctly.  In about another 10 hours, I expect to have a working verilog version
in simulation, and possibly synthesized on an FPGA.  At that point, I can start working on
what I'm actually interested in.

A Few Word on Methodology
-------------------------

One of the main keys to success with this project is the methodology.  The process is
incremental and constructive, building a series of simulations with ever greater degrees
of specification.  Over time, the successive revisions will tease out details necessary
to make the design work in reality:

* a high level emulation and tool chain
* a gate level simulation and self test
* a physical level simulation and hardware test rig
* an asic implemenation with tool and test chain

The high level emulation allows for testing and playing with logical constructs and 
behaviors.  It is cheap to do an experiment entirely in software, and easy to test the
state machine with previously saved state.  In contrast to hardware, it is much 
easier to get your software emulation into a known state.  This also allows for the
development of the software tool chain before there is even a gate level simulation.
Being able to write your test kit using what will be the production toolchain gives
more confidence in the feasability of using the instruction architecture in production.

The gate level simulation in EDA software, provides a view into the timing issues you
will have with the output of your HDL.  There's a world of difference between the 
software simulation and the hardware simulation. At least with the software 
simulation verifying the behavior, you can reduce your problem search space to the
translation of HDL to a netlist.  Ideally, your Power On Self Test (POST) that runs
under software emulation will run just as well on your simulation.  

Moving onto a physical level simulation using an FPGA provides another level of 
confirmation.  By synthesizing your netlist into a functioning physical design 
allows for the next stage of tooling.  Specifically, the FPGA board will allow
you to develop a physical test rig for driving inputs to the POST.  While the
FPGA is likely to have very different physical characteristics from your target
package, you can design a breakout board that allows you to emulate that piece
of the tooling.  With that you can design and build a physical test rig for 
proving out your ASIC implementation.

The last billion steps of moving from a GDS file to actual package silicon is 
a whole nother world.  Here's where physics and chemistry and the characteristics
of the manufacturing process take over.  This is also where things start getting
expensive.  $5k+ for a small sample run becomes the norm, and each revision 
will cost at least as much.  If all of the design bits up front have been working
to this point, getting across the finish line is a matter of time and money,
lots of money.


A Few Reasons For Doing This
----------------------------

Given the cost in time and treasure, it would seem I should have a good reason for
doing this.  And while that is debateable, I'll try to describe the problem space
in which I'm interested.  

Most modern CPUs are designed to run legacy programs.  These programs and programming
styles were born out of the limitations of the systems on which they ran.  Typically,
they are derived from software that ran on machines in which a single processor could
run a single instruction at a time, and that processor had to be shared by multiple
users.  Computers were expensive and had t be shared.

The net result is we ended up with large operating systems that attempted to share
computer resources across multiple simultaneous users and programs.  As computers
got smaller and cheaper, we kept running software written for ye olden days.  And
as the physical limits of reality were reached by manufacturing, we started adding
more and more CPUs to ever cheaper computers.  But the software is stuck in the
mainframe world.

If you want to build the future applications, you need machines with not 1000 cores,
but 10k, 100k, 1MM cores.  And these cores aren't going to be running Linux.  In
fact, these cores are going to be more like Objects in OO programming languages,
communicating over physical buses via messages.  Biomimetic programs are good 
targets for these sorts of systems.  Burning a few thousand cores to recognize
things in the real world will become common in the world of robots.  And the
general purpose programming models will not apply, as no sane person is going to 
ask a few robot retina cells to process a spreadsheet some fraction of the time.

The instruction set I'm building is a MISC computer designed for streaming data.
While the processors will be small, they will be capable of doing useful work,
and the designs can be sized to fit the desired workload.  The goal is to have
a design which could support having 1k cores with reconfigurable message buses
in hardware.  By interconnecting multiple cores, the design will be able to 
scale horizontally to 10k, 100k, 1MM cores.

Rather than focus on building hardware for existing applications, I am looking
at designing hardware for future applications, systems which recognize and 
interact with reality on a physical level.  Having worked with speech and 
image recognition at global scale, I feel like I've developed a gut feeling 
for what should work in smaller packages, if only I had the hardware.  This 
design is an experiment to test if that feeling is on track.


Where We're Going There Are No Roads
------------------------------------

Looking at the ambition, it would seem daunting given that not only am I designing
the processor, but also the tooling to program the processor, and also the 
programming methodology for the target applications.  The design is going to 
consist of tens of thousands of independent processors communicating via message
passing, similar to an Erlang program, but without the luxury of OTP.  But the
reality is that the ambition allows me to dump all of the shit I don't need.

For programming languages, Aaron commented "your assembler looks a lot like Forth",
to which I replied it was.  By using the meta properties of a language like Forth,
I can have the assembler be the low level Forth operators, and the instruction set 
architecture directly supports Forth constructs.  My Forth tool chain can directly
compile to the instruction set architecture and much of the core is directly
implemented in the hardware design.

For operating systems, I am not going to have one.  Rather, I am going to focus
on the ROM code for the message routing layers.  By controlling what messages
get passed to which cores, I can provide basic OS level services (process isolation,
hardware access, etc), but through a message broker architecture.  Additionally,
since the cores will be small enough, the object model for the program components
will be similary reduced.  There is no need for object linking and embedding when
each processor is running a single object.  Technologies like DCOM are a poor 
facimilie of the processor based messaging.

Lastly, the hardware interfaces will also be designed to take advantage of the
hardware itself.  As I am designing a familiy of related processors, I intend
to extend the internal message passing to the peripherals.  Keyboard, mice,
stylus, cameras, microphones, laser range finders, servos, etc. will all have
integrated microprocessors which will work the same way.  The hardware will send
messages and the other objects will respond if they are interested.  Having
object oriented hardware will place the device drivers where they belong,
in the device itself.

So the ambition is to reinvent all of modern computing for the future.  It 
should only take a few months at most :)


