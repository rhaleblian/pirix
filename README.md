# pirix
PIRIX is an emulation of SGI's IRIX desktop environment on Raspberry Pi 3.

[http://github.com/rhaleblian/pirix/blob/master/screenshot0.png]

Besides being nostalgic, this desktop enviroment is fast and easy on Pi resources.

## Installation

Examine the 'pirix' Make rule and confirm it won't whack any file you want to keep:

    cat Makefile

If it's safe, invoke the rule via 'make pirix'.

To start PIRIX via startx, put this in your $(HOME)/.xinitrc :

    . /home/pi/.pirixrc
    pirix

and run

    startx

## Goodies
If you want the atlantis demo,

    cd src/demo/atlantis
    make
    ./atlantis

Follow the same pattern for the ideas and glutmech demos.

## Notes
SGI's Indigo Magic Desktop and Interactive Desktop were derivations from the Motif Window Manager;
accordingly, this tweak bases itself on mwm.

A lot of things aren't here, including
* the toolchest
* the file manager 
* a contemporary web browser (Netscape or NCSA Mosaic)

## TODO
* somebody write a toolchest replacement
* add icon images for terminal, emacs, etc

## Credits
* IRIX - Silicon Graphics Computer Systems
* Motif - The Open Group
* GL Demos - opengl.org

