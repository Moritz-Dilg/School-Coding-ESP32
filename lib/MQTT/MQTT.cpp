#include "MQTT.hpp"

MQTT::MQTT(mqtt_callback callback) : MQTT::MQTT(callback, "A", "123456789", "broker.hivemq.com", 1883) {}

MQTT::MQTT(mqtt_callback callback, String ssid, String password, String mqtt_server, int mqtt_port) {
	this->callback = callback;
	this->ssid = ssid;
	this->password = password;
	this->mqtt_server = mqtt_server;
	this->mqtt_port = mqtt_port;
}

MQTT::~MQTT() {
	client.disconnect();
}

void MQTT::connect() {
	delay(500);
	Serial.begin(9600);

	WiFi.begin(ssid.c_str(), password.c_str());
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	client = PubSubClient(wifi);

	client.setCallback(this->callback);
	client.setServer("broker.hivemq.com", 1883);
	delay(500);
}

void MQTT::publish(String topic, String payload) {
	client.publish(topic.c_str(), payload.c_str());
}

void MQTT::publish(String topic, int payload) {
	publish(topic, String(payload));
}

void MQTT::publish(String topic, double payload) {
	publish(topic, String(payload));
}

void MQTT::publish(String topic, DynamicJsonDocument &payload) {
	String payloadString;
	serializeJson(payload, payloadString);
	publish(topic, payloadString);
}

void MQTT::loop() {
	if (!client.connected()) {
		reconnect();
	}
	client.loop();
}

void MQTT::reconnect() {
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		if (client.connect("6534165032")) {
			Serial.println("connected");
			if (client.subscribe("DIC/Button")) Serial.println("Subscribed to DIC/Button");
		} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			delay(5000);
		}
	}
}