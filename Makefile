
instructions:
	@echo "Examine the 'pirix' rule in this Makefile first."
	@echo "If it is not destructive, run 'make pirix'."
	@echo Then see README.md for the remaining steps.


# Operating system packages

deb:
	sudo apt install \
	mwm libmotif-dev motif-clients \
	xosview xfonts-100dpi xfonts-75dpi x11-apps \
	freeglut3-dev rxvt-unicode firefox-esr nedit xloadimage


# Desktop configuration

pirix: deb
	install -d $(HOME)/Pictures/pirix/icons
	install --mode=644 Xresources $(HOME)/.Xresources
	install --mode=644 pirixrc $(HOME)/.pirixrc
	install --mode=644 mwmrc $(HOME)/.mwmrc
	install --mode=644 desktop.jpg $(HOME)/Pictures/pirix
	install --mode=644 icons/* $(HOME)/Pictures/pirix/icons


# NEdit

build/nedit:
	- mkdir build
	git clone https://git.code.sf.net/p/nedit/git build/nedit

build/nedit/source/nedit: build/nedit
	cd build/nedit && make linux

nedit: build/nedit/source/nedit


# OpenGL Demos

demo/atlantis/atlantis:
	cd demo/atlantis && make
demo/ideas/ideas:
	cd demo/ideas && make
demo/glutmech/glutmech:
	cd demo/glutmech && make
demos: demo/atlantis/atlantis demo/ideas/ideas demo/glutmech/glutmech


.PHONY: instructions pirix nedit deb demos
