On word smithing
================

Part of what separates a good program from a mediocre one is the words the programmer selects to express the concepts contained within the code.  Consider the following two examples of PostScript™ code:<div><br /></div><div><blockquote>/frobinate { dup /foo get exch /bar get } def</blockquote><br /><blockquote>/at { dup /x get exch /y get } def</blockquote></div>Now both can be though of doing the exact same thing.  Each takes a dictionary on the top of the stack and returns the values associated with two keys.  Both work exactly the same way, the only difference is the choice of names used to convey meaning to other programmers.  To the computer it makes no difference if the key is called <b>foo</b>  or <b>x</b>. Neither have any particular import to the computer.  Similarly, <b>frobinate</b> is as good a word as any, when dealing with meaningless qualities like <b>foo</b> and <b>bar</b>.  <div><div></div><div><span class="Apple-style-span"  style="font-size:6;"><span class="Apple-style-span"  style="font-size:24px;"><br /></span></span></div><div><span class="Apple-style-span"  style="font-size:x-large;">The Semantic Gap</span></div><div><span class="Apple-style-span"  style="font-size:6;"><span class="Apple-style-span"  style="font-size:24px;"><br /></span></span></div><div></div><div><span class="Apple-style-span"  style="font-size:medium;">This example illustrates how the observer&#39;s preconceptions influence the meanings of the words chosen.  Structurally, these two statements were identical, performing the same operations with the same types of values in the exact same order.   Semantically, however, the second example more clearly expresses the programmer&#39;s intentions and the likely usage of these routines.  For example, we could define a class of dictionaries that all respond to our procedure <b>at</b> as all dictionaries which posses the keys <b>x </b>and <b>y:</b></span></div><div><blockquote>/is { true exch { 2 index exch known and } forall } def</blockquote><blockquote>/locatable [ /x /y ] def</blockquote><blockquote>/scalable [ /width /height ] def</blockquote>In this code segment we define a routine <b>is</b> which will test to see if each of the keys in an array passed on the top of the stack exist within the dictionary which is next on the stack.  So say we define a dictionary <b>B</b><b>ox</b> which is both <b>l</b><b>ocatable</b> and <b>s</b><b>calable</b>:</div><div><blockquote>/Box << /x 100 /y 200 /width 30 /height 40 >> def</blockquote>Not only will these routines work for our dictionary <b>B</b><b>ox</b> it will work with any dictionary which has these keys. For example, all <b>l</b><b>ocatable</b> elements could be <b>moved</b>:</div><div><br /></div><div><blockquote>/to { 2 index exch /y exch put /x exch put } def</blockquote><br /></div></div><br />This will allow us to make sensible statements such as:<br /><blockquote>Box locatable is { 400 300 to } if</blockquote>While it may read like Ciceronian Latin, it clearly mimics the semantics of the English sentence:<div><br /></div><div><blockquote>If the box is locatable, move the box to coordinate (400,300).</blockquote>Syntactically there are are differences between what we would like to say, and what we can easily say in PostScript™, but semantically the gap can be kept incredibly narrow.  What makes all the difference is our choice of words, and the manner in which we structure our idioms.  These same techniques can be applied to other languages as well, bringing what you wish to say in English into harmony with what the language designers allowed.</div><div><br /></div><div><span class="Apple-style-span"  style="font-size:x-large;">A Different View of Classes</span></div><div><br /></div><div>In the previous example, I demonstrated what could be considered object oriented style programming in PostScript™.   Rather than using a traditional concept of <i>class,</i> I used a concept similar to <i>traits</i> as found in <i>Self</i> and <i>Smalltalk</i>.  If you are familiar with protocols in <i>Objective-C</i> or interfaces in <i>Java, </i> those concepts are similar as well.  This style of <i>classiness</i> is particularly useful for languages that heavily use associative datatypes: <i>dictionaries, hashes, assoc-lists, </i>in order to represent <i>objects.</i>  By checking to see if an entity has the correct properties at runtime, and applying logic based on the results of the test, you can effectively manage polymorphism in ways where traditional class hierarchies quickly break down.</div><div><br /></div><div><i>Javascript</i> programmers man make particularly strong use of this approach, as all objects in <i>Javascript</i> are <i>Self</i> style key-value slot based objects.  Rather than manipulating a long prototype chain, inheritance can be done with a direct slot copy methodology.  And since protocol chain inheritance can quickly become opaque, through use of anonymous functions, implementing the <b>is</b> function in <i>Javascript</i> as a property of the <i>Object.prototype </i>object can make all of your objects <i>classy</i>.</div>