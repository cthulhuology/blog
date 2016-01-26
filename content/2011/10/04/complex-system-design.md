Complex System Design
=====================

Here&#39;s a scary concept, let&#39;s design a complex system.  By complex I mean consists of many simple moving parts. Individually the components in the system may be trivial to implement. They may do little more than keep a running tally, pass data from point A to point B, or may transform an entire file. How this will differ from an application is that this complex system will consist of individual parts that may run as stand alone applications. It is more than Unix style design, it is a school od engineering that works for the material world as well. Any device made with off the shelf parts exhibits these basic characteristics. <br><br>Step 1.) what are the functional roles necessary to make our system work?<br><br>In general, our system wil:<ul><li>gather information</li><li>collect resources</li><li>catalogue those resources</li><li>measure resource consumption</li><li>mutate resources based on the gathered information</li><li>update status of progress</li><li>deliver final output</li></ul><br>This description will accurately model most systems we would want to build. The specific of each step aren&#39;t important, they only determine the scale to which we focus on any component. In general, the key problems we are trying to solve are managing a large workflow while accounting for the economic model that makes that work practical. It doesn&#39;t matter if we are gathering ore carrying it to a smelter and producing ingots, or generating personalized email spam, or rendering movies for a Hollywood film. Each of these systems will have the same basic set of requirements for the business of doing to to work. <br><br>Step 2.) What technologies can we bring to bear to address these issues:<ul><li>HTTP/1.1 w/ HTML5 to gather information from the operator</li><li>A collection of robots managed by a message queue to collect resources</li><li>A data store with a search interface to catalogue those resources</li><li>A database and a messaging bus to log all resource utilization</li><li>A collection of workers attached to a message queue to perform transformations</li><li>A message bus for the workers to publish status information & monitoring system</li><li>A distribution workers which shuffle work output to new data stores</li></ul><br>If you notice, we can reduce the number of distinct elements through repeated application of a message driven architecture:<ul><li>message bus with queue to manage communication</li><li>UI built on a networked infrastructure</li><li>data storage managed by search</li><li>bots that do all processing, heavy lifting, etc. </li></ul><br>This design is not accidental, it is how your body works. 