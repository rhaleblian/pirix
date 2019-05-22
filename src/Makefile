
instructions:
	@echo "Examine the 'install' rule in this Makefile first."
	@echo "If it is not destructive, run 'make install'."
	@echo Then see README.md for the remaining steps.

install: apt-install icons
	install --mode=644 Xresources $(HOME)/.Xresources
	install --mode=644 pirixrc $(HOME)/.pirixrc
	install --mode=644 mwmrc $(HOME)/.mwmrc
	install -d $(HOME)/.config/pirix/icons
	install --mode=644 icons/*.xpm $(HOME)/.config/pirix/icons
	install --mode=644 wallpaper/desktop.jpg $(HOME)/Pictures/pirix


# Operating system packages

apt-install:
	sudo apt install \
	mwm libmotif-dev motif-clients \
	xosview xfonts-100dpi xfonts-75dpi x11-apps \
	freeglut3-dev rxvt-unicode firefox-esr nedit xloadimage


# Desktop configuration

icons:
	make -C icons


# OpenGL Demos

demos: demo/atlantis/atlantis demo/ideas/ideas demo/glutmech/glutmech
demo/atlantis/atlantis:
	cd demo/atlantis && make
demo/ideas/ideas:
	cd demo/ideas && make
demo/glutmech/glutmech:
	cd demo/glutmech && make


clean:
	cd icons && make clean
	cd demo/atlantis && make clean
	cd demo/ideas && make clean
	cd demo/glutmech && make clean


.PHONY: instructions install icons apt-install demos
