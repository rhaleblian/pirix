
instructions:
	@echo "Examine the 'install' rule in src/Makefile first."
	@echo
	@echo Files are installed to '$(HOME)/.config/pirix'
	@echo and a symlink is made at $(HOME)/.mwmrc .
	@echo
	@echo "If that is not destructive, run 'make install'."
	@echo Then see README.md for the remaining steps.

install:
	make -C src install

