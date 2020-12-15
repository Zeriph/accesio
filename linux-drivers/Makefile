default: all

all: lib tests

tests:
	cd tests && $(MAKE) test-all

drivers:
	cd acces && $(MAKE) drivers

install: drivers
	cd acces && $(MAKE) install

lib: mkbin
	cd acces && $(MAKE) lib

mkbin:
	mkdir -p bin

clean:
	cd acces && $(MAKE) clean
	cd tests && $(MAKE) clean
