
instructions:
	@echo "Examine the 'install' rule in src/Makefile first."
	@echo
	@echo Files are installed to '$(HOME)/.config/pirix' .
	@echo IMPORTANT: installation overwrites any previous edits!
	@echo
	@echo "If that is non-destructive, run 'make install'."
	@echo Then see README.md for the remaining steps.

install:
	make -C src install

# Operating system packages.

install-debian-prerequisites:
	apt install \
	mwm libmotif-dev motif-clients \
	xosview xfonts-100dpi xfonts-75dpi x11-apps \
	freeglut3-dev rxvt-unicode firefox-esr nedit xloadimage \
	imagemagick
	
demos:
	make -C src/demo/atlantis
	make -C src/demo/ideas
	make -C src/demo/gears
