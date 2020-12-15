# Simple Tests

The following folder contains a set of simple tests to show reading and writing with the device.

These tests assume you have downloaded the latest drivers and are in a command prompt. It should be noted as well that to read and write to the device the user you run the tests with needs to be a member of the group that can read/write to the device. For these tests, you can run them as root or using `sudo`.

It should be noted that, aside from the C test, all of these tests will open the device like a character device, only allowing a single byte to be read at a time. The C test utilizes the ACCES API with IOCTL to send/receive larger chunks of data.

## Building the examples

The C, Java and C# tests are the only tests that need to be compiled to run, the others need their respective interpreters.

To build the tests, you can simply run `make` in this directory and all compilable tests will be built in the `../bin` directory.

You can run the other scripts directly from this folder passing in the device path as a parameter to the script.

### C

This test is written in C (C99 minimum), utilizing both standard C library functions, as well as the ACCES C API.

Building only this test: `make test-c`
Running the test from the command line: `../bin/test.bin /dev/accesio/device`

### C#

This test is written in C# against .NET Core, utilizing P/Invoke and Mono in Linux to run the binary.

Building only this test: `make test-cs`
Running the test from the command line: `mono ../bin/test.exe /dev/accesio/device`

Since this test utilizes P/Invoke, it will make `libacces` producing `../bin/libacces.so`, which needs to be in your `LD_LIBRARY_PATH`; to this, you can simply run the following command: `export LD_LIBRARY_PATH="/usr/src/acces/bin/libacces.so"` (assuming the source was extracted to `/usr/src/acces`).

### Java

This test is written in standard Java (no target version), utilizing a basic JRE in Linux to run the class file.

Building only this test: `make test-java`
Running the test from the command line: `java ../bin/test /dev/accesio/device`

### PHP

This test is written in standard PHP (no target version), utilizing basic PHP functionality.

Running the test from the command line: `php test.php /dev/accesio/device`

### Perl

This test is written in standard Perl (no target version), utilizing basic system functionality.

Running the test from the command line: `perl test.pl /dev/accesio/device`

### Python

This test is written in standard Python (no target version), utilizing basic system functionality.

Running the test from the command line: `python test.py /dev/accesio/device`

### Shell script

This test is written to utilize standard shell tools, like `echo` and `dd`.

Running the test from the command line: `sh test.sh /dev/accesio/device`
