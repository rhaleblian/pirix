
instructions:
	@echo "Examine the 'pirix' rule in this Makefile first."
	@echo "If it is not destructive, run 'make pirix'."
	@echo Then see README.md for the remaining steps.

pirix:
	install --mode=644 Xresources $(HOME)/.Xresources
	install --mode=644 pirixrc $(HOME)/.pirixrc
	install --mode=644 mwmrc $(HOME)/.mwmrc
	install --mode=644 pirix-desktop.jpg $(HOME)/Pictures


.PHONY: instructions pirix
