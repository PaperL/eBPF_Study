run: load.c
	# clang -I /usr/share/liburing/src/include -L /usr/lib/aarch64-linux-gnu -luring -lrt -laio -o load load.c
	clang -o load load.c
clean: 
	rm temp
	rm load
