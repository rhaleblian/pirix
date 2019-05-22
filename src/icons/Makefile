prefix := $(HOME)/.config/pirix/icons

TARGETS = \
$(prefix)/epiphany-browser.xpm \
$(prefix)/firefox-esr.xpm \
$(prefix)/gitk.xpm \
$(prefix)/mathematica.xpm \
$(prefix)/nedit.xpm \
$(prefix)/surf.xpm \
$(prefix)/winterm.xpm

.xpm: .png
	convert $< $@

all: $(TARGETS)

$(prefix)/epiphany-browser.xpm: epiphany-browser.png
	convert $< -resize 128x128 $@

$(prefix)/firefox-esr.xpm: firefox-esr.png
	convert $< $@

$(prefix)/gitk.xpm: gitk.png
	convert $< -resize 128x128 $@

$(prefix)/mathematica.xpm: mathematica.png
	convert $< $@

$(prefix)/nedit.xpm: nedit.png
	convert $< $@

$(prefix)/surf.xpm: surf.png
	convert $< $@

$(prefix)/winterm.xpm: winterm.png
	convert $< $@

clean:
	- rm *.xpm

