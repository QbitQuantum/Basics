void LMGraph::loadFromFiles(const char *graphFileName, const char *offsetsFileName, const int h) {

	unLoad();

	// read graph file
	FILE *f = fopen(graphFileName, "rb");
	if(f == NULL) {
		printf("Couldn't open %s for reading.\n", graphFileName);
		return;
	}
	_fseeki64(f, 0, SEEK_END);
	graphPos = graphSize = (unsigned int)_ftelli64(f);
	rewind(f);
	graphBuffer = new unsigned char [ graphSize ];
	if(graphBuffer == NULL) {
		fclose(f);
		return;
	}
	fread(graphBuffer, 1, graphSize, f);
	fclose(f);

	// read offsets file
	f = fopen(offsetsFileName, "rb");
	if(f == NULL) {
		printf("Couldn't open %s for reading.\n", offsetsFileName);
		return;
	}
	_fseeki64(f, 0, SEEK_END);
	int fSize = (int)_ftelli64(f);
	rewind(f);
	offsetsCnt = (fSize - 16) >> 2;
	if(offsetsCnt < 2) {
		delete[] graphBuffer;
		fclose(f);
		return;
	}
	offsets = new unsigned int [offsetsCnt];
	fread(&numNodes, 4, 1, f);
	fread(&maxSuccListLength, 4, 1, f);
	fread(&maxResidListLength, 4, 1, f);
	fread(&maxUncomprSize, 4, 1, f);
	fread(offsets, 4, offsetsCnt, f);

	this->h = h;

	loaded = true;
}