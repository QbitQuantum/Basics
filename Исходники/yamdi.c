int main(int argc, char *argv[]) {
	FILE *fp_infile = NULL, *fp_outfile = NULL, *fp_xmloutfile = NULL, *devnull;
#ifdef __MINGW32__
	HANDLE fh_infile = NULL;
#endif
	int c, lastsecond = 0, lastkeyframe = 0, unlink_infile = 0;
	char *flv, *infile, *outfile, *xmloutfile, *tempfile, *creator;
	unsigned int i;
	size_t filesize = 0, streampos, metadatasize;
	struct stat sb;
	FLVFileHeader_t *flvfileheader;

	opterr = 0;

	infile = NULL;
	outfile = NULL;
	xmloutfile = NULL;
	tempfile = NULL;
	creator = NULL;

	while((c = getopt(argc, argv, "i:o:x:t:c:lkh")) != -1) {
		switch(c) {
			case 'i':
				infile = optarg;
				break;
			case 'o':
				outfile = optarg;
				break;
			case 'x':
				xmloutfile = optarg;
				break;
			case 't':
				tempfile = optarg;
				break;
			case 'c':
				creator = optarg;
				break;
			case 'l':
				lastsecond = 1;
				break;
			case 'k':
				lastkeyframe = 1;
				break;
			case 'h':
				print_usage();
				exit(1);
				break;
			case ':':
				fprintf(stderr, "The option -%c expects a parameter. -h for help.\n", optopt);
				exit(1);
				break;
			case '?':
				fprintf(stderr, "Unknown option: -%c. -h for help.\n", optopt);
				exit(1);
				break;
			default:
				print_usage();
				exit(1);
				break;
		}
	}

	if(infile == NULL) {
		fprintf(stderr, "Please provide an input file. -h for help.\n");
		exit(1);
	}

	if(outfile == NULL && xmloutfile == NULL) {
		fprintf(stderr, "Please provide at least one output file. -h for help.\n");
		exit(1);
	}

	if(tempfile == NULL && !strcmp(infile, "-")) {
		fprintf(stderr, "Please specify a temporary file. -h for help.\n");
		exit(1);
	}

	// Check input file
	if(!strcmp(infile, "-")) {		// Read from stdin
		// Check the temporary file
		if(outfile != NULL) {
			if(!strcmp(tempfile, outfile)) {
				fprintf(stderr, "The temporary file and the output file must not be the same.\n");
				exit(1);
			}
		}

		if(xmloutfile != NULL) {
			if(!strcmp(tempfile, xmloutfile)) {
				fprintf(stderr, "The temporary file and the XML output file must not be the same.\n");
				exit(1);
			}
		}

		// Open the temporary file
		fp_infile = fopen(tempfile, "wb");
		if(fp_infile == NULL) {
			fprintf(stderr, "Couldn't open the tempfile %s.\n", tempfile);
			exit(1);
		}

		// Store stdin to temporary file
		storeFLVFromStdin(fp_infile);

		// Close temporary file
		fclose(fp_infile);

		// Mimic normal input file, but don't forget to remove the temporary file
		infile = tempfile;
		unlink_infile = 1;
	}
	else {
		if(outfile != NULL) {
			if(!strcmp(infile, outfile)) {
				fprintf(stderr, "The input file and the output file must not be the same.\n");
				exit(1);
			}
		}

		if(xmloutfile != NULL) {
			if(!strcmp(infile, xmloutfile)) {
				fprintf(stderr, "The input file and the XML output file must not be the same.\n");
				exit(1);
			}
		}
	}

	// Get size of input file
	if(stat(infile, &sb) == -1) {
		fprintf(stderr, "Couldn't stat on %s.\n", infile);
		exit(1);
	}

	filesize = sb.st_size;

	// Open input file
#ifndef __MINGW32__
	fp_infile = fopen(infile, "rb");
#else
	// Open infile with CreateFile() API
	fh_infile = CreateFile(infile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	// Meaningless type casting here. It is just used to pass the error checking codes.
	fp_infile = (FILE *)fh_infile;
#endif
	if(fp_infile == NULL) {
		fprintf(stderr, "Couldn't open %s.\n", infile);
		exit(1);
	}

	// Check output file
	if(outfile != NULL) {
		if(!strcmp(infile, outfile)) {
			fprintf(stderr, "The input file and the output file must not be the same.\n");
			exit(1);
		}

		if(strcmp(outfile, "-")) {
			fp_outfile = fopen(outfile, "wb");
			if(fp_outfile == NULL) {
				fprintf(stderr, "Couldn't open %s.\n", outfile);
				exit(1);
			}
		}
		else
			fp_outfile = stdout;
	}

	// Check XML output file
	if(xmloutfile != NULL) {
		if(!strcmp(infile, xmloutfile)) {
			fprintf(stderr, "The input file and the XML output file must not be the same.\n");
			exit(1);
		}

		if(!strcmp(outfile, xmloutfile)) {
			fprintf(stderr, "The output file and the XML output file must not be the same.\n");
			exit(1);
		}

		if(strcmp(xmloutfile, "-")) {
			fp_xmloutfile = fopen(xmloutfile, "wb");
			if(fp_xmloutfile == NULL) {
				fprintf(stderr, "Couldn't open %s.\n", xmloutfile);
				exit(1);
			}
		}
		else
			fp_xmloutfile = stdout;
	}

	// create mmap of input file
#ifndef __MINGW32__
	flv = mmap(NULL, filesize, PROT_READ, MAP_NOCORE | MAP_PRIVATE, fileno(fp_infile), 0);
	if(flv == MAP_FAILED) {
		fprintf(stderr, "Couldn't load %s (%s).\n", infile, strerror(errno));
		exit(1);
	}

#else
	HANDLE h = NULL;
	h = CreateFileMapping(fh_infile, NULL, PAGE_READONLY | SEC_COMMIT, 0, filesize,  NULL);
	if(h == NULL) {
		fprintf(stderr, "Couldn't create file mapping object %s. Error code: %d\n", infile, (int)GetLastError());
		exit(1);
	}
	flv = MapViewOfFile(h, FILE_MAP_READ, 0, 0, filesize);
	if(flv == NULL) {
		fprintf(stderr, "Couldn't load %s.\n", infile);
		exit(1);
	}
#endif

	// Simple check if the filee is a flv file
	if(strncmp(flv, "FLV", 3)) {
		fprintf(stderr, "The input file is not a FLV.\n");
		exit(1);
	}

	// Metadata initialisieren
	initFLVMetaData(creator, lastsecond, lastkeyframe);

	flvfileheader = (FLVFileHeader_t *)flv;

	// Die Position des 1. Tags im FLV bestimmen (Header + PrevTagSize0)
	streampos = FLV_UI32(flvfileheader->headersize) + 4;

	// Das FLV einlesen und Informationen fuer die Metatags extrahieren
	readFLVFirstPass(flv, streampos, filesize);

#ifndef __MINGW32__
	devnull = fopen("/dev/null", "wb");
#else
	devnull = fopen("nul", "wb");
#endif

	if(devnull == NULL) {
		fprintf(stderr, "Couldn't open NULL device.\n");
		exit(1);
	}

	// Die Groessen berechnen
	metadatasize = writeFLVMetaData(devnull);
	flvmetadata.lastsecondsize = writeFLVLastSecond(devnull, 0.0);
	flvmetadata.lastkeyframesize = writeFLVLastKeyframe(devnull);	// Not fully implemented, i.e. has no effect

	fclose(devnull);

	// Falls es Keyframes hat, muss ein 2. Durchgang fuer den Keyframeindex gemacht werden
	if(flvmetadata.hasKeyframes == 1) {
		readFLVSecondPass(flv, streampos, filesize);

		// Die Filepositions korrigieren
		for(i = 0; i < flvmetadata.keyframes; i++)
			flvmetadata.filepositions[i] += (double)(sizeof(FLVFileHeader_t) + 4 + metadatasize);

		flvmetadata.lastkeyframelocation = flvmetadata.filepositions[flvmetadata.keyframes - 1];
	}

	// filesize = FLVFileHeader + PreviousTagSize0 + MetadataSize + DataSize
	flvmetadata.filesize = (double)(sizeof(FLVFileHeader_t) + 4 + metadatasize + flvmetadata.datasize);
	if(flvmetadata.hasLastSecond == 1)
		flvmetadata.filesize += (double)flvmetadata.lastsecondsize;

	if(outfile != NULL)
		writeFLV(fp_outfile, flv, streampos, filesize);

	if(xmloutfile != NULL)
		writeXMLMetadata(fp_xmloutfile, infile, outfile);

	// Some cleanup
#ifndef __MINGW32__
	munmap(flv, filesize);
	fclose(fp_infile);
#else
	UnmapViewOfFile(flv);
	CloseHandle(h);
	CloseHandle(fh_infile);
#endif

	// Remove the input file if it is the temporary file
	if(unlink_infile == 1)
		unlink(infile);

	if(fp_outfile != NULL && fp_outfile != stdout)
		fclose(fp_outfile);

	if(fp_xmloutfile != NULL && fp_xmloutfile != stdout)
		fclose(fp_xmloutfile);

	return 0;
}