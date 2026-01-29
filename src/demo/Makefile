all: atlantis/atlantis gears/gears glutmech/glutmech ideas/ideas

prep-debian:
	sudo apt install libxi-dev libxm-dev

atlantis/atlantis:
	make -C atlantis

gears/gears: 
	make -C gears

glutmech/glutmech: 
	make -C glutmech

ideas/ideas:
	make -C ideas

/usr/lib/aarch64-linux-gnu/pkgconfig/xmu.pc: prep-debian

