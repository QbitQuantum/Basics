void GP2Y10::readDust(float *dust) {
	// results are computed for a 5V voltage and a 10bit adc
	float adcVoltage =  readRaw() * (5.0 / 1024);
	// see why we have this limit on: http://www.pocketmagic.net/sharp-gp2y10-dust-sensor/
	if (adcVoltage < 0.583)
		*dust = 0;
	else
	 	*dust =  6 * adcVoltage / 35 - 0.1;
}