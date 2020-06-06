
instructions:
	@echo "Examine the 'install' rule in this Makefile first."
	@echo "If it is not destructive, run 'make install'."
	@echo Then see README.md for the remaining steps.

install: install-rc install-icons
	install -d $(HOME)/.config/pirix/wallpaper
	install --mode=644 wallpaper/desktop*.jpg $(HOME)/.config/pirix/wallpaper

install-rc:
	install -d $(HOME)/.config/pirix
	install --mode=644 Xresources $(HOME)/.config/pirix/Xresources
	install --mode=644 pirixrc $(HOME)/.config/pirix/pirixrc
	install --mode=644 mwmrc $(HOME)/.mwmrc

install-icons:
	make -C icons install

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
