DSTDIR := $(HOME)/.config/pirix/demos


TARGETS=atlantis/atlantis gears/gears glutmech/glutmech ideas/ideas

default: $(TARGETS)

install: $(TARGETS)
	install -d $(DSTDIR)
	cp $? $(DSTDIR)

prep-debian:
	sudo apt install libxi-dev libxm4
	@echo
	@echo Now run make install.
	@echo

atlantis/atlantis:
	make -C atlantis

gears/gears: 
	make -C gears

glutmech/glutmech: 
	make -C glutmech

ideas/ideas:
	make -C ideas

.PHONY: default install
