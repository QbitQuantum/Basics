int main(int argc, char *argv[]) {
	char imageFileName[100];
	char outFileStem[100];
	char textFilename[100];
	char entropyFilename[100];
	char str[50];
	FILE *textFile;
	FILE *entropyFile;
	bool draw = false;

	/*
	 * Check command line arguments
	 */
	if (argc != 3) {
		fprintf(stderr, "Error: Incorrect arguments provided\n");
		fprintf(stderr, "\tUSAGE: ./ScaleSpace [IMAGE] [IMAGE_NAME]\n");
		fprintf(stderr, "\te.g. ./ScaleSpace ads.pgm ads\n");
		exit(-1);
	}

	/*
	 * Miscellaneous steps that must be taken
	 */
	strcpy(imageFileName, argv[1]);
	strcpy(outFileStem, argv[2]);
	if (atoi(argv[3]) == 1) draw = true;
	printf("Starting scale space processing of image %s\n", imageFileName);

	getWidthAndHeight(imageFileName);
	findEdges(imageFileName, outFileStem);

	src.read(imageFileName);
	tgt.initialize(src.NR, src.NC);

	/*
	 * Either perform the scale processing or draw the scales of a
	 * few select pixels.
	 */
	if (!draw) {
		sprintf(str, "texts/%s_GD.txt", outFileStem);
		readGradientFile(str);
		sprintf(str, "texts/%s_MAG.txt", outFileStem);
		readMagnitudesFile(str);

		sprintf(textFilename, "texts/%s_scale_space.txt", outFileStem);
		if ((textFile = fopen(textFilename, "w")) == NULL) {
			fprintf(stderr, "Cannot open text file %s for printing scale space values\n", textFilename);
			exit(-1);
		}

		sprintf(entropyFilename, "texts/%s_scale_space_entropy.txt", outFileStem);
		if ((entropyFile = fopen(entropyFilename, "w")) == NULL) {
			fprintf(stderr, "Cannot open text file %s for printing scale space values\n", entropyFilename);
			exit(-1);
		}

		/*
		 * Initialize scale space and max scale entropies arrays
		 */
		scaleSpaceValues = (int *) malloc(width * height * sizeof(int));
		maxScaleEntropies = (float *) malloc(width * height * sizeof(float));

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				scaleSpaceValues[(i * width) + j] = 0;
				maxScaleEntropies[(i * width) + j] = 0;
			}
		}

		/*
		 * Process Pixels in Parallel
		 */
		srand(time(NULL));
		int rowsPerThread = (int) ceil(height / NUM_THREADS);

		int currRows = 0;
		for (int i = 0; i < NUM_THREADS; i++) {
			threadInfo[i].id = i + 1;
			threadInfo[i].rowStart = currRows;
			threadInfo[i].rowEnd = currRows + rowsPerThread;
			currRows += rowsPerThread;

			int returnVal = pthread_create(&threads[i], NULL, threadProcess, (void *) &threadInfo[i]);
		}

		for(int i=0; i < NUM_THREADS; i++) {
			/*
			 * Must ensure that the main thread waits for children, otherwise we may
			 * run the risk of executing an exit which will terminate the process
			 * and all its children.
			 */
			pthread_join(threads[i], NULL);
		}

		/*
		 * Output information
		 */
		sprintf(str, "maps/%s_scale_map.pgm", outFileStem);
		tgt.save(str);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				fprintf(textFile, "%d ", scaleSpaceValues[(i * width) + j]);
			}
			fprintf(textFile, "\n");
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				fprintf(entropyFile, "%2.5f ", maxScaleEntropies[(i * width) + j]);
			}
			fprintf(entropyFile, "\n");
		}

		/*
		 * Clean up and close
		 */
		fclose(textFile);
		fclose(entropyFile);
		free(gradDirections);
		free(magnitudes);
		free(scaleSpaceValues);
		pthread_mutex_destroy(&writeMutex);

	} else {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				tgt(i, j, RED) = src(i, j, RED);
				tgt(i, j, GREEN) = src(i, j, RED);
				tgt(i, j, BLUE) = src(i, j, RED);
			}
		}

		sprintf(textFilename, "texts/%s_scale_space.txt", outFileStem);
		srand(time(NULL));
		drawScales(textFilename);

		sprintf(str, "maps/%s_scales.ppm", outFileStem);
		tgt.save(str);
	}

	printf("Finished processing\n");
	pthread_exit(0);

	return 0;
}