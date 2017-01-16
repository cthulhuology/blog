Building Xilli
==============

In building [http://xil.li/|xilli linux], I would like to avoid a large number
of the outdated methodologies so popular in commercial linux distributions.
Many of the design decisions behind the systemd / gnome / freedesktop model
are born out of what was cutting edge in Windows NT ca. 1995.  Service managers,
ini file style settings, COM IPC galore, were the hallmarks of the system.

Looking at how Microsoft has evolved PowerShell into a much more functional
and composable model for system administration, it probably should be argued
that the command line was a better interface even for 1995.  And now that
Microsoft is supporting PowerShell on Linux for system administration and
open sourced it, I think it is time to re-evalutate what a system should 
look like for the next 20 years.

Some Historical Perspective
---------------------------

About 16/17 years ago, I worked at VA Linux in the Software Engineering 
department working on factory automation.  While there, we had an idea for
a fully static compiled linux distro which would have solved many of
the problems we saw with updating systems in the field and in the factory.
While we had been re-packaging Redhat and Debian with a more enterprise
friendly set of fixes for our hardware, we couldn't easily distribute new
applications for old systems.  Every few months the upstream libraries 
would release fixes, and ABI compatability was something of a joke in the
open source movement of the time (and still is).

Our thinking was if you could statically compile all of the applications
you could simply rsync updates.  Entire clusters could be upgrades in
as much time as was required to compute the diff and upload the changed bits.
Since each application was statically compiled, you could be certain that
if you copied a new binary to an old system it "would just work" (TM).

At the same time, I was rather interested in the development of [http://0install.net/|0install]
which promised bringing application bundles similar to those on NextStep
(now MacOS) to Linux.  By bundling the application and it's dependencies
into a single directory with relative pathing, one could get rid of the
co-mingling that comes with installers and package managers.  It is the
sharing of state that causes problem as state changes.  The best answer
is to isolate the concerns (aka applications) so that they could be 
managed independently.

This line of thinking was also adopted heavily at Google, where the design
of Go lang captured this same problem space.  Go statically compiles 
everything because it is much easier to distribute a binary with all of
it's dependencies included, than it is to replicate the dependent state
across hundreds of data centers.  When trying to ensure reliability you
want your state to be as reproducible as possible, and cp produces an
exact copy of that state.

The Xilli Experiments
---------------------

In developing xilli linux, I plan on experimenting with a set of concepts
to make a linux distribution that will be very pragmatic in it's approaches
and management.  By looking back on the last 40 years of systems administration,
I'd like to take the best ideas of systems past, and look to how they
should shape the future.  At the same time, I want to look at historical
baggage that results in cruft, and ruthlessly remove it from the system.

Towards these ends I'm going to run a set of experiments to see if it is
possible to build a future looking system with modern technology and 
careful application of technique.  These experiments include:

* fully static linux - no ld-linux interpreter anywhere in the system
* isolated services - all services run in chrooted cgroups (containers light)
* monitors not managers - independent watchdogs ensure system state
* new command line - all management through the command line w/ improved shell
* message passing ipc - command pipes for extended service management
* rsync updates - update service & security patches through rsync
* no packaging - all in one binaries for application packages
* single user system - key based access for both physical and virtual
* signed binaries - all binaries are signed and verified before running

The core concept is to minimize the dependencies between system components,
while providing clear interfaces for each application to communicate intent.
Isolation will be core to the system, including being able to isolate the
system from the administrators.  It should be easy to create an applicance
which has no user accounts, but can still be managed via a remote command
line interface.  As for user accounts, the premise is the high lander 
principle of "there can only be one".  Services will run in unprivledge
containers, but the only user account on the system will be root (which
will be renameable to a name of your choice). I want xilli linux user
to own their machines, and not have their machines own them.

There are a few hard hacks that will make this system possible which 
include doing things such as patching 3rd party binaries to statically
link what were previously dynamic objects, building a new shell that
is much more secure and network aware, and bundling r/o file system images
into elf binaries for applications.  Should these experiments be 
successful, the resulting system binaries should run for  as long as 
the linux kernel ABI remains stable, and the processor architecture 
available.  

From a system administrator perspective, security should be vastly 
improved, as one can rationally prevent users from accessing the
system directly.  Most management tasks should be acomplished by
cloning a base system image, or through use of key based application
access via a remote shell.  With signed binaries, a system will
only run applications that the owner of the system has explicitly
authorized to run by signing them.  By removing the dynamic linking
option, it should also prevent library injection which makes the
signing system much more practical.

Managing multiple datacenters of xilli linux machines will also 
benefit form having monitoring built in as a fundamental concept.
Rather than relying upon a local system init & friends to monitor 
applications, xilli will follow OTP concepts of remote monitoring, 
wherein remote watchdogs and logging are the norm.  With logging
taking the form of event message passing, remote monitors will 
make it easy to eliminate single points of failure in your 
datacenters.


