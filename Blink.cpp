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
	
	digitalWrite(_pin,HIGH);
	Serial.println("high");
	delay(delaytime);
	
}
void Blink::off(int delaytime)
{	
    
	digitalWrite(_pin,LOW);
	Serial.println("low");
	delay(delaytime);
	
}

