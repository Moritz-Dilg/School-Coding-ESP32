#include <CAN.h>

class CAN_transmitter {
   public:
	CAN_transmitter();
	void init();
	void send(char* text);
};