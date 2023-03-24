#include "ESP_NOW.hpp"

/* void OnDataSentDefaultCB(const uint8_t *mac_addr, esp_now_send_status_t status) {
	Serial.print("\nLast Packet Send Status:\t");
	Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecvDefaultCB(const uint8_t *mac, const uint8_t *incomingData, int len) {
	DynamicJsonDocument doc(1024);
	deserializeJson(doc, incomingData);

	Serial.print("Mac: ");
	// Print mac
	for (int i = 0; i < 6; i++) {
		Serial.print(mac[i], HEX);
		if (i < 5) Serial.print(":");
	}
	Serial.print("\nName: ");
	Serial.println(doc["Name"].as<String>());
	Serial.println();
} */

ESP_NOW::ESP_NOW(esp_now_recv_cb_t onDataRecieved, esp_now_send_cb_t onDataSent) {
	this->onDataRecieved = onDataRecieved;
	this->onDataSent = onDataSent;
}

ESP_NOW::~ESP_NOW() {
}

void ESP_NOW::init() {
	Serial.begin(9600);
	WiFi.mode(WIFI_STA);
	Serial.println(WiFi.macAddress());

	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return;
	}

	esp_now_register_send_cb(onDataSent);
	esp_now_register_recv_cb(onDataRecieved);

	// Register peer
	memcpy(peerInfo.peer_addr, broadcastAddress, 6);
	peerInfo.channel = 0;
	peerInfo.encrypt = false;

	// Add peer
	if (esp_now_add_peer(&peerInfo) != ESP_OK) {
		Serial.println("Failed to add peer");
		return;
	}
}

void ESP_NOW::send(DynamicJsonDocument doc) {
	char output[100];
	serializeJson(doc, output);

	// Send message via ESP-NOW
	esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&output, sizeof(output));

	if (result == ESP_OK) {
		Serial.println("Sent with success");
	} else {
		Serial.println("Error sending the data");
	}
}
