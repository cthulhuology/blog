Design to scale
===============

There is this common misconception that a users machine is slow. We assume for some reason that a typical desktop is anemic even by year 2000 standards, and fall into a falacy that as more and more people access the web via smart phones, that this trend will continue. <br /><br />That said, the iPad and Samsung Galaxy Tab both have twice the CPU, RAM, and the same storage as a ca. 2000 iMac. More to the point, a $300 net book typically has more horsepower than those to "mobile" devices. Smart phones will soon contain multicore ARM processors, and are already powering the next wave of Android tablets. <br /><br />When combined with the typical 3-5yr life span of devices, we are looking at a very different baseline for 2015 than we were in 2005. Mobile devices currently are more capable, have better networking, and significantly more utility than our desktops did 5 years ago. And these trends are accelerating. <br /><br />The best way to design for this future is to design to scale, by which I mean to design each layer of you application to take advantage of the differences in scale between the components in the architecture. Leverage the fact that your clients are more powerful by offloading work to the client that is only done for that client. Leverage static caches by moving your data as close to the edge of the cloud as possible, by publishing data not rendering it. Shift your processing tasks to an application tier that exploits high speed backplanes and minimizes you datacenter footprint. And keep your databases out of the front office, and leave them for reporting and back office tasks. <br /><br />Server tech is following the path of least resistance to multi-thousand core low power CPUs. At the same time a number of OTP compliant special purpose software platforms are gaining acceptance in industry. Erlang&#39;s message passing model is highly compatible with Ajax and fits into the best OO tradition of Smalltalk. <br /><br />From a software perspective we have the tools and models necessary to program these systems. We just need to change our perspective to see the patterns at the right scale