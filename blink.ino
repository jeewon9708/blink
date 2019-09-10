
#include <Blink.h>


Blink blink(4);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("\nBlink Version 1.0 Jeewon Chae");
}

void loop() {
  // put your main code here, to run repeatedly:
  blink.on(500);
  blink.off(300);

}
