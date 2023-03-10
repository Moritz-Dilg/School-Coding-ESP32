#include <Arduino.h>
#include <CAN.h>
#include <TFT_eSPI.h>

#include <CAN_receiver.hpp>
#include <CAN_transmitter.hpp>

TFT_eSPI tft = TFT_eSPI();
CAN_receiver receiver = CAN_receiver();
CAN_transmitter transmitter = CAN_transmitter();
char array[8] = {'t', 'e', 's', 't', '\0'};

void setup() {
	tft.init();
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(1);

	Serial.begin(9600);
	while (!Serial)
		;
	transmitter.init();
}

void loop() {
	char* data = receiver.read();
	if (data != NULL) {
		Serial.println(data);
		tft.setCursor(0, 0);
		tft.setTextColor(TFT_WHITE, TFT_BLACK);
		tft.setTextSize(2);
		tft.printf("> %s", data);
	}

	// Serial.readBytesUntil(13, array, 8);
	/*
		if (array[0] != '\0') {
			Serial.println(array);
			tft.setCursor(0, 0);
			tft.setTextColor(TFT_WHITE, TFT_BLACK);
			tft.setTextSize(2);
			tft.printf("< %s", array);
			transmitter.send(array);
		}
	 */
	/* for (int i = 0; i < 8; i++) {
		array[i] = '\0';
	} */
}
