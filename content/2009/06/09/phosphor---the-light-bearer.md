Phosphor - the Light Bearer
===========================

<p><a href="http://www.dloh.org">Phosphor</a> is a new Javascript development environment, written in Javascript, and runs in <a href="http://www.apple.com/safari/download/">Safari 4</a>.    It provides a direct manipulation model for editing Javascript objects using a multi-purpose text block.  It allows you to inspect and edit live Javascript objects. </p><br /><p>Phosphor uses Phos as its underlying object framework / display subsystem.  It also adds support for interactive Image, Movie, and Sound objects.  These objects are likely to be rolled back into the Phos system in future versions, and provide an easy means to rapidly prototype Javascript interfaces. </p><br /><h3>Future Direction</h3><br /><p>There is still some work left to do to package widgets up for sharing and embedding in webpages.  While Phos adds AJAX support to all of the objects, there is still some work necessary to make the json deserialization process properly reinitialize saved object state.  Once that is done, however, it will be possible to trade live objects across browsers and deploy static applications using Phosphor.</p><br /><p>The goal of this project is to create an interactive programming environment that is suitable for teaching children of all ages how to program.  It is loosely inspired by <a href="http://www.squeakland.org/">Squeak Etoys</a> and the of UI is based on the work of <a href="http://research.sun.com/self/papers/programming-as-experience.html">Randall Smith and David Ungar</a>.  Specifically, the concept that Javascript objects are represented as a collection of slots, and each slot is directly manipulable.  There is no need for creepy action at a distance, typical of the edit, compile, run cycle common to most development environments.</p><br /><h3>Getting the Code</h3><br /><p>You can either use the <a href="http://www.dloh.org/">current web app</a> or download the code from the source repository using git:</p><br /><blockquote><pre><br />          git clone git://github.com/cthulhuology/Phos.git<br /></pre></blockquote><br /><p>There are a few minor variations between the two code bases mostly to account for the changes required to run it on Google Apps.  The tutorial code has been removed from the version in git, as it isn&#39;t really applicable to everyday use.  If you wish to use Phosphor in your own applications, I recommend using the version stored in git.</p>