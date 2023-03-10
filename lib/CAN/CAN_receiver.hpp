#include <CAN.h>

class CAN_receiver {
   public:
	CAN_receiver();
	void init();
	char* read();
};