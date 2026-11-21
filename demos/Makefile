DSTDIR := $(HOME)/.config/pirix/demos


install: atlantis/atlantis gears/gears glutmech/glutmech ideas/ideas
	- mkdir $(DSTDIR)
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

