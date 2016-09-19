Rethinking Software Services
============================

Over the past few months, I've been evaluating my usage of various software
services.  How do I actually use these platforms? What are my frustrations?
Do I really need them?  The services that I've looked at largely consist of:

* Google - search, mail, authenticator
* Rackspace - hosting
* Namecheap, Godaddy - DNS registrar
* Slack - chat
* Apple iTunes - music
* Netflix, Amazon - videos
* Steam - video games

Of these, my greatest pain points with the above are:

* search - constantly can't find things I know are there that I previously read
* mail - flood of email so great that I don't read it any more
* dns - too many registrars & SOAs
* music - too many files on too many devices, all redundant, poorly tagged

Most of these services can be replaced with local versions of them.  And 
considering my increasing pain points with some of them, I've started building
alternatives.

My Personal Search Engine
-------------------------

A number of years ago, I started working on a bookmark engine that would allow
me to download and index any sites I bookmarked.  The reasoning was if I found
it interesting enough to click a button, I would want to come back to it.  The
problem is that I have thousands of data sheets, PDFs, and images that I've 
downloaded over the decades that I literraly can't find anymore on my piles
of backup drives.  None of the existing indexing tools from Google, Apple, or
Microsoft help, and often they make the situation worse by consuming resources
without providing any value.

I am now revising the personal search engine, where in I will have a local 
service running which will download any page or pdf I bookmark, archive it,
and add it to my search index.  This way even when a site goes offline, I 
can still have a copy of the information, and if Google forgets about it,
I can still find it, without relying upon Archive.org to capture it.

And since I'm going to have my own search engine, I might as well provide an
API for friends to share my search results and theirs with me.  This approach
will allow for a "currated web" sort of like the early days of Yahoo, but
without the centralized servers.  A decentralized Google.

MTA, GPG, and Whitelisting service
----------------------------------

Now most of the email I need to read comes from my wife.  Basically, I get too
much email to read, and I need to cut down.  Even trying to sign off of all
of the mailing lists isn't working, as I have a few dozen email accounts which
have been in service for over a decade in some cases. So the easiest way to
fix this problem is to generate a giant whitelist of people from which
I want to see email from, and /dev/null the rest.

Now I'm never going to be able to teach my wife to PGP, and I can't expect
other people to do the same. But I can setup my MTA to encrypt all mail by
default.  If I run my own MTA, postfix + dovecot + gpg, I can add my white
lists to ensure the email I need to read get prioritized, that the email I 
may want to read gets flagged, and the rest just goes to /dev/null.  I can
also make sure that nothing remains in clear text on disk to avoid easy
access.

Finally, since I'm adding my own search engine, I can bookmark emails adding
them to my searchable archive and dump the ones I don't need.  This work flow
could be done in Google, but it is a real pain in the ass to do when you
can't download your email because their archive service times out.  And I 
can never implement the whitelist in Google and be certain it is working.


DynDNS, DNS servers, and Discovery
----------------------------------

This one is the simplest, in that I need to move all of my domains to a 
single registrar and have that registrar point at my own DNS servers.  
I already run multiple servers that can host a DNS server (and often do
for internal purposes).  I might as well just take ownership of this one.

Additionally, since I'm running my own DNS servers it is trivial to have
all of my machines update their external DNS in the public SOA file
using a simple IP reflection script.  It would be nice to also support
a .local DNS for my home networks using mDNS.  The DNS servers will also
help with managing the MX records for the MTA above, and the redirect 
server for the search sharing app above.

One thought that keeps banging about my head is it might be possible to
use the DNS server to kickstart another service serving as a public 
endpoing for a P2P discovery service.  A rather simple DNS server could
respond to queries for a subdomain with a list of random IP addresses for
public seed nodes. This would allow a simple getaddrbyname interface to
source a list of hosts from which you can discover online friends.  Ideally,
all of my friends would run their own DNS servers, so ultimately we'd
only need to know where our servers were.


