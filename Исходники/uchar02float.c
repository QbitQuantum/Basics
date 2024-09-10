int main(int argc, char **argv)	// argv are the command-line arguments
{
 
	char infname[512], outfname[512];	// file names for input and output
	unsigned char imagetypein, imagetypeout;
	IMAGE *data;
	IMAGE *target;

	if(argc<5)		// too few command-line arguments?
	{
		printf("Command-line usage:\n");
		printf("   %s (inf) (outf) (x) (y)\n",argv[0]);
		printf("   (inf)  is the input file name\n");
		printf("   (outf) is the output file name\n");
		printf("   (x), (y) are the image dimensions\n");
		exit(0);
	}

	// Allocate local memory for struct pointers
	data = malloc(sizeof(IMAGE));

	// Handle Command Line args
	strcpy(infname,nextargs);	// read input file name
	strcpy(outfname,nextargs);	// read output file name
	data->xmax = nextargi;		// Read image dimensions
	data->ymax = nextargi; 
	//data->zmax = nextargi;
	data->zmax = 1;

	// params set image data types in and out
	imagetypein  = UCHARIMAGE;
	imagetypeout = FLOATIMAGE;

	// Read Image into Mem
	printf("Reading image %s with dimensions %d, %d, %d\n",infname,data->xmax,data->ymax,data->zmax);
	if(read_raw(infname, data)){  printf("Error reading file\n");  exit (1);  }

	// Set target params, Allocate local memory
  	target = malloc(sizeof(IMAGE));
	if(copyimage(target, data, imagetypeout)){  fprintf(stderr,"Could not Create Image: target\n");  exit(-1);  }

	/* Image Processing calls here */
	printf("   Converting Data Types...\n");
	//switch case with command line parameters to specify data type conversions
	if(uchar2float(target, data)){ printf("Error Converting\n");  exit(3); }

	// Write Image to File
	printf("Writing processed image %s with dimensions %d, %d, %d\n",outfname,target->xmax,target->ymax,target->zmax);
	if(write_raw(outfname, target)){  printf("Error writing file\n");  exit (4);  }

	// Free All Memory
	removeimage(data,imagetypein);
	removeimage(target,imagetypeout);
	printf("Program completed successfully\n");
	exit (0);

}