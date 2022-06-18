all:
	# clang -I /usr/share/liburing/src/include -L /usr/lib/aarch64-linux-gnu -luring -lrt -laio -o load load.c
	clang -O0 -o load_stdio load_stdio.c
	clang -O0 -I iouring/include -L iouring -luring -o load_iouring load_iouring.c
clean: 
	sudo rm temp
	rm load_stdio
	rm load_iouring
