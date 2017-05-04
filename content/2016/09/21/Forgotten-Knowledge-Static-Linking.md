Forgotten Knowldge Static Linking
=================================

The past few nights, I have been researching what the current state of the
art is when it comes to the building of a static toolchain.  As much of my
knowledge of static linking of elf on Linux comes from hand coded i386 and 
x86_64 assembler, my personal information is largely on how the kernel 
actually handles the elf file format (what it uses, what it ignores, what
it doesn't care about). My knowledge of how binutils and gcc handle static
linking is much more limited, as I have largely delegated that knowledge
to musl-gcc.  So I wanted to make sure that I wasn't opening a can of worms
that wouldn't have me hacking on gcc internals before long.

What I found suprising is that there is precious little written about how
gcc and ld-linux actually operate, especially when it comes to how they
use the elf file format.  Instead, there are a lot of people writing 
opinion pieces like mine:

* [https://ro-che.info/articles/2016-09-09-static-binaries-scientific-computing|https://ro-che.info/articles/2016-09-09-static-binaries-scientific-computing]
* [https://www.akkadia.org/drepper/no_static_linking.html|Static Linking Considered Harmful]
* [http://sta.li/faq|Stali FAQ]
* [http://harmful.cat-v.org/software/dynamic-linking/|Dynamic Linking]

This state of affairs is rather deplorable, as it demonstrates we have
reached a point where these core technical decisions are largely a matter
of religion and historical accident than data and reason.  Finding a
half decent description of how things function will take you to pages 
like:

* [http://www.ibm.com/developerworks/library/l-dynamic-libraries/|Anatomy of Linux dynamic libraries]
* [http://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html|Shared Libraries]
* [http://tldp.org/HOWTO/Program-Library-HOWTO/dl-libraries.html|Dynamically Loaded (DL) Libraries]
* [http://man7.org/linux/man-pages/man8/ld.so.8.html|ld-linux man page]

But all of them give only the most superficial descriptions of how the
linker actually works.  Having implemented dynamic linked elf files
by hand in assembler, I find the gap in information readily available
and what is required to be huge.  Reading the opinion pieces, I also
get the feeling that most of the parties weighing in, while well 
educated on the subject, would also be hard pressed to explain
to ordinary programmers what and why these systems work they way they do.

In fact, the GNU toolchain has so many peculiar implemenation details
that are taken for granted across the board, it is incredibly difficult 
not to get the feeling that the current state of the art is just layers 
of cruft compacted so hard through years of abuse.


