/*
 * USBdevice.c
 *
 * Created: 09.03.2014 15:21:57
 *  Author: Eckhard
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "usb_drv.h"

static void blinkforever(void);


int main(void)
{
	cli();
	CLKPR = (1<<7);
	CLKPR = 0; // clock prescaler == 0, so we have 16 MHz mpu frequency with our 16 MHz crystal
	UsbDevLaunchDevice(false);
	// UsbDevWaitStartupFinished(); // no reason to wait
	blinkforever();
	return 0;
}

// a LED connected to PORTA0 will toggle to indicate the unused processing power
static void
blinkforever(void)
{
	int i = 0; // to suppress warning of avr-gcc
	DDRA |= (1<<DDA0);
	while (1)
	{
		while (i++)
		{
			asm volatile ("nop"); // necessary for avr-gcc 4.x to prevent removing of empty delay loop
		}
		PORTA ^= (1<<PORTA0);
	}
}
