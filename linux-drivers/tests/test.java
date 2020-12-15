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
public class test
{
    private static void TestDevice(String device) throws java.io.FileNotFoundException, java.io.IOException
    {
        int data; // we have to use a type larger than a byte since they are signed in Java
        java.io.RandomAccessFile file = new java.io.RandomAccessFile(device, "rw");
        System.out.printf("Communicating with device %s\n", device);
        for (int i = 0; i < 16; ++i) {
            System.out.printf("Reading from offset 0x%02X\n", i);
            file.seek(i);
            data = (int)(file.readByte() & 0xFF);
            System.out.printf("data read = 0x%02X\n", data);
        }
        for (int i = 0; i < 16; ++i) {
            System.out.printf("Writing to offset 0x%02X\n", i);
            file.seek(i);
            file.writeByte(0);
            System.out.printf("wrote data\n");
        }
    }

    public static void main(String[] args)
    {
        if (args.length > 0) {
            try {
                TestDevice(args[0]);
            } catch (java.io.FileNotFoundException fex) {
                System.out.printf("FileNotFoundException: %s\n", fex.toString());
            } catch (java.io.IOException iex) {
                System.out.printf("IOException: %s\n", iex.toString());
            }
        } else {
            System.out.printf("usage: test /dev/accesio/device\n");
        }
    }
}
