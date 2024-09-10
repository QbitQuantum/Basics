void Satin::gaussianCalculation(int inputPower, float smallSignalGain, char outputFile[]) {
	ofstream fd;
	double temp;
	double *expr;
	double zInc;
	double inputIntensity;
	double outputIntensity;
	double outputPower;
	float radius;
	int saturationIntensity;

	fd.open(outputFile, ios::in | ios::app);
	inputIntensity = 2 * inputPower / AREA;

	set_new_handler(noMemory);
	expr = new double[8 * 8001];

	for (int i = 0; i < 8001; i++) {
		zInc = ((double) i - 4000) / 25;
		expr[i] = zInc * 2 * DZ / (Z1 * Z1 + zInc * zInc);
	}

	for (saturationIntensity = 10000; saturationIntensity <= 25000; saturationIntensity += 1000) {
		outputPower = 0;
		temp = (double) saturationIntensity * (smallSignalGain / 32000) * DZ;

		for (radius = 0; radius <= 0.5; radius += DR) {
			outputIntensity = inputIntensity * exp(-2 * (radius * radius) / (RAD * RAD));

			for (int j = 0; j < 8001; j++) {
				outputIntensity *= (1 + temp / ((double) saturationIntensity + outputIntensity) - expr[j]);
			}

			outputPower += (outputIntensity * 2 * M_PI * radius * DR);
		}

		fd << setiosflags(ios::fixed)
		   << setprecision(1)
		   << inputPower
		   << "\t\t"
		   << setprecision(3)
		   << outputPower
		   << setiosflags(ios::fixed)
		   << setprecision(1)
		   << "\t\t"
		   << saturationIntensity
		   << "\t\t"
		   << setprecision(3)
		   << log(outputPower / inputPower)
		   << "\t\t"
		   << (outputPower - inputPower)
		   << "\n";
	}

	fd.flush();
	fd.close();
	delete expr;
}