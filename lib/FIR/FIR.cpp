#include <FIR.hpp>

FIR::FIR() {
	this->filterLength = 5;
	this->filterCoefficients = new float[5]{0.1, 0.2, 0.4, 0.2, 0.1};
	this->inputBuffer = new float[5]{0, 0, 0, 0, 0};
}

FIR::FIR(u_int16_t filterLength, float* filterCoefficients) {
	this->filterLength = filterLength;
	this->filterCoefficients = filterCoefficients;
	this->inputBuffer = new float[filterLength];
}

volatile boolean sampling = false;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

float FIR::updateFilter(float inputValue) {
	for (int i = this->filterLength - 1; i > 0; i--) {
		this->inputBuffer[i] = this->inputBuffer[i - 1];
	}
	this->inputBuffer[0] = inputValue;

	float outputValue = 0;
	for (int i = 0; i < this->filterLength; i++) {
		outputValue += this->filterCoefficients[i] * this->inputBuffer[i];
	}

	return outputValue;
}

void IRAM_ATTR onTimer() {
	portENTER_CRITICAL_ISR(&timerMux);
	sampling = true;
	portEXIT_CRITICAL_ISR(&timerMux);
}

void FIR::init() {
	// Init ADC
	pinMode(ADC1_CHANNEL_0, INPUT);
	adc1_config_width(ADC_WIDTH_12Bit);							// 12-Bit Resolution
	adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_11db);	// Input voltage 0-2.6V

	// Timer interrupt for 8kHz sampling frequency
	hw_timer_t* timer = timerBegin(0, 80, true);
	timerAttachInterrupt(timer, &onTimer, true);
	timerAlarmWrite(timer, 125, true);	// sampling frequency 8kHz
	timerAlarmEnable(timer);
}

void FIR::loop() {
	while (!sampling)
		;

	portENTER_CRITICAL(&timerMux);
	sampling = false;
	portEXIT_CRITICAL(&timerMux);

	float inputValue = analogRead(A0);
	float filteredValue = this->updateFilter(inputValue);
	// Skaliere den gefilterten Wert auf den DAC-Bereich (0-4095)
	int dacValue = map(filteredValue, 0, 4095, 0, 255);
	dacWrite(26, dacValue);
}

FIR::~FIR() {
	delete[] this->filterCoefficients;
	delete[] this->inputBuffer;
}