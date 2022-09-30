# piRIX

piRIX is an emulation of SGI's IRIX Interactive Desktop on Raspberry Pi 3/4
(and some other platforms).

![screenshot](etc/screenshot2.png)
![screenshot](etc/screenshot1.png)
![screenshot](etc/screenshot0.png)

Besides being nostalgic, this desktop environment is fast and easy on Pi 
resources.


## Installation

On Debian distributions, you'll need a few packages first. Run

    sudo make install-debian-prerequisites

Look at `Makefile` for specifics on what OS packages are being installed.

As usual, Fedora distributions will use different names for these packages.

Then install:

    make install

Put this in your `$HOME/.xinitrc` or `$HOME/.xsession` file:

    . $HOME/.config/pirix/pirixrc
    pirix

If you're booting directly to PIXEL Desktop, change your boot setting
with `raspi-config` to drop into a shell. Then run

    startx

We mentioned `.xsession` because some remote desktop mechanisms
and display managers like `xrdp` will use that file instead.
Salient if you, say, want piRIX to be available from your login screen.


## What gets installed?

Files will be installed to

    $HOME/.config/pirix

NOTE! Any changes you may have made to files already here will be
overwritten!


## How do I uninstall this?

    rm -r $HOME/.config/pirix

and undo anything you did to `$HOME/.xinitrc`.


## Where is the Toolchest?

There ain't none.
Find a compromise by pressing your left mouse button
over the desktop root window.


## Goodies

If you want the atlantis demo,

    cd src/demo/atlantis
    make install

The executable will in be that directory.
Follow the same pattern for any of the other demos.
The Toolchest (well, the thing that must serve for it)
has menu items to launch them, provided you put the executable
in your search path.


## Does this hackamadoodle only work on the Pi?

Actually it ought to work in many other Linux contexts, like clan Debian
or clan Fedora.  There have been minor problems with OpenBSD but we hear
it still works.  @rhaleblian even got it working in WSL2 and X410.

This hackamadoodle really just sets resources for `mwm` so that you get
that particular CDE-like feeling.
So if your whatever-NIX has `mwm` you're mostly there.

If you get it working in macOS, post about that.


## Notes

SGI's Indigo Magic Desktop and Interactive Desktop seem to bear similaries
to CDE and Motif, being a derivation;
accordingly, this tweak bases itself on `mwm` at el.

A lot of things aren't here, including
* styling modifications to Motif (those rounded windows and scrollbars)
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
