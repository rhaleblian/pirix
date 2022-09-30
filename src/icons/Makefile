prefix := $(HOME)/.config/pirix/icons

TARGETS = \
$(prefix)/client.xpm \
$(prefix)/epiphany-browser.xpm \
$(prefix)/firefox.xpm \
$(prefix)/gitk.xpm \
$(prefix)/mathematica.xpm \
$(prefix)/nedit.xpm \
$(prefix)/surf.xpm \
$(prefix)/winterm.xpm

.xpm: .png
	convert $< $@

all: $(TARGETS)

$(prefix)/client.xpm: client.png
	convert $< $@

$(prefix)/epiphany-browser.xpm: epiphany-browser.png
	convert $< -resize 128x128 $@

$(prefix)/firefox.xpm: firefox.png
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

install: $(HOME)/.config/pirix/icons $(TARGETS)


$(prefix):
	install -d $(prefix)

clean:
	- rm *.xpm
