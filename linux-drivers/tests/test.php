<?php
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

# This file is to demonstrate how to communicate with the
# ACCES I/O device via normal function calls.

function TestDevice($device)
{
    # NOTE: due to how PHP handles files/pipes/devices through fopen/fread, etc., fseek
    # won't work in PHP to specify a different offset for the device, but shell execution
    # of normal command line options (like dd/echo) works
    if ($dev != "/dev/null") {
        echo "Communicating with device $device\n";
        for ($i = 0; $i < 16; ++$i) {
            printf("Reading from offset 0x%02X\n", $i);
            $cmd = "/usr/bin/dd if=$device bs=1 count=1 skip=$i 2>/dev/null | /usr/bin/hexdump -e '/1 \"0x\" \"%02X\" \"\\n\"'";
            echo "data read = ".exec($cmd)."\n";
        }
        for ($i = 0; $i < 16; ++$i) {
            printf("Writing 0x00 to offset 0x%02X\n", $i);
            shell_exec("echo -n \"\\0\" | /usr/bin/dd of=$device bs=1 count=1 seek=$i 2>/dev/null");
            echo "wrote data\n";
        }
    } else {
        echo "usage: test /dev/accesio/device";
    }
}

$dev = "/dev/null";
if (!isset($_SERVER["HTTP_HOST"])) { parse_str($argv[1], $_GET); }
if (isset($_POST['dev'])) {
    $dev = $_POST['dev'];
} elseif (isset($_GET['dev'])) {
    $dev = $_GET['dev'];
}

TestDevice($dev);

?>
