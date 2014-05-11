//////////////////////////////////////////////////////////////////////////////
//
// CmUsbDevice.h: Declaration of the CmUsbDevice class
//
//////////////////////////////////////////////////////////////////////////////
//
// Author: 	   Eckhard Kantz
// website:    http://wegalink.eu
//
//////////////////////////////////////////////////////////////////////////////
/*
This is FREE software

Permission is hereby granted, free of charge,  to any person obtaining  a copy
of this software and associated documentation files (the "Software"),  to deal
in the Software without restriction, including without limitation  the  rights
to use,  copy,  modify,  merge,  publish,  distribute, sublicense, and/or sell
copies  of  the  Software,   and  to  permit  persons  to  whom  the  Software
is furnished to do so, subject to the following conditions:

There are no conditions imposed on the use of this software.

THE SOFTWARE IS PROVIDED "AS IS",  WITHOUT  WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING  BUT  NOT  LIMITED  TO  THE  WARRANTIES OF MERCHANTABILITY,
FITNESS  FOR  A  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM,  DAMAGES OR OTHER
LIABILITY,  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN  THE
SOFTWARE.
*/

#ifndef CmUsbDeviceH
#define CmUsbDeviceH

#include "CmTypes.h"

// USB characteristics
#define BLOCK_SIZE            64
#define USB_READ_TIMEOUT    2000

// USB exceptions
#define USB_ERROR_FIRST               -1000
#define USB_EERROR_LAST               -1100
#define USB_BLOCK_SIZE_EXCEEDED       -1 + USB_ERROR_FIRST

// USB declarations
#define USB_CONTROL_INTERFACE         0
#define USB_NO_INTERFACE              -1

#pragma warning (disable: 4200)

#ifndef LIBUSB01

#include "libusb.h"

namespace Cosmos
{
enum TransferDirection {
	HOST_TO_DEVICE		= 0,
	DEVICE_TO_HOST		= 1
};

enum RequestType {REQ_TYPE_STANDARD =0, REQ_TYPE_CLASS =1, REQ_TYPE_VENDOR =2};

enum RequestRecipient {REQ_RECP_DEVICE =0, REQ_RECP_INTERFACE =1, REQ_RECP_ENDPOINT =2};

enum RequestCode {
	GET_STATUS					= 0,
	CLEAR_FEATURE				= 1,
	SET_FEATURE					= 3,
	SET_ADDRESS					= 5,
	GET_DESCRIPTOR			= 6,
	SET_DESCRIPTOR			= 7,
	GET_CONFIGURATION		= 8,
	SET_CONFIGURATION		= 9,
	GET_INTERFACE				= 10,
	SET_INTERFACE				= 11,
	SYNCH_FRAME					= 12,
	SET_ENCRYPTION			= 13,
	GET_ENCRYPTION			= 14,
	SET_HANDSHAKE				= 15,
	GET_HANDSHAKE				= 16,
	SET_CONNECTION			= 17,
	SET_SECURITY_DATA		= 18,
	GET_SECURITY_DATA		= 19,
	SET_WUSB_DATA				= 20,
	LOOPBACK_DATA_WRITE	= 21,
	LOOPBACK_DATA_READ	= 22,
	SET_INTERFACE_DS		= 23,
	SET_SEL							= 48,
	SET_ISOCH_DELAY			= 49
};


class CmUsbDevice
{
public:
  CmUsbDevice();
  ~CmUsbDevice();

	// http://www.dreamincode.net/forums/topic/148707-introduction-to-using-libusb-10/
	// http://stackoverflow.com/questions/14769107/libusb-bulk-transfer
  // http://www.beyondlogic.org/usbnutshell/usb4.shtml

public:
	// USB device discovery and open/close functions
	int discover_devices(CmString& Devices);
	bool open_device(uint16_t _VendorID, uint16_t _ProductID);
	bool close_device();

  // Discovering/claiming/releasing USB interface
	int discover_interface(uint16_t _VendorID, uint16_t _ProductID, CmString& Interfaces);
	bool claim_interface(int Interface = USB_CONTROL_INTERFACE);
	bool release_interface();
		
	// Sent/Receive control data
	int send_command(RequestType Type, RequestRecipient Recipient, CmString& Data, RequestCode Request =SET_FEATURE, int16 Value = 0, int16 Index = 0, int32 Timeout_ms =0);
	int query_status(RequestType Type, RequestRecipient Recipient, CmString& Data, RequestCode Request = GET_STATUS, int16 Value = 0, int16 Index = 0, int32 Tineout_ms =0);

  // Transfer binary data from/to device (direction will be infered from endpoint: < 128 - write, otherwise read)
	int transfer_data(int8 Endpoint, int8 *Data, int Length, int *Transferred = NULL, double *TransferRate = NULL, int Timeout_ms =0);

  // Access functions to USB configuration parameters
  int getVendorID();
  int getProductID();
  int getBlockSize();

  // Error description
  CmString getErrorString(int Error);

private:
  // Local variables
  int UsbRet;

private:
  uint16_t VendorID;
  uint16_t ProductID;

private:
	libusb_context *UsbContext;
	libusb_device_handle *device;

private:
	int Interface;
  int BlockSize;
};

}  // namespace

#else

#include "lusb0_usb.h"

namespace Cosmos
{

class CmUsbDevice
{
public:
  CmUsbDevice();
  ~CmUsbDevice();

public:
  // USB discovery and open function
  bool open_device(int VendorID, int ProductID, int BlockSize =BLOCK_SIZE);

  // Claiming USB interface
  bool claim_interface();

  // Read a data block
  // @return number of received bytes 
  int read_data(int8 *Data, int Length =BLOCK_SIZE, int Timeout_ms =USB_READ_TIMEOUT);

  // Access functions to USB configuration parameters
  int getVendorID();
  int getProductID();
  int getBlockSize();

  // Error description
  CmString getErrorString(int Error);

private:
  // Local variables
  int UsbRet;

private:
  // USB configuration parameters
  int VendorID;
  int ProductID;

private:
  // Data access
  int BlockSize;

private:
  // libUSB structs
  struct usb_bus *bus;
  struct usb_device *dev;
  struct usb_dev_handle *device;
  bool control_interface_claimed;
};

}  // namespace

#endif

using namespace Cosmos;

#endif 
