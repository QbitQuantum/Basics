int main(int argc, char *argv[]) {
	char imageFileName[100];
	char outFileStem[100];
	char resultsFileName[100];
	char str[50];
	FILE *imgFile;

	if (argc != 3) {
		fprintf(stderr, "Error: Incorrect arguments provided\n");
		exit(-1);
	}

	strcpy(imageFileName, argv[1]);
	strcpy(outFileStem, argv[2]);

	/* Get width & height of image */
	if ((imgFile = fopen(argv[1], "r")) == NULL) {
		printf("Cannot open image file %s\n", argv[1]);
		exit(-1);
	}

	fscanf(imgFile, "%s", str); // Get the P5 string
	width = getint(imgFile);
	height = getint(imgFile);

	if (width <= 0 || height <= 0) {
		printf("Image file %s is in an invalid format\n", argv[1]);
		exit(-1);
	}

	getWindowDimensions();
	findEdges(imageFileName, outFileStem);

	sprintf(str, "%s.atts", outFileStem);
	readAttributesFile(str);
	initializeGroups();

	sprintf(resultsFileName, "Results/%s_results/%s_results_%d.txt", outFileStem, outFileStem, WINDOWS);
	if ((resultsFile = fopen(resultsFileName, "w")) == NULL) {
		fprintf(stderr, "Could not initialize results file\n");
	}

	/* Print entropy values to file */
	fprintf(resultsFile, "---- RESULTS FOR IMAGE FILE %s USING %d (rows) x %d (cols) WINDOWS ----\n", imageFileName, NUM_ROWS, NUM_COLS);
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			fprintf(resultsFile, "WINDOW (%d, %d) - Members = %d, Entropy= %2.4f\n", i, j, groupWindows[i][j].elemCount, groupWindows[i][j].calculateRenyiEntropy());
		}
	}
	fclose(resultsFile);

	/* Drawing */
	src.read(imageFileName);
	tgt.initialize(src.NR, src.NC);
	convertGroupArrayToList(groupWindows);
	drawTopFiveGroups(outFileStem);

	return 0;
}