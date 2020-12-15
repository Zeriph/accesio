# The `libacces.c` C wrapper library.

# Table of Contents
1. What the library is and is not
2. How to build it
3. How to use it
4. How to extend it

## What the library is and is not

The C wrapper library is a simple C file that wraps certain functionality for
other languages to utilize through `extern`-ally marked C functions.

This wrapper is __not__ an API and is __not__ a full fledged library for the
line of cards at ACCES.

This wrapper is self contained and does __not__ access other driver code.

This wrapper is intended solely for the purpose of exposing low-level reading
and writing of the hardware to higher level languages that might have problems
communicating with the device otherwise (possibly due to how that language
might buffer when reading/writing to devices).

If you are still confused on what the full breadth of this file is, it is
highly recommended you read the source for `libacces.c`.

## How to build it

Since all of the functions are `extern`, to build this C library, you merely
need to call your compiler with the `-fPIC -shared` arguments to compile the
output file as a shared object for import in other code:

```
cc -fPIC -shared libacces.c -o libacces.so
```

That's it!

## How to use it

To use `libacces.so` in your program will depend on the language you are
utilizing, you'll also need to make sure your `LD_LIBRARY_PATH` includes the
path to `libacces.so`, example: `export LD_LIBRARY_PATH=/usr/src/acces/bin/`.

### Java
For Java, there's JNI and `System.loadLibrary("libacces.so");` exporting
the functions in `libacces.c` to their equivalent Java function signatures:

```java
static {                                                                     
    try {                                                                  
        System.loadLibrary("libacces");
    } catch (UnsatisfiedLinkError ex) {
        System.out.println("Could not load ACCES shared library."); 
        System.exit(1);
    }
}

public static native int close_handle(int fd);
public static native int cancel_wait_irq(int fd);
public static native int open_device(String device);
public static native int read_handle(int fd);
public static native int set_register_offset(int fd, int offset);
public static native int read_offset(int fd, int offset);
public static native int write_handle(int fd, int data);
public static native int write_offset(int fd, int offset, int data);
public static native int wait_for_irq(int fd);
```

### C#
For C#, there's P/Invoke; exporting the functions in `libacces.c` to their
equivalent C# function signatures:

```cs
[DllImport("libacces.so", EntryPoint="close_handle")]
static extern int close_handle(int fd);
[DllImport("libacces.so", EntryPoint="cancel_wait_irq")]
static extern int cancel_wait_irq(int fd);
[DllImport("libacces.so", EntryPoint="open_device")]
static extern int open_device(string device);
[DllImport("libacces.so", EntryPoint="read_handle")]
static extern int read_handle(int fd);
[DllImport("libacces.so", EntryPoint="set_register_offset")]
static extern int set_register_offset(int fd, int offset);
[DllImport("libacces.so", EntryPoint="read_offset")]
static extern int read_offset(int fd, int offset);
[DllImport("libacces.so", EntryPoint="write_handle")]
static extern int write_handle(int fd, int data);
[DllImport("libacces.so", EntryPoint="write_offset")]
static extern int write_offset(int fd, int offset, int data);
[DllImport("libacces.so", EntryPoint="wait_for_irq")]
static extern int wait_for_irq(int fd);
```

### C/C++
If you're using C or C++, you technically don't need this wrapper as all of the
functionality is part of the standard libraries (like `open` to open a file
handle), however, you could simply build this file in your project as the
functions are all marked `extern`, you can create a header file with the
function signatures such that you do not get implicit function warnings:

```c
extern int close_handle(int fd);
extern int cancel_wait_irq(int fd);
extern int open_device(const char* device);
extern int read_handle(int fd);
extern int set_register_offset(int fd, int offset);
extern int read_offset(int fd, int offset);
extern int write_handle(int fd, int data);
extern int write_offset(int fd, int offset, int data);
extern int wait_for_irq(int fd);
```

### OTHER
For other language support, doing a search for "use C shared library in X"
where 'X' is your language should yield enough results to help you get the
function signatures made and the library loaded in your application.


## How to extend it

To extend the functionality of the wrapper, you can simply add whatever you
would like to `libacces.c` and rebuild it and your application; if you want
to wrap the ACCES API (`api.h`), you can include that header in `libacces.c`
and do what you will; just remember to add the extra functions that you have
created to your exported function signature list in your application or you
won't be able to use them.
