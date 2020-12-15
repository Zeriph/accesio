/*
 * Copyright (c), ACCES I/O Products, Inc.
 * All rights reserved.
 * 
 * Contributor(s):
 * Zach Perez, zach.perez@accesio.com
 * 
 * PERMISSION TO USE, COPY, MODIFY, AND/OR DISTRIBUTE THIS SOFTWARE FOR ANY
 * PURPOSE WITH OR WITHOUT FEE IS HEREBY GRANTED, PROVIDED THAT THE ABOVE
 * COPYRIGHT NOTICE AND THIS PERMISSION NOTICE APPEAR IN ALL COPIES.
 * 
 * THIS SOFTWARE IS PROVIDED BY ACCES I/O AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ACCES I/O AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// This file is to demonstrate how to utilize communicate with the
// ACCES I/O device via normal function calls.
using System;
using System.IO;
using System.Runtime.InteropServices;

namespace ACCESIO
{
    static class Program
    {
        // NOTE: export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/path/to/so_file/"
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

        // NOTE: the reason we're having to use P/Invoke has to do with how the underlying Stream objects
        // of the .NET Framework buffer data and the inability to create a proper hardware buffer without
        // using unsafe code means it's better to utilize P/Invoke, especially since we're dealing with
        // single byte values.

        private static void TestDevice(string device)
        {
            Console.WriteLine("Communicating with device {0}", device);
            int handle = open_device(device);
            for (int i = 0, data = 0; i < 16; ++i) {
                set_register_offset(handle, i);
                Console.WriteLine("Reading from offset 0x{0:X2}", i);
                data = read_handle(handle);
                Console.WriteLine("data read = 0x{0:X2}", (byte)data);
            }
            for (int i = 0; i < 16; ++i) {
                set_register_offset(handle, i);
                Console.WriteLine("Writing to offset 0x{0:X2}", i);
                write_handle(handle, 0x00);
                Console.WriteLine("wrote data");
            }
            close_handle(handle);
        }

        static void Main(string[] args)
        {
            if (args.Length > 0) {
                try {
                    TestDevice(args[0]);
                } catch (Exception ex) {
                    Console.WriteLine(ex);
                }
            } else {
                Console.WriteLine("usage: test /dev/accesio/device");
            }
        }
    }
}