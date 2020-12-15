# Copyright (c), ACCES I/O Products, Inc.
# All rights reserved.
# 
# Contributor(s):
# Zach Perez, zach.perez@accesio.com
# 
# PERMISSION TO USE, COPY, MODIFY, AND/OR DISTRIBUTE THIS SOFTWARE FOR ANY
# PURPOSE WITH OR WITHOUT FEE IS HEREBY GRANTED, PROVIDED THAT THE ABOVE
# COPYRIGHT NOTICE AND THIS PERMISSION NOTICE APPEAR IN ALL COPIES.
# 
# THIS SOFTWARE IS PROVIDED BY ACCES I/O AND CONTRIBUTORS "AS IS" AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL ACCES I/O AND CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# This file is to demonstrate how to utilize communicate with the
# ACCES I/O device via normal function calls.
import sys

def TestDevice(device):
    i = 0
    print "Communicating with device " + device
    file = open(device, "rb+", 0)
    while i < 16:
        print "Reading from offset 0x{:02X}".format(i)
        file.seek(i, 0) # sets the register offset
        data = file.read(1)
        print "data read = 0x{:02X}".format(ord(data))
        i += 1
    i = 0
    while i < 16:
        print "Writing to offset 0x{:02X}".format(i)
        file.seek(i, 0) # sets the register offset
        file.write("\0")
        print "wrote data"
        i += 1
    file.close()

dev = "/dev/null"
if len(sys.argv) > 1:
    dev = sys.argv[1]
    TestDevice(dev)
else:
    print "usage: test /dev/accesio/device"
