//////////////////////////////////////////////////////////////////////////////
//
// CmUsbDevice.cpp: Implementation of the CmUsbDevice class
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


#include "CmUsbDevice.h"

// Constants
int USB_RET								= 0;
int USB_CONFIGURATION			= 1;


//-----------------------------------------------------------------------------
// Constructors and destructor
//-----------------------------------------------------------------------------
CmUsbDevice::CmUsbDevice()
{
  // Initialize state variables
  VendorID = 0;
  ProductID = 0;
  BlockSize = BLOCK_SIZE; // must not be zero
	Interface = USB_NO_INTERFACE;

#ifndef LIBUSB01
  // Initialize state variables
  UsbContext = NULL;
  device = NULL;
  // Initialize USB lib
  libusb_init(&UsbContext);
#else
  // Initialize state variables
  bus = NULL;
  dev = NULL;
  device = NULL;
  // Initialize USB lib
  usb_init();
#endif
}

CmUsbDevice::~CmUsbDevice()
{
#ifndef LIBUSB01
  // Release interface and close USB device
  if (0!=device){
		USB_RET = libusb_release_interface(device,USB_CONTROL_INTERFACE);
		libusb_close(device);
	}
  // Close USB lib
  if (NULL != UsbContext)
    libusb_exit(UsbContext);
#else
  if (0!=device){
    if (control_interface_claimed)
      usb_release_interface(device,USB_CONTROL_INTERFACE);
		usb_close(device);
	}
#endif
}


//-----------------------------------------------------------------------------
// USB device and interface discovery functions
//-----------------------------------------------------------------------------
int CmUsbDevice::discover_devices(CmString& Devices)
{
	Devices = "\r\n Device list:";

	libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices  
	libusb_context *ctx = NULL; //a libusb session  
	libusb_device_descriptor desc;

	int r; //for return values  
	ssize_t cnt; //holding number of devices in list  

	r = libusb_init(&ctx); //initialize a library session  

	if (r < 0) 	return r;

	libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation  

	cnt = libusb_get_device_list(ctx, &devs); //get the list of devices  
	if (cnt < 0) return cnt;

	for (ssize_t i = 0; i < cnt; i++) {
		r = libusb_get_device_descriptor(devs[i], &desc);
		if (r < 0) 	return r;

		// generate an info line for each device
		char Info[256];
		sprintf_s(Info, sizeof(Info), "\r\n  %02d)   VID: %04X   PID: %04X   Class: %03d   Configs: %d", i+1, desc.idVendor, desc.idProduct, desc.bDeviceClass, desc.bNumConfigurations);
		Devices += Info;
	}

	libusb_free_device_list(devs, 1); //free the list, unref the devices in it  
	libusb_exit(ctx); //close the session  

	return LIBUSB_SUCCESS;
}

