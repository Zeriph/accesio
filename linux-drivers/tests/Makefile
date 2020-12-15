default: all

all: lib test-all

test-all: test-c test-java test-cs

test-c: mkbin
	cc test.c -I . -I ../ -Wall -Wno-unused-function -o ../bin/test.bin

test-java: mkbin
	javac -d ../bin -sourcepath . test.java

test-cs: lib
	mcs test.cs -out:../bin/test.exe

lib: mkbin
	cd ../acces && $(MAKE) lib

mkbin:
	mkdir -p ../bin

clean:
	rm -vf ../bin/test*
	rm -vf ../bin/libacces.so
