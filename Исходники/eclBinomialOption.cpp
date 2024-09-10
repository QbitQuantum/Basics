int main(int argc, char *argv[])
{
	gmactime_t s, t, S, T; 

	cl_float* randArray = NULL;
	cl_float* output = NULL;
	cl_float* refOutput;
	cl_int numSamples = 64;
	getTime(&S);
	getTime(&s);
	assert(ecl::compileSource(code) == eclSuccess);
	setParam<cl_int>(&numSteps, numStepsStr, numStepsDefault);
	// Alloc & init data
	randArray = new (ecl::allocator) cl_float[numSamples * sizeof(cl_float4)];
	output = new (ecl::allocator) cl_float[numSamples * sizeof(cl_float4)];
	assert(randArray != NULL);
	assert(output != NULL);
	refOutput = (float*)malloc(numSamples * sizeof(cl_float4));
	if(refOutput == NULL)
		return 0;
	getTime(&t);
	printTime(&s, &t, "Alloc: ", "\n");
	getTime(&s);
	/* random initialisation of input */
	for(int i = 0; i < numSamples * 4; i++) {
		randArray[i] = (float)rand() / (float)RAND_MAX;
	}
	valueInit(output, 0, numSamples * 4);
	getTime(&t);
	printTime(&s, &t, "Init: ", "\n");
	getTime(&s);
	ecl::config globalSize(numSamples * (numSteps + 1));
	ecl::config localSize(numSteps + 1);

	ecl::error err;
	ecl::kernel kernel("binomial_options", err);
	assert(err == eclSuccess);
#ifndef __GXX_EXPERIMENTAL_CXX0X__
	assert(kernel.setArg(0, numSteps) == eclSuccess);
	assert(kernel.setArg(1, randArray) == eclSuccess);
	assert(kernel.setArg(2, output) == eclSuccess);
	assert(kernel.setArg(3, (cl_float4 *)NULL) == eclSuccess);
	assert(kernel.setArg(4, (cl_float4 *)NULL) == eclSuccess);
	assert(kernel.callNDRange(globalSize, localSize) == eclSuccess);
#else
	assert(kernel(globalSize, localSize)(numSteps, randArray, output, NULL, NULL) == eclSuccess);
#endif
	getTime(&t);
	printTime(&s, &t, "Run: ", "\n");
	printf("Output: ");
	for(int i = 0; i < numSamples; i++) {
		printf("%f ", output[i]);
	}

	getTime(&s);
	bool result = 1;
	binomialOptionCPUReference(refOutput, randArray, numSamples, numSteps);
	float error = 0.0f;
	float ref = 0.0f;

	for(int i = 1; i < numSamples; ++i) {
		float diff = output[i] - refOutput[i];
		error += diff * diff;
		ref += output[i] * output[i];
	}

	float normRef =::sqrtf((float) ref);
	if (::fabs((float) ref) < 1e-7f) {
		result = 0;
	}
	if(result) {
		float normError = ::sqrtf((float) error);
		error = normError / normRef;
		result = error < 0.001f;
	}
	if(result)
		printf("\nPassed!\n");
	else
		printf("\nFailed!\n");
	getTime(&t);
	printTime(&s, &t, "Check: ", "\n");
	getTime(&T);
	printTime(&S, &T, "Total: ", "\n");
	getTime(&s);
	free(refOutput);
	refOutput = NULL;
	ecl::free(randArray);
	ecl::free(output);
	getTime(&t);
	printTime(&s, &t, "Free: ", "\n");
	return 0;
}