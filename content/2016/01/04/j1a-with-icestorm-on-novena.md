J1a with Icestorm on Novena
===========================

Today I had the pleasure of getting to a milestone I've long looked forward to.  I managed to get [SwapForth](https://github.com/jamesbowman/swapforth) running on an [J1A CPU core](http://excamera.com/sphinx/article-j1a-swapforth.html#j1aswapforth) programed with an open source tool chain [Project IceStorm](http://www.clifford.at/icestorm/) on an open hardware laptop the [Novena](https://www.crowdsupply.com/sutajio-kosagi/novena).  This was the first time I got to run open source software on an open cpu architrecture using open source tools on open source hardware.

<iframe width="560" height="315" src="https://www.youtube.com/embed/hsTqjghq7eM" frameborder="0" allowfullscreen></iframe>

The next step is I would like to make some modifications to the J1A architecture and build a smaller version of the [ICEd](https://hackaday.io/project/6636-iced-an-arduino-style-board-with-ice-fpga) board to a formfactor closer to that of the [Adafruit Trinket](https://www.adafruit.com/category/261).  I like the idea of the ESP8266 wifi controller attached, but I have yet to get the build environment running on the Novena.

What excites me about this development is that it is becoming increasingly possible to run a full stack on open source hardware and software.  I'm running OpenWRT routers at home, a RaspberryPi cluster, and piles of random software.  Being able to realize my ideas in FPGA form, also allows me to experiment with new design concepts it would have been prohibitively expensive to explore.  I am happy to stand on the sholder of giants like:

* James Bowman (j1a & swapforth)
* Clifford Wolf and Mathias Lasser (project icestorm)
* Bunnie Huang and Sean Cross (novena)

