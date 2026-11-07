prefix := $(HOME)/.config/pirix/icons

TARGETS = \
$(prefix)/client.xpm \
$(prefix)/emacs.xpm \
$(prefix)/epiphany-browser.xpm \
$(prefix)/firefox-esr.xpm \
$(prefix)/gitk.xpm \
$(prefix)/mathematica.xpm \
$(prefix)/nedit.xpm \
$(prefix)/surf.xpm \
$(prefix)/winterm.xpm

install: $(prefix) $(TARGETS)

$(prefix)/client.xpm: client.png
	magick convert $< $@

$(prefix)/emacs.xpm: emacs.png
	magick convert $< $@

$(prefix)/epiphany-browser.xpm: epiphany-browser.png
	magick convert $< -resize 86x86 $@

$(prefix)/firefox-esr.xpm: firefox-esr.png
	magick convert $< $@

$(prefix)/gitk.xpm: gitk.png
	magick convert $< -resize 86x86 $@

$(prefix)/mathematica.xpm: mathematica.png
	magick convert $< $@

$(prefix)/nedit.xpm: nedit.png
	magick convert $< $@

$(prefix)/surf.xpm: surf.png
	magick convert $< $@

$(prefix)/winterm.xpm: winterm.png
	magick convert $< $@

$(prefix):
	install -d $(prefix)

clean:
	- rm $(prefix)/*.xpm
