prefix := /opt/pirix

install: install-rc install-icons
	sudo install -d $(prefix)
	sudo chgrp -R $(USER) $(prefix)
	sudo install -d $(prefix)/wallpaper
	sudo install -m 644 wallpaper/desktop*.jpg $(prefix)/wallpaper

install-rc:
	sudo install -d $(prefix)
	sudo install -m 644 Xresources $(prefix)/Xresources
	sudo install -m 644 pirixrc $(prefix)/pirixrc
	sudo install -m 644 mwmrc $(prefix)/mwmrc

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
