# pirix
Emulation of SGI's IRIX desktop environment on Raspberry Pi.

## Installation

    sudo apt install mwm libmotif-dev motif-clients
   
Examine the 'install' Make rule and confirm it won't whack any file you want to keep.

    cat Makefile

If it's safe, invoke the install rule.

## Notes
SGI's Indigo Magic Desktop and Interactive Desktop were derivations from the Motif Window Manager;
this tweak bases itself on mwm.

A lot of things aren't here, including the file manager and the web browser.

## TODO
* add icon images for terminal, emacs, etc
