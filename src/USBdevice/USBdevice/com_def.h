// AT90USB/com_def.h
// Common defines for firmware and PC program
// S. Salewski, 23-MAR-2007
// Eckhard Kantz, 2014-04-27

#ifndef _COM_DEF_H_
#define _COM_DEF_H_

#define MyUSB_VendorID 0x03eb // Atmel code
#define MyUSB_ProductID 0x0001 // arbitrary value
#define USB_VendorRequestCode (1<<6)

// Endpoint 1, used for transferring messages:
// Bulk IN, 64 byte FIFO
#define EP1_FIFO_Size 64

// Endpoint 2, used for transferring data to host:
// Bulk IN, 64 byte dual bank FIFO
#define EP2_FIFO_Size 64

// Endpoint 2, used for receiving data from host:
// Bulk OUT, 8 byte FIFO
#define EP3_FIFO_Size 64

// Status codes
#define UsbDevStatusOK 0
#define UsbDevStatusDAQ_BufferOverflow 1
#define UsbDevStatusDAQ_TimerOverflow 2
#define UsbDevStatusDAQ_ConversionNotFinished 3

#endif
