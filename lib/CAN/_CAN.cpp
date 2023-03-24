#include "_CAN.hpp"

TFT_eSPI tft = TFT_eSPI();
CAN_receiver receiver = CAN_receiver();
CAN_transmitter transmitter = CAN_transmitter();

_CAN::_CAN() {
}

_CAN::~_CAN() {
}

void _CAN::init() {
	tft.init();
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(1);

	Serial.begin(9600);
	while (!Serial)
		;
	transmitter.init();
}

void _CAN::send(char* data) {
	Serial.println(data);
	tft.setCursor(0, 0);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setTextSize(2);
	tft.printf("< %s", data);
	transmitter.send(data);
}

char* _CAN::read() {
	char* data = receiver.read();
	if (data != NULL) {
		Serial.println(data);
		tft.setCursor(0, 0);
		tft.setTextColor(TFT_WHITE, TFT_BLACK);
		tft.setTextSize(2);
		tft.printf("> %s", data);
	}

	return data;
}
