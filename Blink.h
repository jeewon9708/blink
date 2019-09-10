#ifndef Blink_h
#define Blink_h

#include "Arduino.h"

class Blink
{
	public:
		Blink(int pin);
		void on(int delaytime);
		void off(int delaytime);
	private:
		int _pin;
};

#endif



