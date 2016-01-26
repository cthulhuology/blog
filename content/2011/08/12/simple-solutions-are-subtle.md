Simple Solutions are Subtle
===========================

These days it is hard to tell at first glance if something is "simple" or not:<br><br>  App.add(&#39;/foo&#39;, function(req,res,next) {<br>          res.send(&#39;bar&#39;);<br>  })<br><br>Simple right?  Request http://localhost/foo in your web browser and get back the word &#39;bar&#39;. What could be simpler?<br><br>Well looking at this we are dealing with a Sinatra style framework, which implies a path router of some kind. We are passing a first class function object as a parameter which may enclose state from the surrounding scope. We all know how scoping works right?  The language is also JavaScript probably running on NodeJS, which means our HTTP processing stack is async, and since we&#39;re running in a framework, probably getting important things handled for us like gzip compression by middleware. This means we are writing a layer on an onion. <br><br>NodeJS itself uses V8 which compiles C++ classes on the fly in order to just in time compile JavaScript to native code. This code runs in a memory sandbox, and communicates with the underlying OS through shims written in C++. These shims themselves are often calling into system libraries which abstract the underlying OS calls. Key to all this is a segmented proccess model where privileged code executes the necessary commands to the hardware independently of the user space program. <br><br>Drilling down we often find layers of virtual device drivers which abstract interfaces to actual devices. Some virtual devices such as the loopback network device have no hardware associated with them at all. When we connect to localhost, we use the sockets, transfer data between processes, but never really send any traffic over the net. <br><br>And that is just to get the 3 byte 1/2 way!<br><br>It is a simple example but actually much more complex than one might suspect. <br><br>Things worth remembering before saying some large scale distributed system is complex. 