The Grand Renaming
==================

Today&#39;s project was convert selfish.js to adhoc.js, and apply the <i>Grand Renaming</i> throughout.   The process used removed the old <i>let</i> function and replaced it with the <i>from</i> derivation.  Additionally, the variable assignments were replaced with <i>named</i> and <i>plural</i> function calls, which more clearly designate what happens.  Using these features Objects can now assign themselves a proper name.    What this means in practical terms, is that each object definition is technically a single statement.  For example consider:<br /><br /><blockquote><pre><br />An.object().named(&#39;Device&#39;).plural(&#39;Devices&#39;).from({<br />  dispatch: function(n,e) { <br />    App.widgets.every(function(w,i) { try { if (w.can(n)) w[n](Event.init(e)) } catch(e) {} });<br />    return this;<br />  }, <br />});<br /></pre></blockquote><br /><br />This is just one statement, that constructs a new object, with a names Device and Devices (the plural form), and derives from an object with a dispatch function, that takes a name of an event, and an event object, and applies it to every widget that can process the named event.  This is actually the dispatch loop of the entire environment.  <br /><br /><h3>Porting Territory</h3><br /><br />I&#39;m beginning to port the Smalltalk visualization tools developed for Squeak to the Phos/Adhoc.js environment.  The idea is the same, to create a circle for each object, and then display relevant data about the relationships between objects based on the contents of their methods.   For the time being, the base Territory widget is constructed for a given object using the following code:<br /><blockquote><pre><br />An.object().named(&#39;Territory&#39;).from(Circle, {<br />  init: function(x) { <br />    var target = x.name();<br />    return this.clone().copy({<br />      target:  target,<br />    }).radius(window[target].slots()).instance().here();<br />  },<br />});<br /></pre></blockquote><br /><br />What this does is create a new Territory object deriving from Circle, it then changes the initialization routine to set the radius to the number of slots in the  target object passed to the initialization routine, and returns an instance underneath the cursor.  To create a Territory for a Box object one could say:<br /><br /><blockquote><pre><br />A.territory(Box);<br /></pre></blockquote><br /><br />The primary advantage of these single line constructor sentences is it allows most object initialization code to be wrapped up in a simple string that can be directly evaluated to initiate a new core object.  The way that <i>named</i> works is it not only binds the global name of the object, but also registers a constructor function in the A and An objects.  This makes it possible to write your own archetypal objects and have them work as if they were core code.<br /><br /><h3>Using external code</h3><br /><br />One of the things I&#39;ve been doing in my own projects is using the adhoc.js method <i>use</i> to include other files at runtime from my local repository.  I&#39;ve been working on a book on programming, and have been developing interactive exercises.  Rather than merely read about how various parts of the computer work, you can directly manipulate simulations of the code.  For example, in the chapter discussing combinatorial logic, there is an example of how an OR gate works.  To instantiate an or gate the following code is used:<br /><blockquote><pre><br />use(&#39;book.js&#39;);<br />An.orgate();<br /></pre></blockquote><br /><br />This will create an or gate whose inputs can be clicked on to turn them on and off.    The gate fully supports drag and drop, and can easily be joined to other gates to produce any combination of circuits imaginable.  And the full simulation works in your web browser.  However, the really cool thing is that the gate is built up of a series of components stored in a number of different files.  So the code for it looks something like:<br /><br /><blockquote><pre><br />An.object().named(&#39;Gate&#39;).from(Component,{ ...  }).use(&#39;bit.js&#39;,&#39;connector.js&#39;)<br /></pre></blockquote><br /><br />So the files <i>bit.js</i> and <i>connector.js</i> are imported and the objects that they contain are used as components in the gate.  The individual Bit objects represent bits and can be toggled on and off, and the Connector objects represent wires which connect the bits that represent the gates inputs and outputs.  The gate also loads an image to represent the logic diagram symbol, which is read in using the Image object.  Everything can be interacted with, moved, and controlled using a mouse, and the wire traces are automatically routed by the wire objects.  Learning to build circuits using combinatorial logic couldn&#39;t be any more easy and fun!