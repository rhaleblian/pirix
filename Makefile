
default:
	echo 'Examine the install rule first.'

install:
	install Xresources $(HOME)/.Xresources
	install pirixrc $(HOME)/.pirixrc
	install mwmrc $(HOME)/.mwmrc
	install pirix-desktop.jpg $(HOME)/Pictures
