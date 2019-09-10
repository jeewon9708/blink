#include "Arduino.h"
#include "Blink.h"

Blink::Blink(int pin)
{
	_pin=pin;
	pinMode(_pin,OUTPUT);
	pinMode(0,OUTPUT);
	digitalWrite(_pin,LOW);
	
}

void Blink::on(int delaytime)
{
	delay(delaytime);
	digitalWrite(_pin,HIGH);
	Serial.println("high");
	
}
void Blink::off(int delaytime)
{	
    delay(delaytime);
	digitalWrite(_pin,LOW);
	Serial.println("low");
	
}