Chat, Talk, Video, etc.
----------------------------------------------

I've really started hating Slack, having now used it at three companies
and on 5 different platforms (Windows, Linux, MacOS, iOS, Android).  
While it isn't going away from my daily life anytime soon (since my
customers use it), I'm leaning towards integrating Slack into my chat
service, rather than the other way round. 

I'm kinda tired of having multiple clients open all day for multiple
protocols and multiple services.  At any time I have 2 slack windows,
an IRC client, an XMPP client, and Skype open. On top of that my phone
has SMS, Facebook Messenger, Facetime and Signal beeping at me.   I would
consider adding more communication platforms but I have too many already.

What I'm looking to do here is unify all of my various notification
platforms and shove them into one of my own.  Ideally, I'd have one
client and have it talk to a locally hosted service which communicated
to all those shitty services.

I'd also like to integrate SIP and my own PBX setup for home. I've been
working on adding video cameras to the public areas, but would also like
to have an intercom functionality added.  Ideally, I'd like that tied
into my phone so that I can answer the door from anywhere.  If I can
have WebRTC / HLS video streaming all the better, because then I can also do
a video chat and video log playback on any of my devices.


Music and Video server
----------------------

The entertainment solution is one that I can pretty easily knock together
using off the shelf pieces.  I need to consolidate my media collection,
retag all of my files, and then just access my music collection via
streaming.  This is easy to do, and my client of choice is vlc.  A simple
UDP based server is enough to do most of what I want. I'll probably also 
add a DynDNS entry for my music and video servers so that I can access 
them remotely.  

Now the really cool idea here would be to support transperant caching and
streaming of Netflix, Amazon video, and HBO Now.  This would require a
bit of work, but basically it would involve making a custom audio sink
and a display driver that would stream screen buffer to a remote machine.
Remote controls can be done with a simple X input driver, and can work
via the X protocol directly. And if I can stream it I can spool it and
replay later.  Ideally, I'd use this setup to "pre-watch" all my videos
late at night, so they're locally cached.  This would help immensely
with the kids' video habits, where they watch the same PBS videos a dozen
times a week.


Steam
-----

Steam is it's own special place of pain and suffering.  I run SteamOS
as my laptop OS. I have a gaming laptop built for running Steam games
on Linux.  But I really want off the Debian train.   So I've begun
writing my own linux distro [http://xil.li/] so that I can run Steam
on something a little more sane.

This is a long term problem because SteamOS ships with a compositor
the depends upon libsystemd and as a result crashing far too frequently.
Also since systemd doesn't play nicely with my integrated graphics and
BIOS, I can't get suspend to work without patching the kernel and 
disabling SteamOS updates (as they'll break as well).  Finally, there
are some additional USB device drivers I'm working on that won't
play nicely without a custom kernel.  So SteamOS isn't a good fit
long term as I need more control over my machine without someone else
shoving updates down my throat.

This proccess has had me rethinking the whole software stack.  What
do I actually need to be productive.  How much software can I just ditch
and not miss?  This is probably the most exciting thought, that one
could build from scratch a computing environment which does just what
one needs to do.


Going Offline
-------------

The beauty of this project is that when I succeed, I will be able to
go offline.  While I'll always have to have a couple servers hosted
somewhere with a static public IP, I should be only dependent on my
ISP.  By taking control of the input coming into my systems, I can
also hopefully reduce the noise that distracts from actually getting
things done.  And by taking over the management of the full stack,
I can be fairly certain if it can be fixed, I can fix it.

And in the long term, that is a much healthier world to live in. It
became far too easy to delegate responsiblity for too much of my
digital life to external entities who don't have my best interests
at heart.  It has also become a massive pain in the ass to manage
my digital life over the ever changing morass of online services
I don't really need.

Once these projects reach a state of "done-ness" I will be releasing
them as Open Source Software.  And if you'd like to take control
of your own digital future, you're more than welcome to join me.
