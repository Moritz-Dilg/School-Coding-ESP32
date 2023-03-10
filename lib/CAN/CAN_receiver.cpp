// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "CAN_receiver.hpp"

#include <Arduino.h>

CAN_receiver::CAN_receiver() {}

void CAN_receiver::init() {
	Serial.println("CAN Receiver");

	// start the CAN bus at 500 kbps
	if (!CAN.begin(500E3)) {
		Serial.println("Starting CAN failed!");
		while (1)
			;
	}
}

char* CAN_receiver::read() {
	int packetSize = CAN.parsePacket();

	if (packetSize != 0 && CAN.packetId() != -1) {
		if (!CAN.packetRtr()) {
			auto data = new char[packetSize + 1];
			data[packetSize] = '\0';

			for (int i = 0; CAN.available(); i++) {
				data[i] = (char)CAN.read();
			}

			return data;
		}
	}

	return nullptr;
}