//-----------------------------------------------------------------------------
// USB device operating functions
//-----------------------------------------------------------------------------
#ifndef LIBUSB01
bool CmUsbDevice::open_device(uint16_t _VendorID, uint16_t _ProductID)
{
  // Check current state
  if (NULL!=device){
    if (VendorID==_VendorID && ProductID==_ProductID) return true;
    else return false;
  }else{
    // Search for desired USB device
    VendorID = _VendorID;
    ProductID = _ProductID;
    device = libusb_open_device_with_vid_pid(UsbContext,VendorID,ProductID);
    // Check if a device was found
    if (NULL==device) return false;
  }
  return true;
#else
bool CmUsbDevice::open_device(int _VendorID, int _ProductID, int _BlockSize)
{
  // Find device
  usb_find_busses();
  usb_find_devices();
  for (bus = usb_busses; bus; bus = bus->next){
    for (dev = bus->devices; dev; dev = dev->next){
      if ((dev->descriptor.idVendor==_VendorID) && (dev->descriptor.idProduct==_ProductID)) break;
    }
  }
  // Check device availability
  if (NULL==dev) return false;
  // Open device
  device = usb_open(dev);
  // Check device open
  if (NULL==device) return false;
  // Initialize data transfer: block size must never be zero
  BlockSize = _BlockSize>0 ? _BlockSize : 1;  
  return true;
#endif
}

bool CmUsbDevice::close_device()
{
	// Release interface and close USB device
	if (0 != device){
		if (false == release_interface()) return false;
		libusb_close(device);
		device = 0;
	}
	return true;
}

int CmUsbDevice::discover_interface(uint16_t _VendorID, uint16_t _ProductID, CmString& Interfaces)
{
	libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices  
	libusb_context *ctx = NULL; //a libusb session  
	libusb_device_descriptor desc;
	const libusb_interface *inter;
	const libusb_interface_descriptor *interdesc;
	const libusb_endpoint_descriptor *epdesc;
	int r; //for return values  
	ssize_t cnt; //holding number of devices in list  

	r = libusb_init(&ctx); //initialize a library session  
	if (r < 0) 	return r;

	libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation  
	cnt = libusb_get_device_list(ctx, &devs); //get the list of devices  
	if (cnt < 0) return cnt;

	for (ssize_t i = 0; i < cnt; i++) {
		r = libusb_get_device_descriptor(devs[i], &desc);
		if (r < 0) 	return r;

		// Check for requested vendor and product ID
		if (_VendorID != desc.idVendor || _ProductID != desc.idProduct) continue;

		char Info[256];
		sprintf_s(Info, sizeof(Info), "\r\n  Device:  VID: %04X   PID: %04X   Class: %03d   Configs: %d  Interfaces: ", desc.idVendor, desc.idProduct, desc.bDeviceClass, desc.bNumConfigurations);
		Interfaces = Info;

		// generate an info line for each interface/endpoint
		libusb_config_descriptor *config;
		libusb_get_config_descriptor(devs[i], 0, &config);
		Interfaces += (int)config->bNumInterfaces;

		for (int i = 0; i<(int)config->bNumInterfaces; i++) {
			Interfaces += "\r\n  Interface-";
			Interfaces += i;

			inter = &config->interface[i];
			for (int j = 0; j<inter->num_altsetting; j++) {
				interdesc = &inter->altsetting[j];

				for (int k = 0; k<(int)interdesc->bNumEndpoints; k++) {
					epdesc = &interdesc->endpoint[k];
					sprintf_s(Info, sizeof(Info), "\r\n    Endpoint-%d  Address: %03d  MaxPacket: %02d  Attributes: %d  Interval: %d  Length: %d", k+1, epdesc->bEndpointAddress, epdesc->wMaxPacketSize, epdesc->bmAttributes, epdesc->bInterval, epdesc->bLength);
					Interfaces += Info;
				}
			}
		}

		libusb_free_config_descriptor(config);
	}

	libusb_free_device_list(devs, 1); //free the list, unref the devices in it  
	libusb_exit(ctx); //close the session  

	return LIBUSB_SUCCESS;
}

bool CmUsbDevice::claim_interface(int _Interface)
{
	// Check for USB device
	if (0 == device) return false;
  // Check if already claimed
  if (Interface == _Interface) return true;
#ifndef LIBUSB01
	// Release interface
	if (false == release_interface()) return false;
	// Enabled 'detach kernel driver' if supported, otherwise do nothing
	USB_RET=libusb_set_auto_detach_kernel_driver(device, 1);
	// USB configuration 1 is used
	if (LIBUSB_SUCCESS!=(USB_RET=libusb_set_configuration(device,USB_CONFIGURATION))) return false;
	// Claim interface 
	if (LIBUSB_SUCCESS!=(USB_RET=libusb_claim_interface(device,_Interface))) return false;
	// Interface successfully claimed
	Interface = _Interface;
	return true;
#else
  // Select first configuration
  if (0!=usb_set_configuration(device,USB_CONFIGURATION)) return false;
  // Claim control interface
  if (0!=usb_claim_interface(device,USB_CONTROL_INTERFACE)) return false;
	// Control interface successfully claimed
  control_interface_claimed = true;
  return true;
#endif
}

bool CmUsbDevice::release_interface()
{
	if (Interface != USB_NO_INTERFACE){
		// Release interface
		if (LIBUSB_SUCCESS != libusb_release_interface(device, Interface)) return false;
		Interface = USB_NO_INTERFACE;
	}
	return true;
}

int CmUsbDevice::send_command(RequestType _Type, RequestRecipient _Recipient, CmString& _Data, RequestCode _Request, int16 _Value, int16 _Index, int32 _Timeout_ms)
{
	int Ret;
	int8 Type = (HOST_TO_DEVICE << 7) + (_Type << 5) + _Recipient;

	// estimate a suitable timeout based on 100 kB/s
	if (_Timeout_ms == 0){
	_Timeout_ms = 100 + _Data.getLength() / 100;
	}

	Ret = libusb_control_transfer(device, Type, _Request, _Value, _Index, (uint8*)_Data.getBuffer(), _Data.getLength(), _Timeout_ms);

	if (Ret < 0) return Ret;
	if (Ret > _Data.getLength()) return LIBUSB_ERROR_OTHER;   // received more data than requested, this should never happen

	return LIBUSB_SUCCESS;
}

int CmUsbDevice::query_status(RequestType _Type, RequestRecipient _Recipient, CmString& _Data, RequestCode _Request, int16 _Value, int16 _Index, int32 _Timeout_ms)
{
	int Ret;
	int8 Type = (DEVICE_TO_HOST << 7) + (_Type << 5) + _Recipient;

	// estimate a suitable timeout based on 100 kB/s
	if (_Timeout_ms == 0){
		_Timeout_ms = 100 + _Data.getLength() / 100;
	}

	Ret = libusb_control_transfer(device, Type, _Request, _Value, _Index, (uint8*)_Data.getBuffer(), _Data.getLength(), _Timeout_ms);

	if (Ret < 0) return Ret;
	if (Ret > _Data.getLength()) return LIBUSB_ERROR_OTHER;   // received more data than requested, this should never happen

	return LIBUSB_SUCCESS;
}

int CmUsbDevice::transfer_data(int8 _Endpoint, int8 *_Data, int _Length, int *_Transferred, double *_TransferRate, int _Timeout_ms)
{
	int32 TotalData = 0;
	int Ret;

	// estimate a suitable timeout based on 100 kB/s
	if (_Timeout_ms == 0)
		_Timeout_ms = 100 + _Length / 100;

	CmTimestamp Start;		// current timestamp

	// transfer data until data length is reached or an error occurred
	while (TotalData < _Length){
		int Transferred;

		Ret = libusb_bulk_transfer(device, _Endpoint, (uint8*)_Data + TotalData, _Length - TotalData, &Transferred, _Timeout_ms);

		// handle error conditions
		if (Ret != LIBUSB_SUCCESS) return Ret;

		TotalData += Transferred;
	}
	// return received total amount of data
	if (NULL != _Transferred)
		*_Transferred = TotalData;
	// return estimated data rate (amount of data should be > 100 kB, otherwise estimation becomes inaccurate)
	if (NULL != _TransferRate)
		*_TransferRate = Start.getDataRate(TotalData);

	return Ret;
}

//-----------------------------------------------------------------------------
// USB configuration parameters
//-----------------------------------------------------------------------------
int CmUsbDevice::getVendorID()
{
  return VendorID;
}
int CmUsbDevice::getProductID()
{
  return ProductID;
}
int CmUsbDevice::getBlockSize()
{
  return BlockSize;
}

//-----------------------------------------------------------------------------
// USB error strings
//-----------------------------------------------------------------------------
CmString CmUsbDevice::getErrorString(int _Error)
{
  CmString Description;
  // Check for USB class' errors
  if (_Error>=USB_ERROR_FIRST && _Error<=USB_EERROR_LAST){
    Description = "USB class error: "; 
    Description += CmString(_Error);
  }else{
    // libUSB error
#ifndef LIBUSB01
	  Description = libusb_error_name(_Error);
#else
	  Description = usb_strerror();
#endif
	  return Description;
  }
}


