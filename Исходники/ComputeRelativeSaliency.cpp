int main(int argc, char *argv[]) {
	char imageFileName[100];
	char outFileStem[100];
	char resultsFileName[100];
	char shanFileName[100];
	char renyiFilename[100];
	char shannonFilename[100];
	char str[50];
	int window;
	int dimension;
	int percentage;

	if (argc != 6) {
		fprintf(stderr, "Error: Incorrect arguments provided\n");
		fprintf(stderr, "\tUSAGE: ./ComputeSaliency [IMAGE] [IMAGE_NAME] [WINDOW] [SQUARE_HISTOGRAM_DIMENSION] [SAMPLING]\n");
		fprintf(stderr, "\te.g. ./ComputeSaliency ads.pgm ads 11 10 5\n");
		exit(-1);
	}

	strcpy(imageFileName, argv[1]);
	strcpy(outFileStem, argv[2]);
	window = atoi(argv[3]);
	dimension = atoi(argv[4]);
	percentage = atoi(argv[5]);

	getWidthAndHeight(imageFileName);
	findEdges(imageFileName, outFileStem);

	sprintf(str, "texts/%s_GD.txt", outFileStem);
	readGradientFile(str);

	sprintf(str, "texts/%s_MAG.txt", outFileStem);
	readMagnitudesFile(str);
	eliminateLowMagnitudes();

	src.read(imageFileName);
	rel.initialize(src.NR, src.NC);
	shan.initialize(src.NR, src.NC);

	sprintf(resultsFileName, "maps/%s_rel_%d.pgm", outFileStem, window);
	sprintf(renyiFilename, "texts/%s_rel_%d.txt", outFileStem, window);

	processPixelsForEntropy(window, dimension, percentage, renyiFilename);
	rel.save(resultsFileName);

	free(gradDirections);
	free(magnitudes);
	free(entropies);

	return 0;
}