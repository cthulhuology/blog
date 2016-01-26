New Blog Engine
===============

So Ghost has been treating me poorly the last few weeks. The monitoring I have crashes the node service every few days. Once swap fills up, the site grinds to a halt and dies a horrible death. Occasionally the server even needs a reboot just to get SSH to work. 

So I have started writing a new blog server based on the original design for Jawas2. That idea was based on the practice of in ye olden days of serving CGI scripts from inetd.  To those young whippersnappers who were in short pants in those days, inetd is a generic server that hands off a TCP socket or UDP dgram to a regular UNIX process. The process then reads from stdin and writes it's response to stdout.  It really is quite simple, and makes it possible to turn any Unix style program into a server.

Many distros still ship <a href="https://github.com/xinetd-org/xinetd">xinetd</a> but the original website is gone, and development has largely stalled for the past 3 years.  Additionally, the code has not been updated to use any modern kernel functionality, and is still selecting on FD_SETs in a blocking fashion.  In general, the code base suffers from decades of ambition, and doing far too much.

 The original idea for the Jawas2 server was to convert what was a monolithic server into a series of servers what cooperated to generate a website.  The goals for the infrastructure were:

* process isolation - each client ran in their own process space
* multiple engines - each port could be serviced by a different engine
* non-blocking accept - port management would take advantage of epoll
* zombie handling - child processes would be reaped efficiently
* low overhead sockets - each child would own their own socket

The idea is there is one or more "central servers" which handle client connections, and then hand off all of the processing to separate child processes.  These child processes would be separate applications that did whatever they wanted with the data stream for each connection.  If one child process died, the central service would continue to be available, and all other children would remain unaffected.

This design flies in the face of the general trend in web server architecture.  Historically, inetd was replaced with dedicated servers like Apache, which provided a huge array of modules and features for building web applications.  Apache engineering went to great lengths to provide a M-N scheduling facility with pre-forked child processes for handling web requests.  This allowed you to spin up as many processing nodes as you had CPUs, and take full advantage of your multi-procesor systems.  This also allowed your LAMP application to share database connections, as many DBs were practically limited to <1000 concurrent connections.  This meant your thread pool would typically share a connection pool to the DB, avoiding the setup and teardown overhead on each request.

As time went on, the <a href="http://www.kegel.com/c10k.html">C10k</a> problem, sought to address the issue of having a limited number of cores each servicing a limited file descriptors.  Specifically, on most systems the maximum FD_SETSIZE is 1024, and with a listen backlog SOCONNMAX of 128, you could have no more than 1000ish clients connected to any one process (1152 max).  As a practical matter, that meant you could have #CPUs k users simultaneously connected to a given piece of hardware. A 8 core machine could only support about 8k users, and that assumes all of the requests are completed within the alloted cycle count.  Longer requests necessarily reduced this even further, and cleanup of resource could reduce practical concerns by an order of magnitude.

By about 2004, servers like nginx, jawas, and the like solved this problem by taking advantage of async I/O and kernel level events to service >10k simultaneous connects per server.  With being able to hold on to far more simultaneous connections, it was possible to only process client requests when there was data to be acted upon.  This allowed for the creation of many tiered web architectures where most of the processing could be done by lower levels of middleware.  Database connections were often handled by a second tier data access layer, which would manage the DB pool, and allow the frontends to serve more clients.  In distributed systems, the lower tiers could shard across multiple databases and data centers, making it impractical to block a client task on long running scatter/gather jobs.

Later servers like 2009's Nodejs, would go even further down the single process route, and use pthreads to simulate async I/O for lots of blocking system calls.  Thanks to the abuse of threads, node faked being async well enough that people started to think it actually was under the hood.  Node's inability to make use of multiple cores would ultimately be a huge step backwards for web server architecture.  As a result, node developers would ultimately end up reinventing the xinetd architecture poorly, making extensive abuse of the SO_REUSEADDR flag which would allow multiple processes to bind to the same port. As a result, it became typical for people to spin up multiple identical monolithic node apps all on the same machine, and then front them with a proxy or reverse-caching proxy like nginx or varnish.

Well it is 2016 now, and a lot of the assumptions we make when designing web scale architectures may not hold anymore.  Epoll and kqueue mean we no longer have an issue handling more than 1k concurrent connections per process.  Back when the Apache release 2.0.0 in 2002, the multi-threading support in MPM was still very new, and kernel level copy-on-write semantics were just a couple years old. Most web frameworks at the time could not take advantage of either. When nginx was designed, the plague of trying to get existing web apps to play nicely in a multi-client single process environment was a major topic of discussion. The design of subsequent high performance systems largely aped the design of the C10k winners, or require them as part of a complete stack.  With many databases providing their own RESTful interfaces, connection pools and limits are not a going concern, and the advantages of more monolithic frameworks aren't nearly as reasonable given their complexity and costs.

Rather than assume the world hasn't changed in the 12 years since I started on Jawas, I have decided to reevaluate the underlying assumptions. On a modern Linux, a fork + exec strategy should involve little more than a page table copy and possibly some link updates. If I can compile a static binary, there should be no link updates necessary and the COW semantics should make the clone + exec nearly free. Similarly, with kernel level events via epoll, the cost of blocking in the linux kernel scheduler should be minimal, and provide thread level responsiveness while maintaining strict isolation between clients.  Finally, as I'm not running this on a desktop operating system, like MacOS X with it's piddly 255 max procs, we should be able to keep many parallel clients around doing long running tasks like Keep-Alive connections and WebSockets, without worrying about fair scheduling of threads (and instead rely on the kernel to do that).

Never mind that most of the traffic my blog currently gets is my own monitoring scripts, but it should be able to handle the strain of serving largely static content as well as anything, and definitely better than the nodejs app it is running right now.







