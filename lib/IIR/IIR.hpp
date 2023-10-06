#include <Arduino.h>
#include <driver/adc.h>

class IIR {
   public:
	IIR();
	IIR(u_int16_t filterLength, float *aCoefficients, float *bCoefficients);
	~IIR();
	void init();
	void loop();

   private:
	float updateFilter(float inputValue);
	u_int16_t filterLength;
	float *aCoefficients;
	float *bCoefficients;
	float *inputBuffer;
	float *outputBuffer;
};