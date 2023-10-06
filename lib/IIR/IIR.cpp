#include <IIR.hpp>

IIR::IIR() {
	this->filterLength = 3;
	this->aCoefficients = new float[3]{1, 0.97, -0.33};
	this->bCoefficients = new float[3]{1, 2, 1};
	this->inputBuffer = new float[3]{0, 0, 0};
	this->outputBuffer = new float[3]{0, 0, 0};
}

IIR::IIR(u_int16_t filterLength, float* aCoefficients, float* bCoefficients) {
	this->filterLength = filterLength;
	this->aCoefficients = aCoefficients;
	this->bCoefficients = bCoefficients;
	this->inputBuffer = new float[filterLength];
}

volatile boolean sampling = false;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

float IIR::updateFilter(float inputValue) {
	for (int i = this->filterLength - 1; i > 0; i--) {
		this->inputBuffer[i] = this->inputBuffer[i - 1];
	}
	this->inputBuffer[0] = inputValue * 0.097;

	float outputValue = 0;
	for (int i = 0; i < this->filterLength; i++) {
		outputValue += this->bCoefficients[i] * this->inputBuffer[i];
	}

	for (int i = this->filterLength - 1; i > 0; i--) {
		this->outputBuffer[i] = this->outputBuffer[i - 1];
	}
	this->outputBuffer[0] = outputValue;

	outputValue = 0;

	for (int i = 0; i < this->filterLength; i++) {
		outputValue += this->aCoefficients[i] * this->outputBuffer[i];
	}

	this->outputBuffer[0] = outputValue;

	return outputValue;
}

void IRAM_ATTR onTimer() {
	portENTER_CRITICAL_ISR(&timerMux);
	sampling = true;
	portEXIT_CRITICAL_ISR(&timerMux);
}

void IIR::init() {
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

void IIR::loop() {
	while (!sampling)
		;

	portENTER_CRITICAL(&timerMux);
	sampling = false;
	portEXIT_CRITICAL(&timerMux);

	float inputValue = analogRead(A0);
	float filteredValue = this->updateFilter(inputValue);
	// Skaliere den gefilterten Wert auf den DAC-Bereich (0-4095)
	if (filteredValue < 0) filteredValue = 0;
	int dacValue = map(filteredValue, 0, 4095, 0, 255);
	dacWrite(26, dacValue);
}

IIR::~IIR() {
	delete[] this->bCoefficients;
	delete[] this->inputBuffer;
}