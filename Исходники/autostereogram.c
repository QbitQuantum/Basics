int main(int argc, char **argv)	// argv are the command-line arguments
{
 
	char infname[512], outfname[512];	// file names for input and output
	IMAGE *data;
	IMAGE *target;

	if(argc<5)		// too few command-line arguments?
	{
		printf("Command-line usage:\n");
		printf("   %s (inf) (outf) (x) (y)\n",argv[0]);
		printf("   (inf)  is the input file name\n");
		printf("   (outf) is the output file name\n");
		printf("   (x), (y) are the image dimensions\n");
		//printf("   (x), (y), (z) are the image dimensions\n");
		exit(0);
	}

	// Allocate local memory for struct pointers
	data = malloc(sizeof(IMAGE));

	// Handle Command Line args
	strcpy(infname,nextargs);	// read input file name
	strcpy(outfname,nextargs);	// read output file name
	data->xmax = nextargi;		// Read image dimensions
	data->ymax = nextargi; 
	data->zmax = 1;	//nextargi;

	// Read Image, Allocate Img mem
	printf("Reading image %s with dimensions %d, %d, %d\n",infname,data->xmax,data->ymax,data->zmax);
	if(read_raw(infname, data)){ printf("Error reading file\n");  exit (1);	}

	// Set target params, Allocate local memory
  	target = malloc(sizeof(IMAGE));
	if(copyimage(target, data)){ fprintf(stderr,"Could not Create Image: target\n");  exit(-1); }

	/* Image Processing calls here */
	printf("   Drawing AutoStereogram...\n");
	if(heightmap(data)){ printf("Error Making Height Map\n");  exit(3); }
	if(DrawAutoStereogram(target, data)){ printf("Error Generating SIRDS\n");  exit(3); }

	// Write Image
	printf("Writing processed image %s with dimensions %d, %d, %d\n",outfname,target->xmax,target->ymax,target->zmax);
	if(write_raw(outfname, target)){ printf("Error writing file\n");  exit (4); }

	// Free All Memory
	removeimage(data);
	removeimage(target);
	printf("Program completed successfully\n");
	exit (0);

}