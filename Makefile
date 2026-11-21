
instructions:
	@echo Files are installed to '$(HOME)/.config/pirix' .
	@echo IMPORTANT: installation overwrites any previous edits!
	@echo
	@echo "Run 'make install'."
	@echo Then see README.md for additional steps.

install:
	make -C share install
	make -C etc install

demos:
	make -C src/demos

install-demos:
	make -C src/demos install
