int main2(int argc, char **arg){
	char* error;
	int n = 3;

	/*start OpenGL*/
	initOpenGL();

	/*testing system compatibility*/
	if ((error = test()) != 0){
		printf("Error: %s\n", error);
		return -1;
	}

	/*initializing system.*/
	if (!init()){
		printf("Init not successful...");
		return -1;
	}

	/*create layers using the sigmoid_sum fragment program.*/
	A = generateLayer("sigmoid_sum_masked.fp", 4, 40, 0);
	B = generateLayer("sigmoid_sum_masked.fp", 40, 16, 0);
	C = generateLayer("sigmoid_sum_masked.fp", 40, 22, 16);
	D = generateLayer("sigmoid_sum_masked.fp", 38, 5, 0);
	E = generateLayer(0, 5, 0, 0);

	setOutput(A, B);
	setInput(C, A);
	setOutput(B, D);
	setOutput(C, D);
	setOutput(D, E);

	/*dummy values.*/
	/*fill vectors with values.*/

	fillWeights(A);
	copyWeightsToTexture(weight_matrix, A);
	copyMaskToTexture(mask_matrix, A);
	free(weight_matrix);
	free(mask_matrix);

	fillWeights(B);
	copyWeightsToTexture(weight_matrix, B);
	copyMaskToTexture(mask_matrix, B);
	free(weight_matrix);
	free(mask_matrix);

	fillWeights(C);
	copyWeightsToTexture(weight_matrix, C);
	copyMaskToTexture(mask_matrix, C);
	free(weight_matrix);
	free(mask_matrix);

	fillWeights(D);
	copyWeightsToTexture(weight_matrix, D);
	copyMaskToTexture(mask_matrix, D);
	free(mask_matrix);
	free(weight_matrix);

	/*Execute the network N times.*/
	while (n-->0){
		fillVector(A);
		/*glFinish(); //finish all operations before starting the clock*/
#ifdef WIN32
		QueryPerformanceCounter(&start);
#else
		start = clock();
#endif
		copyVectorToTexture(input, A);
		run(A);
		run(B);
		run(C);
		run(D);
		printLayer(E);
		/*glFinish(); //finish all operations before stopping the clock*/
#ifdef WIN32
		QueryPerformanceCounter(&end);
		QueryPerformanceFrequency( &freq );
		printf("Time in s:%f\n", ((double)(end.QuadPart - start.QuadPart))/(double)freq.QuadPart);
#else
		end = clock();
		run_time = (end-start)/CLOCKS_PER_SEC*1000;
		printf("Time in ms: %d\n", (int)run_time);
#endif
		free(input);
	}

	/*clean up*/
	destroyLayer(A);
	destroyLayer(B);
	destroyLayer(C);
	destroyLayer(D);
	destroyLayer(E);

	return 0;
}