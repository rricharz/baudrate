all: baudrate

baudrate: baudrate.c
	cc -o baudrate baudrate.c

install: baudrate
	./install

clean: baudrate
	-rm -f baudrate
