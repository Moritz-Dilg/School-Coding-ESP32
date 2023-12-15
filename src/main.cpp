#include <Arduino.h>

#include <ESP_NOW.hpp>
#include <FIR.hpp>
#include <IIR.hpp>
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
/*
-0.0004872245858301694
-0.002815732104702255
-0.008151699315969747
-0.0141073783734772
-0.011622597681533392
0.012637934744367564
0.06620569890643453
0.13947460447830148
0.20479027488652032
0.2311025556079767
0.20479027488652032
0.13947460447830148
0.06620569890643453
0.012637934744367564
-0.011622597681533392
-0.0141073783734772
-0.008151699315969747
-0.002815732104702255
-0.0004872245858301694
*/

float* coefficients = new float[19]{-0.0004872245858301694,
									-0.002815732104702255,
									-0.008151699315969747,
									-0.0141073783734772,
									-0.011622597681533392,
									0.012637934744367564,
									0.06620569890643453,
									0.13947460447830148,
									0.20479027488652032,
									0.2311025556079767,
									0.20479027488652032,
									0.13947460447830148,
									0.06620569890643453,
									0.012637934744367564,
									-0.011622597681533392,
									-0.0141073783734772,
									-0.008151699315969747,
									-0.002815732104702255,
									-0.0004872245858301694};
FIR fir = FIR(19, coefficients);

/*--IIR--*/
// IIR iir = IIR();

void setup() {
	/*--CAN--*/
	// can.init();

	/*--ESP-NOW--*/
	// esp_now.init();

	/*--MQTT--*/
	// mqtt.connect();

	/*--FIR--*/
	fir.init();

	/*--IIR--*/
	// iir.init();
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

	/*--IIR--*/
	// iir.loop();
}
