#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <WiFi.h>

class MQTT {
   public:
	typedef void (*mqtt_callback)(char *topic, byte *payload, unsigned int length);
	MQTT(mqtt_callback callback);
	MQTT(mqtt_callback callback, String ssid, String password, String mqtt_server, int mqtt_port);
	~MQTT();
	void connect();
	void publish(String topic, String payload);
	void publish(String topic, int payload);
	void publish(String topic, double payload);
	void publish(String topic, DynamicJsonDocument &payload);
	void loop();

   private:
	void reconnect();

	String ssid;
	String password;
	String mqtt_server;
	int mqtt_port;
	mqtt_callback callback;
	WiFiClient wifi;
	PubSubClient client;
};