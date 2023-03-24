#include <Arduino.h>
#include <WiFi.h>

#include <ESP_NOW.hpp>
#include <_CAN.hpp>

/*--CAN--*/
// _CAN can = _CAN();
// char array[8];

/*--ESP-NOW--*/
void OnDataSentDefaultCB(const uint8_t *mac_addr, esp_now_send_status_t status) {
	Serial.println("\nLast Packet Send Status:\t" + (status == ESP_NOW_SEND_SUCCESS) ? "Successfully sent" : "Sending failed");
}

void OnDataRecvDefaultCB(const uint8_t *mac, const uint8_t *incomingData, int len) {
	DynamicJsonDocument doc(1024);
	deserializeJson(doc, incomingData);

	Serial.print("Mac: ");
	for (int i = 0; i < 6; i++) {
		Serial.print(mac[i], HEX);
		if (i < 5) Serial.print(":");
	}
	Serial.print("\nName: ");
	Serial.println(doc["Name"].as<String>());
	Serial.println();
}
ESP_NOW esp_now = ESP_NOW(OnDataRecvDefaultCB, OnDataSentDefaultCB);

void setup() {
	/*--CAN--*/
	// can.init();

	/*--ESP-NOW--*/
	esp_now.init();
}

void loop() {
	/*--CAN--*/
	// can.read();
	// Serial.readBytesUntil(13, array, 8);
	// if (array[0] != '\0') can.send(array);
	// for (int i = 0; i < 8; i++) array[i] = '\0';

	/*--ESP-NOW--*/
	DynamicJsonDocument doc(1024);
	doc["MAC"] = WiFi.macAddress();
	doc["Name"] = "Dalek";
	esp_now.send(doc);
	delay(1000);
}
