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
	magick $< $@

$(prefix)/emacs.xpm: emacs.png
	magick $< $@

$(prefix)/epiphany-browser.xpm: epiphany-browser.png
	magick $< -resize 86x86 $@

$(prefix)/firefox-esr.xpm: firefox-esr.png
	magick $< $@

$(prefix)/gitk.xpm: gitk.png
	magick $< -resize 86x86 $@

$(prefix)/mathematica.xpm: mathematica.png
	magick $< $@

$(prefix)/nedit.xpm: nedit.png
	magick $< $@

$(prefix)/surf.xpm: surf.png
	magick $< $@

$(prefix)/winterm.xpm: winterm.png
	magick $< $@

$(prefix):
	install -d $(prefix)

clean:
	- rm $(prefix)/*.xpm
