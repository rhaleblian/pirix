
instructions:
	@echo "Examine the 'install' rule in src/Makefile first."
	@echo
	@echo Files are installed to '$(HOME)/.config/pirix'
	@echo and $(HOME)/.mwmrc .
	@echo
	@echo "If that is not non-destructive, run 'make install'."
	@echo Then see README.md for the remaining steps.

# Operating system packages

debian:
	apt install \
	mwm libmotif-dev motif-clients \
	xosview xfonts-100dpi xfonts-75dpi x11-apps \
	freeglut3-dev rxvt-unicode firefox-esr nedit xloadimage \
	imagemagick


install:
	make -C src install

