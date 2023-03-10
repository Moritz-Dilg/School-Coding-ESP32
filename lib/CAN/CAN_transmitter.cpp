#include "CAN_transmitter.hpp"

CAN_transmitter::CAN_transmitter() {}

void CAN_transmitter::init() {
	Serial.begin(9600);
	while (!Serial)
		;

	Serial.println("CAN Sender");

	// start the CAN bus at 500 kbps
	if (!CAN.begin(500E3)) {
		Serial.println("Starting CAN failed!");
		while (1)
			;
	}
}

void CAN_transmitter::send(char* text) {
	int length = strlen(text);

	if (length > 0) {
		Serial.print("Sending packet ... ");
		CAN.beginPacket(0x12);
		for (uint8_t i = 0; i < length; i++) {
			CAN.write(text[i]);
		}
		CAN.endPacket();

		Serial.println("done");
	}

	delay(1000);

	// send extended packet: id is 29 bits, packet can contain up to 8 bytes of
	// data
	/*
	Serial.print("Sending extended packet ... ");

	CAN.beginExtendedPacket(0xabcdef);
	CAN.write('w');
	CAN.write('o');
	CAN.write('r');
	CAN.write('l');
	CAN.write('d');
	CAN.endPacket();

	Serial.println("done");

	delay(1000);
	*/
}
