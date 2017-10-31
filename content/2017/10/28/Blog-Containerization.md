Blog Containerization
---------------------

Today I decided to containerize the blog server, and move it to AWS ECS.  The core of my blog engine is a custom C page engine, server, and monitor.  There is also a markdown parser/generator that generates the static site files.  As such, the prior deployment methodology was to build it locally, test the view, and then rsync to the production server.  This had some nice properties:

* The site build was static and could be run read only
* The webserver was statically compiled, and ran on multiple linuxes without dependencies
* The hosted solution was inexpensive to run

So why would I change it?  Well when I started my blog, my development environment was a Linux server in Rackspace (programmed on an iPad mini).  But as time went on, I started developing it on Mac OS X, and then switch to Ubuntu, Debian, and now Slackware.   Rather than worry about what the blog is running on in the production environment, I've decided to standardize on Slackware throughout.

[https://hub.docker.com/r/vbatts/slackware/|Vincent Batts] did the heavy lifting to make a Slackware Docker image.  I used this as the basis for my blog service container.  It is pretty light weight, and as I am running 14.2 on all of my local development boxes, porting software is easy.  The final addition to the Makefile added creating the docker container and pushing it to the repository in AWS.  Building the contianer, tagging, and pushing means that I can test the image locally before applying the changes to production, and be fairly certain I will get the same user experince.


