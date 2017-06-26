# ti-easylink-test
C++ CLI to test interaction with TI SimpleLink-EasyLink AT command API

Tested with the TI CC1350 LaunchPad development board on OS X.

## Resources

* [LaunchPad overview](http://www.ti.com/lsds/ti/tools-software/launchpads/overview/overview.page?keyMatch=launchpad&tisearch=Search-EN-Everything&rec=true)
* [CC1350](http://www.ti.com/tool/launchxl-cc1350)
* [EasyLink Network Processor example](http://dev.ti.com/tirex/content/simplelink_academy_cc13x0sdk_1_12_01_16/modules/prop_03_easylink_nwp/prop_03_easylink_nwp.html)
* [EasyLink reference](http://processors.wiki.ti.com/index.php/SimpleLink-EasyLink)

## Dependencies

Uses libusb:

* [Home page](http://libusb.info/)
* [Code](https://github.com/libusb/libusb)

The libusb libraries are expected to be installed into `/usr/local`

## Building

Simple Makefile included.  This should work for any recent C++ compiler and libusb installed in `/usr/local`.

## Usage

Start the `easylink` binary from a terminal and enter some commands as described in the [EasyLink reference](http://processors.wiki.ti.com/index.php/SimpleLink-EasyLink).

Example (entered commands are just before the 'Sending' lines):

```
$ ./easylink
Start entering commands!
AT+i 0
Sending: AT+i 0
Response line: AT+i 0
Response line: OK
ATPFR?
Sending: ATPFR?
Response line: ATPFR?
Response line: 868000000OK
ATPFR=915000000
Sending: ATPFR=915000000
Response line: ATPFR=915000000
Response line: OK
ATPFR?
Sending: ATPFR?
Response line: ATPFR?
Response line: 915000000OK
ATPPW?
Sending: ATPPW?
Response line: ATPPW?
Response line: 0012OK
AT+rs
Sending: AT+rs
Response line: AT+rs
Response line: Reset:EasyLink-v2.00.00
bye
Have a nice day!
```
