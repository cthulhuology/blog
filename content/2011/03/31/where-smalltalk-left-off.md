Where Smalltalk Left Off
========================

This is just a little thought experiment. What if Smalltalk were invented 10 years from now, what would it have looked like?<br><br>Well currently there are several companies with 256+ ARM cores per die chips heading to market, so we could assume in 10 years time chips would reasonably contain between 2^10 and 2^20 cores. As a result, we could reasonably assume a process model where each object gets it&#39;s own core, memory, and stack. A message send would travel over a bus, and would be limited by the speed of the interconnects. Since each object was opaque to the user, these messages could as easily travel over the network as across the chip interconnects or on the system bus. <br><br>Each object would also have a universally unique address, so that each process could be referenced and messaged anywhere in the system. This would necessitate the ability to gracefully ignore and verify the sender of the message, which could be accelerated at the hardware layer as the messaging bus could be encoded on the wire. Security would be hard coded into the network of objects, allowing organizations to share hardware without worrying about whose code is running on adjacent nodes. <br><br>Furthermore, garbage collection, persistence, and global namespaces would be anachronisms. An object would persist by being saved to off chip RAM, which would amount to sending a message containing the state of the CPU and it&#39;s attached ram to another Object on the network. This sort of problem, where sharing CPUs between objects is simply not cost effective, and messaging to swarms of logically identical objects would be used to persist data in an eventually consistent model for all applications. Since each object is encapsulating state, the messaging protocol would contain versioning information much like git, or Riak, or Couchdb, or any other system designed for concurrency, distribution, and eventual conflict resolution. <br><br>Since each object would be universally addressible, applications could migrate across swarms of CPUs like herds on the savanah. Rather than VPS computing cores could float their state to remote nodes following the cheapest utility costs. Migrating applications in this fashion will necessitate all message passing be fully asynchronous. The return operator would not alter a nested context stack but rather pass a message to the sender of the current message. This means stack traces, tail calls, and all sorts of optimizations would be unnecessary. In fact the entire model would look more like Erlang than current Smalltalk implementations. <br><br>Finally, since core are cheap hardware peripherals would be directly driven by general purpose CPUs, each of which would also be a networked object encapsulating hardware state. The net result being these machines would need no operating system, merely a set of standards and well defined messages. Further divorcing where computing occurs from where it is accessed and displayed. <br><br>Or I could be wrong. 