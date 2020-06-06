
instructions:
	@echo "Examine the 'install' rule in this Makefile first."
	@echo "If it is not destructive, run 'make install'."
	@echo Then see README.md for the remaining steps.

install: install-rc install-icons
	install -d $(DESTDIR)/share
	install --mode=644 wallpaper/desktop*.jpg $(DESTDIR)/share

install-rc:
	install -d $(DESTDIR)/etc
	install --mode=644 --target-directory $(DESTDIR)/etc Xresources pirixrc mwmrc

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
