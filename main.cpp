#include <iostream>
#include <thread>
#include "libusb-1.0/libusb.h"

using namespace std;

// CC1350 LaunchPad device and interface
uint vendor = 0x0451;
uint product = 0xbef3;
uint interface = 1;

// Libusb globals
libusb_context *ctx;
libusb_device_handle *dev;

// Endpoints for in and out
unsigned char endpointIn = 0x02 | LIBUSB_ENDPOINT_IN;
unsigned char endpointOut = 0x01 | LIBUSB_ENDPOINT_OUT;

// Other variables
int len = 1024;
bool run = true;

// Simple error output
void error(string s, int err) {
	cout << s << " Error: " << libusb_error_name(err) << endl;
}

// Simple thread function to receive responses
void thread_function()
{
	int transfer_size;
	int err;
	unsigned char *resp;
	resp = new unsigned char[len];
	string respData;
	// cout << "Reading response..." << endl;
	while (run) {
		memset(resp, 0, len);
		err = libusb_bulk_transfer(dev, endpointIn, resp, len, &transfer_size, 250);
		if (err == LIBUSB_ERROR_TIMEOUT) {
			continue;
		}
		if (err) {
			error("Bulk IN transfer failed.", err);
		}
		for (int i = 0; i < transfer_size; ++i) {
			// printf(" %02d ", resp[i]);
			if (resp[i] == 13) {
				cout << "Response line: " << respData << endl;
				respData.clear();
			} else {
				respData += resp[i];
			}
		}
		// cout << endl;
		// cout << "Response: (" << transfer_size << ") " << resp << endl;
	}

	delete resp;
}

// Main app
int main()
{

	int transfer_size;
	int err;

	libusb_init(&ctx);
	// libusb_set_debug(ctx, LIBUSB_LOG_LEVEL_DEBUG);

	// Open the TI device
	dev = libusb_open_device_with_vid_pid(NULL, vendor, product);

	if (nullptr == dev) {
		cout << "Device not found, exiting." << endl;
		return -1;
	}

	// Enabling this does not allow the LaunchPad device to connect
	// to both the debug and command interface at the same time.
	// err = libusb_set_configuration(dev, 1);
	// if (err) {
	// 	error("Cannot set device configuration.", err);
	// }

	// Claim the proper interace
	err = libusb_claim_interface(dev, interface);
	if (err) {
		error("Cannot claim interface.", err);
		return -1;
	}

	err = libusb_set_interface_alt_setting(dev, interface, 0);
	if (err) {
		error("Cannot claim alt interface.", err);
		return -1;
	}

	libusb_transfer *xfer;		// libusb transfer data
	unsigned char *command;		// command entered by user
	string byeCmd = "bye";		// command used to exit the app

	command = new unsigned char[len];

	// Fire up the response thread
	std::thread threadObj(thread_function);

	cout << "Start entering commands!" << endl;
	while (run) {
		// cout << "Enter a command: ";
		memset(command, 0, len);
		std::cin.getline((char *)command, len);
		if (byeCmd == (char*)command) {
			run = false;
			break;
		}
		cout << "Sending: " << command << endl;
		command[strlen((char *)command)] = '\r';

		// Do the transfer
		err = libusb_bulk_transfer(dev, endpointOut, command, strlen((const char*)command), &transfer_size, 1000);
		if (err) {
			error("Bulk OUT transfer failed.", err);
		}
		// cout << "OUT transferred: " << transfer_size << endl;

	}

	// Wait for response thread to finish
	threadObj.join();

	cout << "Have a nice day!" << endl;
	delete command;

	return 0;
}