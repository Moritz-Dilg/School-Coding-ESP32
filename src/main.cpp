#include <Arduino.h>

#include <ESP_NOW.hpp>
#include <FIR.hpp>
#include <MQTT.hpp>
#include <_CAN.hpp>

/*--CAN--*/
// _CAN can = _CAN();
// char array[8];

/*--ESP-NOW--*/
// void OnDataSentDefaultCB(const uint8_t *mac_addr, esp_now_send_status_t status) {
//	Serial.println("\nLast Packet Send Status:\t" + (status == ESP_NOW_SEND_SUCCESS) ? "Successfully sent" : "Sending failed");
// }
//
// void OnDataRecvDefaultCB(const uint8_t *mac, const uint8_t *incomingData, int len) {
// 	DynamicJsonDocument doc(1024);
// 	deserializeJson(doc, incomingData);
//
// 	Serial.print("Mac: ");
// 	for (int i = 0; i < 6; i++) {
// 		Serial.print(mac[i], HEX);
// 		if (i < 5) Serial.print(":");
// 	}
// 	Serial.print("\nName: ");
// 	Serial.println(doc["Name"].as<String>());
// 	Serial.println();
// }
// ESP_NOW esp_now = ESP_NOW(OnDataRecvDefaultCB, OnDataSentDefaultCB);

/*--MQTT--*/
// void callback(char *topic, byte *payload, unsigned int length) {
//	Serial.print("[" + String(topic) + "] ");
//	for (int i = 0; i < length; i++) {
//		Serial.print((char)payload[i]);
//	}
//	Serial.println();
// }
//
// MQTT mqtt = MQTT(callback);

/*--FIR--*/
FIR fir = FIR();

void setup() {
	/*--CAN--*/
	// can.init();

	/*--ESP-NOW--*/
	// esp_now.init();

	/*--MQTT--*/
	// mqtt.connect();

	/*--FIR--*/
	fir.init();
}

void loop() {
	/*--CAN--*/
	// can.read();
	// Serial.readBytesUntil(13, array, 8);
	// if (array[0] != '\0') can.send(array);
	// for (int i = 0; i < 8; i++) array[i] = '\0';

	/*--ESP-NOW--*/
	// DynamicJsonDocument doc(1024);
	// doc["MAC"] = WiFi.macAddress();
	// doc["Name"] = "Dalek";
	// esp_now.send(doc);
	// delay(1000);

	/*--MQTT--*/
	// mqtt.publish("DIC/Button", "Hello World!");
	// mqtt.loop();

	/*--FIR--*/
	fir.loop();
}
