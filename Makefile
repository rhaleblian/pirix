
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

pirix: deb images
	install --mode=644 Xresources $(HOME)/.Xresources
	install --mode=644 pirixrc $(HOME)/.pirixrc
	install --mode=644 mwmrc $(HOME)/.mwmrc

images:
	make -C src/icons
	install -d $(HOME)/Pictures/pirix/icons
	install --mode=644 src/icons/*.xpm $(HOME)/Pictures/pirix/icons
	install --mode=644 src/wallpaper/desktop.jpg $(HOME)/Pictures/pirix


# OpenGL Demos
# Does one need glut-3.6 for these?

src/demo/atlantis/atlantis:
	cd src/demo/atlantis && make
src/demo/ideas/ideas:
	cd src/demo/ideas && make
src/demo/glutmech/glutmech:
	cd src/demo/glutmech && make
src/demos: src/demo/atlantis/atlantis src/demo/ideas/ideas src/demo/glutmech/glutmech


.PHONY: instructions pirix nedit deb demos
