Blog Architecture Revisited
===========================

Today I have released a new blog architecture that I wrote just to challenge my assumptions about programming servers on Linux.  The basic concept behind the design of the 
server itself is a modern take on inetd, in which a generic server forks off request handlers that process data from stdin and write it to stdout.  Right now the server is 
setup to serve content on a single port (unlike the crazy configuratoin system for inetd) and it invokes a **blog** executable that parses the HTTP request and generates the
HTTP response.  Since each client is handled by a separate process, there is no chance for one user to receive data meant for another user.  This provides some level of security
through isolation.  Additionally, as the programs are reading and writing from stdin and stdout, testing the program's behavior without running a server is trivial. This
makes it possible to separate the concerns to only the most essential bits.  By isolating the concerns, it also allows for simplifying the behavior of various components.
The primary server merely accepts TCP connections and hands it off to another program to process.  The http handler process itself merely servers static pages, and in the event
that a path is not found it serves a table of contents page.  The blog is generated from markdown files and some prebaked html headers and footers.  Deployment is handled
via a very simple rsync, and code can be swapped out at run time as the binaries are loaded on a per-request basis.  The only reason the server ever need go down is to solve
a bug in the core socket handling code.

The separation of concerns not only improves security but it also improves performance.  As each program does so little, it can afford to be statically linked as they are
terribly small.  The cost of loading 10,000 per second small statically linked binaries is neglible compared to loading of most monolithic frameworks.  Additionally, as 
the binaries are statically linked, the kernel has them in memory and the copy-on-write behavior means very little actual memory need to allocated for each process.  Finally,
as each client is handled by it's own process, there is no need to ever call free or do any garbage collection as the entire process space is typically consumed in under 100ms.
What this means is that the code works more like Erlang code written in C using the Linux kernel as a fair queuing scheduler and garbage collector.  It turns out the vast
amount of effort that has gone into tuning the Linux kernel has produced a system that can sustain spawning 1000s of processes per second with very little load.  The magic
of the clone() system call and it's behavior with execvp() allows us to write little UNIX programs that read from stdin and write to stdout without even knowing we have a
socket connection.

So what impact did these architectural changes have?
---------------------------------------------------

Compared to serving on via Ghost (nodejs), the new C code is a massive improvement.  The over all performance is insanely better and the response times are much better.

* Time to First Byte - from ~140ms (nodejs) to 5ms (C)
* Request Duration - from ~150ms (nodejs) to 5ms (C)
* Request Size - from 15k to 25k
* Site generation time - from ??? to 214ms

Seriously, the time it took for another machine in the same data center to receive a byte when from 140ms to 5ms, and the response size grew by 66%! The reason it grew,
was rather than serving 20ish article links, I decided to single page the entire site table of contents.  I removed the meaningless blurbs, and just left the titles.  
As I have 240 blog posts over the past 6 years, this actually results in a considerable amount of processing not happening every request.  As a result, the efficiency
is basically that of the kernel serving a request from RAM, because that is what it is effectively doing each time.  Caching no longer makes sense, when you are going at
the speed of the Linux kernel.

For example, downloading the home page over wifi from my house takes about 87ms on average (with all caching disabled).  That is a good 60ms faster than I was getting in 
the same datacenter using Ghost!  Before I was seeing page load times of around 220ms for the smaller 15k home page.  And since I've still not enabled any sort of etag
on the server side, the server is still handling all of the client requests each time.  Considering how little traffic this blog gets, I doubt I will ever care about that.

Site generation is an interesting problem, as on my 8core i7 system, the new code generator takes 214ms to generate all 240 blog posts.  It does this by spawning a sepratate
worker process for each md file it converts to html, and it creates a site index file for the table of contents.  By running these in separate processes, the full 8 cores
are used, and it takes about 214ms to generate the entire site.  This time is so small that making a quick change to all of the pages isn't a concern.  Ghost generates the
HTML for each post when you edit it, so I can't get an apples to apples comparison, but it is interesting to note that the time it takes to generate the entire site on my
machine is less than the time it takes Ghost to serve 2 requests on the local network!

But what about the software complexity?
---------------------------------------

The comparison between Ghost and the C code in terms of complexity is totally unfair.  Ghost includes a lot of features I have decided against.  My editor for blogs is VIM,
and my database is the filesystem, and my publishing tool is rsync.  My C code base does however properly convert all of the Ghost md pages I had to clean HTML.
Currently, the entire C code base included test framework and tests is 1431 lines of C (1113 of code and headers, 318 lines of tests).  This code is divided among several
different applications:

* server (73 loc) - primary socket server that accepts client TCP connections and forks off workers
* blog (20 loc) - blog server that takes a http request on stdin and output a http response on stdout
* generate (64 loc) - generates the static site by traversing the directory tree and spawning md workers
* md (175 loc) - takes markdown on stdin and outputs html files on stdout

These four programs make up the core of the blog system, and are very similar in their over all philosophy.  Both *server* and *generate* are top level supervisor systems
which spawn workers that do all of the dirty work.  In the case of *server*, the workers are forked per client connection, whereas *generate* forks one per file.  The
*blog* and *md* programs too serve the same basic function, taking some user input from a socket or file and generating the desired output be it a http response or html file.
Each supervisor waits for their workers to finish their jobs, and then properly reaps their processes, preventing a flood of zombies on the system.

Supporting these programs are a number of utility files which provide the infrastructure for building these applications:

* str (83 loc) - string routines 
* list (56 loc) - double ended cyclic list routines
* dict (46 loc) - cyclic hash map routines
* file (39 loc) - file routines
* dir (61 loc) - directory routines
* parse (110 loc) - string parser routines
* worker (47 loc) - worker spawing and reaping routines
* html (69 loc) - html generation routines
* http (209 loc) - http request and response routines
* test (49 loc) - test framework routines

These supporting files are often used by more than one of the primary programs, and provide some common idioms across applications.  The parser routines are used by
both the markdown and http code to process the text of each.  The string, list, and dictionary routinesr provide constant space data structures that are similar to those
found in most dynamic languages, however with a very opinionated feel.  I should note that although I wrote the dict code, it isn't actually used anywhere in the system.
The list code is also only really used as a stack for traversing directory trees or generating paths.  All the same, I may have use for that code one day, and it has tests,
so I'm including it.

Conclusions?
------------

So what I take away from all this is that it is now possible to write UNIXy programs that work like Erlang processes, that each only do one thing well.  Rather than building
on top of complex frameworks w/ tons of dependencies, it is in fact easier to write the entire thing from scratch.  Code reuse inside the project provide sufficient
justification to break some things out into their own files, but higher levels of abstraction and interface cost more the more you use them.  Probably most importantly, by
removing features, we enable new modes of behavior.  For example, my blog is now under source control, backed up in multiple locations, runs remotely and locally, and 
can be rebuilt from source in less than 1 second.  By composing the output of multiple programs in a sane architecture, I get isolation, graceful restarts, and hot deployment 
practically for free.  And best of all, my resource utilization has gone through the floor, and my server costs have dropped by about $40 per month.  While the three weeks
I spent working part time on this project may take years to pay off in terms of savings, the rewards of challenging my assumptions will pay off 1000 fold over the next few
years.
