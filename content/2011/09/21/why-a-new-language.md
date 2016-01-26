Why A New Language
==================

A friend of mine, this weekend while examining <a href=greenarrays.com>a new Green Arrays dev board</a> with 288 cores, asked me why I spent so much time abusing other languages and didn&#39;t just implement my own. Now part of the inspiration for this question as the board sitting in front of us. Chuck Moore has not only designed the programming language, wrote his own CAD system, he also designed the chips as well. The question of could a skilled practitioner of the art build the full thing himself?  The answer was undeniably yes (assuming he had access to a fab facility and could afford the wafer runs). <br><br>My answer to his question was that I was more interested in establishing the techniques necessary to program the types of systems, so if I could bend any existing language to my will, it was a short jump to running my code anywhere. Moreover, each experiment would allow me to better understand the problem space, and remove barriers to thinking by forcing myself to overcome orher&#39;s implicit assumptions.   That being said, I still have a good idea of what my preferred language would look like:<ul><li>it would have words and numbers and punctuations</li><li>a word would be [A-Za-z][A-Za-z]*</li><li>a number would be [0-9]</li><li>and punctuation would be all other printable character combinations, usually . , ? ! &#39; " - : ; —</li><li>Objects may have Proper Names and those Names start with a Capital Letter</li><li>Object proper names may consist of more than one word like David Goehrig</li><li>indefinite articles a and an may be placed in front of a proper name to refer to the category of object</li><li>a categorical Refernce may also include adjectival guards to narrow the subset, a green Book, a categorical Reference</li><li>the definite the may be placed infront of a proper name to refer to the categorical example, the Good, the State, the President</li><li>additional categorical logic words like all, none, no, some, one, can be used to operate upon sets of objects, all good Children goto Bed</li><li>all words and punctuation are message sends</li><li>each message send occurs in the current context, and is sent to the noun of last address</li><li>new context can be created by referring to more objects</li><li>each object resides in it&#39;s own context and communicate only with its neighbors (objects it can refer to by name or category)</li><li>an object in it&#39;s time may play many parts, and may change it&#39;s category repeatedly</li><li>no object may violate the space of any other object</li><li>objects communicate only via message passing</li></ul><br>And that&#39;s about it. <br><br>