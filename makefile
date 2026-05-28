CFLAGS := $(shell pkg-config --cflags SDL2_ttf)
LIBS := $(shell pkg-config --libs SDL2_ttf)

all:
	gcc *.c -g -o tracker $(CFLAGS) $(LIBS)

clean:
	rm tracker
	rm -rf tracker.dSYM