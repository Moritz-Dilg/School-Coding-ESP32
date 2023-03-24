#include <ArduinoJson.h>
#include <WiFi.h>
#include <esp_now.h>

class ESP_NOW {
   public:
	ESP_NOW(esp_now_recv_cb_t onDataRecieved, esp_now_send_cb_t onDataSent);
	~ESP_NOW();
	void init();
	void send(DynamicJsonDocument doc);

   private:
	esp_now_send_cb_t onDataSent;
	esp_now_recv_cb_t onDataRecieved;
	uint8_t broadcastAddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	esp_now_peer_info_t peerInfo;
};