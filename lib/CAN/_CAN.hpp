#include <CAN.h>
#include <TFT_eSPI.h>

#include <CAN_receiver.hpp>
#include <CAN_transmitter.hpp>

class _CAN {
   public:
	_CAN();
	~_CAN();
	void init();
	void send(char* data);
	char* read();
};