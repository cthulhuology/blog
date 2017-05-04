Fighting History
================

In working on several projects recently, I have become increasingly unhappy with
the state of tooling and it's relationship with the GNU/Linux ecosystem.  One of
the things I tried to do was bootstrap a minimal Linux system with different 
C compilers:

* [http://gcc.gnu.org/|GCC]
* [http://pcc.ludd.ltu.se/|PCC]
* [http://bellard.org/tcc/|TCC]
* [http://git.suckless.org/scc/|SCC]

And what I discovered while doing this is that a tremendous amount of code assumes
that you are using GCC and GLIBC.  GNU code is particularly horrible when it comes
to doing non-standard "standard" things.  In many cases, the more pendantic you 
set your compiler settings, even with gcc.  There is also a considerable amount of
code duplication.  Probably the worst piece of software is [https://www.gnu.org/software/gnulib/|gnulib]
, which attempts to provide a gnuism layer on non-gnu libc.  It itself often requires
patching because it fails to be portable!

For those who are curious what sorts of bad behavior are baked into the core tools
of their system, we have some wonderful examples:

* [https://wiki.linuxfoundation.org/networking/iproute2|iproute2] 
* [http://net-tools.sourceforge.net/|net-tools]
* [https://w1.fi/wpa_supplicant/|wpa_supplicant]
* [https://www.freedesktop.org/wiki/Software/pkg-config/|pkg-config]
* [https://www.gnu.org/software/groff/|groff] 
* [http://man-db.nongnu.org/|man-db] 

Iproute2 ships with it's own  linux kernel headers, which it attempts to use over the kernel supplied ones.
Net-tools has a few C syntax issues in addition to having some GLIBC specific header non-sense, while missing limits.h.
Wpa_supplicant assumes you're using OpenSSL, and requires significant patches to work with LibreSSL, while making horrible
assumptions about your linker behavior. Pkg-config makes unsafe use of formatted output in an attempt to test the locale 
capabilites of the system, and is questionable at the best of times.  Groff mixes C and CPP in horrible ways
resulting in failure to compile entirely with compilers other than GCC, and  failing to link with GCC if any sanity 
checking flags are applied.  Man-db ships with broken gnulib and getopt code and doesn't work with other libcs other than 
glibc, which if ironic since gnulib only exists to make it portable.

All of these packages are prime examples of software in desperate need of replacing.
In the case of groff / man-db, I simply replaced them with the excellent [http://mdocml.bsd.lv/|mdocml]
which is portable, and compiles both on Linux and BSD.  It also has a great example
of doing the:

* ./configure
* make
* make install

without abusing automake, autoconf, and libtool.  And let's make no mistake, there
is nothing but abuse when it comes to those there abominations.  They do little to
nothing for portability, and are a legacy born out of GNU incestuous behavior.  The GNU ecosystem
has developed pathological idiomatic behavior.  It has so heavily infected the GNU/Linux ecosystem
that most people kinda just shrug an ignore it.  Projects like [http://suckless.org|Suckless] are
sane reactions against this sort of behavior.  In comparison, it was possible to compile sbase and ubase
with a couple different C compilers, once issues with libc were ironed out.

There is a common idiom used by all of the tools that actually work nicely in a portable fashion:

* environment variables for overriding settings
* a sane makefile architecture
* a generated header file for code configuration

One of the great failures of the automake, autoconf, and especially libtool set, is they have too many
layers of indirection.  Projects ship with multiple layers of configuration vairables aliased by layers
of generated makefiles and configs, but then don't honor them due to hard coded values in templates or
libtool scripts.  For example, several projects offer ./configure --enable-static as an option, but then
hard code -Wl,export-dynamic in their libtool script!  Get to the end of compilation, and it tries to
generate a set of .so files even though the compiler and platform don't support them!

Similar behavior is being exhibited by the systemd crowd as well, where their tools are also pathologically
idiomatic.  The sheer antagonism towards other systems exhibited by some of the developers in that community
is repugnant.  Where as GNU made it a bad habit to build upon it's own idiomatic behaviors, the systemd 
crowd are explicitly antagonistic to the BSDs and other open platforms.  I can easily see them creating an
even more insular ecosystem of institutionalized poor design decisons.

 


