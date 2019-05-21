
instructions:
	@echo "Examine the 'install' rule in this Makefile first."
	@echo "If it is not destructive, run 'make install'."
	@echo Then see README.md for the remaining steps.

install: apt-install icons 
	install --mode=644 Xresources $(HOME)/.Xresources
	install --mode=644 pirixrc $(HOME)/.pirixrc
	install --mode=644 mwmrc $(HOME)/.mwmrc
	install -d $(HOME)/.config/pirix/icons
	install --mode=644 src/icons/*.xpm $(HOME)/.config/pirix/icons
	install --mode=644 src/wallpaper/desktop.jpg $(HOME)/Pictures/pirix

	
# Operating system packages

apt-install:
	sudo apt install \
	mwm libmotif-dev motif-clients \
	xosview xfonts-100dpi xfonts-75dpi x11-apps \
	freeglut3-dev rxvt-unicode firefox-esr nedit xloadimage


# Desktop configuration

icons:
	make -C src/icons


# OpenGL Demos
# Does one need glut-3.6 for these?

demos: src/demo/atlantis/atlantis src/demo/ideas/ideas src/demo/glutmech/glutmech
src/demo/atlantis/atlantis:
	cd src/demo/atlantis && make
src/demo/ideas/ideas:
	cd src/demo/ideas && make
src/demo/glutmech/glutmech:
	cd src/demo/glutmech && make


clean:
	cd src/icons && make clean
	cd src/demo/atlantis && make clean
	cd src/demo/ideas && make clean
	cd src/demo/glutmech && make clean


.PHONY: instructions install icons apt-install demos

