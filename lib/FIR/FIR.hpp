#include <Arduino.h>
#include <driver/adc.h>

class FIR {
   public:
	FIR();
	FIR(u_int16_t filterLength, float *filterCoefficients);
	~FIR();
	void init();
	void loop();

   private:
	float updateFilter(float inputValue);
	u_int16_t filterLength;
	float *filterCoefficients;
	float *inputBuffer;
};