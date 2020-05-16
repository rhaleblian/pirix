# pirix

piRIX is an emulation of SGI's IRIX desktop environment on Raspberry Pi 3.

![screenshot](etc/screenshot0.png)
![screenshot](etc/screenshot1.png)

Besides being nostalgic, this desktop enviroment is fast and easy on Pi resources.


## Installation

Files will be installed to

    .config/pirix
    .mwmrc

in your home directory. To install:

     make install

Put this in your $HOME/.xinitrc :

    . $HOME/.config/pirix/pirixrc
    pirix

Finally, run

    startx


## Goodies

If you want the atlantis demo,

    cd src/demo/atlantis
    make
    ./atlantis

Follow the same pattern for the ideas and glutmech demos.

On a Pi 3B running Raspbian Buster, the GL demos run too fast! :D


## Notes

SGI's Indigo Magic Desktop and Interactive Desktop were derivations
from the Motif Window Manager; accordingly, this tweak bases itself on mwm.

A lot of things aren't here, including
* styling modifications to MWM (those rounded windows and scrollbars)
* the toolchest (i think you could write an Xm app of buttons with menus
  and no frame)
* the file manager (remember that they drew scalable vector icons)
* a contemporary web browser (Netscape Navigator or NCSA Mosaic)

Firefox is the defined browser, in the spirit of being a successor
to Navigator.


## TODO

* somebody write a toolchest replacement
* there's a starting point for a file manager at src/pirix/filemanager
* add icon images for more applications
* other omissions mentioned in the notes you may have just read


## Credits

* IRIX - Silicon Graphics Computer Systems
* Motif - The Open Group
* GL Demos - opengl.org
