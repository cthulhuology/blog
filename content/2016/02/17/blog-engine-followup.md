Blog Engine Followup
====================

So the new blog has been running for a few weeks, I've been beating on it, 
and watching what happens as various search engines around the world index it.
I've had monitoring turned on the entire time, and have logs going back weeks,
so any changes that I make can be measured against their prior behavior.  When
ever you have a new project in the wild, there is a shake down period where
you experience every thing that can possibly go wrong.  Here's what happened
to my server:


Out of Memory Killer
--------------------

First thing I saw was that there was a memory issue with the server.  Originally, 
it was crashing periodically when a cron job was running at night to apply security 
updates.  Every few days, the server would be killed dead as the Linux OOM killer
hit.  The problem here was there was no obvious problem with the application 
itself:

<pre>
	VmPeak:     4216 kB
	VmSize:     4216 kB
	VmLck:         0 kB
	VmPin:         0 kB
	VmHWM:      1480 kB
	VmRSS:      1480 kB
	VmData:      192 kB
	VmStk:       136 kB
	VmExe:         8 kB
	VmLib:      1800 kB
	VmPTE:        32 kB
	VmSwap:        0 kB
</pre>

Basically it wasn't using more than 4.2MB of RAM, and the server should have
been perfectly fine.  The run time state was 1.4MB of resident memory, which
is pretty close to none.  The OOM killer wasn't killing it because it was using
too much memory, but because it got hit with election.  What was the source?

Well looking at running processes, it turned out that [http://varnish-cache.org|varnish]
was running for no good reason, and it was using a default config with 1GB of
cache on a machine with 512MB of RAM and no swap!  I had at one point toyed with 
the idea of running varnish in front of it, but decided against it.  What I 
didn't realize was that just installing the package activated it!  This is
absolutely retarded behavior on the part of the Debian packager, as best 
practice is off by default.  Killing the 3 varnish services would solve this
project, and telling systemd to disable them all stopped the OOM killer events.


Unexpected Memory Leak
----------------------

The second issue I encountered is that the server continued to run out of memory.
Over the span of two days, the server would see RAM going from 215896 kB free RAM
down to 7648 kB.  The server would still be running, but I would eventually not
be able to SSH into the server.  

Weird thing here was in /proc/cpuinfo  SUnreclaim was going through the roof, and
SReclaimable was at 0.  Eventually the server would die due to a kernel panic,
as the kernel itself was unable to allocate pages and Xen would freak out.  This
bug took days to trigger, and wasn't consistent.  It also was undebugable as
a Xen kernel panic in Rackspace requires root access on the HV, which I don't have.

I suspected this had something to do with the child reaping.  The number in
/proc/stat processes as in the millions, but that also meant that it wasn't
the likely cause.  Needless to say this was a confusing state, as I had no
direct evidence of the source of the leak, and it looked like the leak was
kernel side!

In order to buy some time, I added singal support to the blog, and wrote a
basic monitor program to auto-restart the server on a SIGHUP.  I could have
configured systemd to do this, but given I was already dealing with a squirely
kernel level behavior issue, I didn't want to press my luck and discover 
a systemd bug as well.

Adding the signal handler, and the monitor, and having it auto-restart solved
no problems what so ever, but it meant that I could more easily reboot the
main server.  This lead me to discover the actual source of the leak.


Too Many Open Files
-------------------

After running for about a week of reboots every 2 days, and absolutely no 
data in the logs.  One of the problems of debugging the memory issue after
adding the restart monitor was nothing was failing, I just couldn't ssh 
into the machine any more.  Nova-console was also failing now to give any
connections, and the web server was running but I was getting connections
dropped on the client side.

I had scripts running in the background which proved I had memory enough
right before I reboot. So I decided to check a hunch that the source of
the kernel running out of slabs was a side effect of having lingering file
descriptors.  One of the possible causes for not being able to get a ssh
connection was that there were literally no free file descriptors left! 
Even with ulimit -n set to 65k files for the server process, 
/proc/sys/fs/file-max only reported 48k.  Bingo!  

So the reason that this was happening was I forgot to add a close statement.
After the fork() call in the main server, the accepted file descriptor
was still open on the server side!  The interior of the fork() duped the
socket into stdin and stdout of the child process, and that would get
closed when the child process exited.  I had forgotten to close the copy
of the socket file descriptor in the parent's process.  It just happened
that rougly every 2 days, this would result in hitting the 48226 open files
and the server was more than happy to linger.  Sending the process a
SIGHUP would now cause it to exit, and the open file count would drop 
down to a couple hundred, and the system would be fine again.

So adding line 119 to the server.c to close(client); solved the system
going unresponsive, and freed all of the missing slabs, and ensured
that the free memory of the system was back up to 200MB.  This also
demonstrated something interesting in that my blog server is currently
serving about 24k requests per day!  4k of those requests are the
3 monitoring checks made every minute.  What are the other 20k requests?

Just bots.  Lots of bots.

