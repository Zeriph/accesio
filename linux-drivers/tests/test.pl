#!/usr/bin/perl
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
use strict;
use Fcntl;

my $device = "/dev/null";
my $data;
my $tmp = 0;
if (($#ARGV + 1) > 0) {
    $device = $ARGV[0];
} else {
    die "usage: test /dev/accesio/device";
}
printf("Communicating with device %s\n", $device);
sysopen(my $fd, $device, O_RDWR|O_BINARY);
for ($tmp = 0; $tmp < 16; $tmp++) {
    sysseek($fd, $tmp, 0);
    printf("Reading from offset 0x%02X\n", $tmp);
    sysread($fd, $data, 1);
    printf("data read = 0x%02X\n", ord($data));
}
for ($tmp = 0; $tmp < 16; $tmp++) {
    sysseek($fd, $tmp, 0);
    printf("Writing 0x00 to offset 0x%02X\n", $tmp);
    syswrite($fd, 0, 1);
    printf("wrote data\n");
}
close($fd);