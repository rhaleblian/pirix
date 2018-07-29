
default:
	echo 'Examine the install rule first.'

install:
	cp xinitrc $(HOME)/.xinitrc
	cp mwmrc $(HOME)/.mwmrc
	- mkdir $(HOME)/Pictures/wallpaper
	cp mwm.jpg $(HOME)/Pictures/wallpaper

