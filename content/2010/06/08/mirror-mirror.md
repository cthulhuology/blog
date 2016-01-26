Mirror mirror
=============

<b>NB: The current version is now live as a Google AppEngine webapp located at: <a href="http://www.dloh.org">http://www.dloh.org</a> </b><br /><br />I&#39;ve been playing around with improving the <i>mirror</i> capabilities of <a href="http://github.com/cthulhuology/Phos/">Phos</a> and have put together a little demo suggested by Randy Smith as follows:<br /><br /><object width="640" height="480"><param name="movie" value="http://www.youtube.com/v/4qrCgerCDG8&hl=en_US&fs=1&"></param><param name="allowFullScreen" value="true"></param><param name="allowscriptaccess" value="always"></param><embed src="http://www.youtube.com/v/4qrCgerCDG8&hl=en_US&fs=1&" type="application/x-shockwave-flash" allowscriptaccess="always" allowfullscreen="true" width="640" height="480"></embed></object><br /><br />The basic concept here is modifying a text <i>Block</i> element by dropping other <i>Block</i> objects onto the original <i>Block</i>&#39;s <i>Mirror</i>.  To obtain the <i>Mirror</i> instance, we simply call <b>mirror()</b> on any object.  Once we have that entity, we can dynamically alter any property of the object by performing operations on its mirror that would be outside of the behavior of the object itself.<br /><br /><a href="http://bracha.org/mirrors.pdf">Gilad Bracha and David Ungar</a> wrote a paper not to long ago about the need for encapsulating the meta-programming level stuff, and when you actually use a system with live objects this requirement becomes self evident.  For example, once can not easily just "add a feature" to an object by dropping a feature object onto it, as the default behavior for most objects will be "respond to that message".  If you provide a message for "add a feature", quickly everything becomes a meta-level problem.  <br /><br />I went down this route initially and end up with an object understanding "application stuff" and also understanding "programming stuff", which was the original <i>Block</i>.  The new <i>Block</i> vs. <i>Mirror</i> structure, made meta-programming on the block easier, and reduce the Mirror to a collection of Blocks, which knew how to operate on generic objects.  While I&#39;m still not happy with the current <i>Mirror</i> object, it will ultimately become an organizing structure like a Tree or an Array.<br /><br />Back to Bracha & Ungar&#39;s paper.... In it they define 4 terms of art:<br /><ol><br /><li>. Introspection. The ability of a program to examine its own structure.</li><br /><li>. Self-modification. The ability of a program to change its own structure.</li><br /><li>. Execution of dynamically generated code. The ability to execute program fragments that are not statically known. This is a special case of 2.</li><br /><li>. Intercession. The ability to modify the semantics of the underlying programming language from within the language itself</li><br /></ol><br /><br />Currently  the Phos environment supports Introspection largely through <i>Mirrors</i>, Self-modification through <i>Blocks + Mirrors</i>, and execution of dynamically generated code through <i>Block</i> <b>value()</b> and a new style eval that I&#39;m calling a <i>Selection Eval</i> as per this video:<br /><br /><object width="640" height="480"><param name="movie" value="http://www.youtube.com/v/juJhWtRN9ws&hl=en_US&fs=1&"></param><param name="allowFullScreen" value="true"></param><param name="allowscriptaccess" value="always"></param><embed src="http://www.youtube.com/v/juJhWtRN9ws&hl=en_US&fs=1&" type="application/x-shockwave-flash" allowscriptaccess="always" allowfullscreen="true" width="640" height="480"></embed></object><br /><br />In the not too distant future, I plan on support some additional layers of <i>Intercession</i>, mostly to ease the job of programmers when typing in behavior definitions in <i>Block</i>s.  The underlying programming language itself is significantly less important when you have objects that are directly manipulable and respond to messages.  If one could easily use objects for property names, there would be little preventing methods from being named by icons.  One could then send a message to an object to invoke a method by dropping, clicking, or hovering over an icon just as easily as passing a block with a function name.  Obviously, things like code comments mean very little when you have live objects which can pop-up their own tool tips!   And do you really need to type <i>function () { </i> over and over again, if you could just populate a different color block?