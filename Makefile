
instructions:
	@echo "Examine the 'install' rule in src/Makefile first."
	@echo
	@echo Files are installed to '$(HOME)/.config/pirix'
	@echo and $(HOME)/.mwmrc .
	@echo
	@echo "If that is not non-destructive, run 'make install'."
	@echo Then see README.md for the remaining steps.

debian:
	apt install urxvt xosview mwm imagemagick x11-apps

install:
	make -C src install

