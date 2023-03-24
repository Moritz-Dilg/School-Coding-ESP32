#include <Arduino.h>

#include <_CAN.hpp>

/*--CAN--*/
_CAN can = _CAN();
char array[8];

void setup() {
	/*--CAN--*/
	can.init();
}

void loop() {
	/*--CAN--*/
	// can.read();
	Serial.readBytesUntil(13, array, 8);
	if (array[0] != '\0') can.send(array);
	for (int i = 0; i < 8; i++) array[i] = '\0';
}
