install: install-rc install-icons
	install -d $(HOME)/.config/pirix/wallpaper
	install -m 644 wallpaper/desktop*.jpg $(HOME)/.config/pirix/wallpaper

install-rc:
	install -d $(HOME)/.config/pirix
	install -m 644 Xresources $(HOME)/.config/pirix/Xresources
	install -m 644 xinitrc $(HOME)/.config/pirix/xinitrc
	install -m 644 emwmrc $(HOME)/.config/pirix/emwmrc

install-icons:
	make -C icons install

# Desktop configuration

icons:s
	make -C icons

test:
	distrobox enter pirix -- launch-pirix

clean:
	cd icons && make clean
	cd demo/atlantis && make clean
	cd demo/ideas && make clean
	cd demo/glutmech && make clean

.PHONY: instructions install icons apt-install demos test clean
