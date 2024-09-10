int cropImage(FILE* inFile, struct bmpFileHeader* fileHead, 
	struct bmpInfoHeader* infoHead, char* outFileName, int cropWidth, 
	int cropHeight, int cropStart[])
{
	// check that cropping parameters make sense
	if (((cropWidth + cropStart[0]) > infoHead->width) || 
		((cropHeight + cropStart[1]) > infoHead->height))
	{
		fprintf(stderr, "Cropping parameters incorrect.\n");
		return EXIT_FAILURE;
	}

	// open file for writing
	FILE *outFile = fopen(outFileName, "w+");

	// check that file opened okay
	if (outFile == NULL)
	{
		fprintf(stderr, "Unable to open file: %s for writing.\n", outFileName);
		return EXIT_FAILURE;
	}

	// store old width/height for use in loop
	LONG oldWidth = infoHead->width;
	LONG oldHeight = infoHead->height;

	// calculate padding used in old image
	int oldPadding = (4 - (oldWidth*sizeof(struct pixel) % 4)) % 4;

	// calculate padding to be used in new image
	int newPadding = (4 - (cropWidth*sizeof(struct pixel) % 4)) % 4;

	// new image size
	infoHead->imageSize = (cropWidth*sizeof(struct pixel) + 
		newPadding)*cropHeight;

	// file size
	fileHead->fileSize = sizeof(struct bmpFileHeader) + 
		sizeof(struct bmpInfoHeader) + infoHead->imageSize;

	// new dimensions
	infoHead->width = cropWidth;
	infoHead->height = cropHeight;

	// write the headers to the output file, checking for errors
	if (writeFileHeader(fileHead, outFile) != 0)
	{
		fprintf(stderr, "Unable to write file header.\n");
		return EXIT_FAILURE;
	}

	if (writeInfoHeader(infoHead, outFile) != 0)
	{
		fprintf(stderr, "Unable to write info header.\n");
		return EXIT_FAILURE;
	}

	// to store pixel being worked on
	struct pixel* curPixel = NULL;

	// run through old pixels, discarding those which are to be cropped
	// and writing the rest to file
	for (int i = 0; i < oldHeight; i++)
	{
		// only run through line if we're out of region to be cropped
		if (!(i < (oldHeight - cropStart[1] - cropHeight) || 
			i > (oldHeight - cropStart[1]))) 
		{
			for (int j = 0; j < oldWidth; j++)
			{
				// only write to file if not in cropped region
				if (!(j < cropStart[0] || j > cropStart[0] + cropWidth))
				{
					// read in the current pixel
					curPixel = getPixel(inFile);

					// make sure read worked
					if (curPixel == NULL)
					{
						fprintf(stderr, "Unable to read pixel.\n");
						return EXIT_FAILURE;
					}

					// write current pixel, checking for error
					if (writePixel(curPixel, outFile) != EXIT_SUCCESS)
					{
						fprintf(stderr, "Unable to write pixel.\n");
						return EXIT_FAILURE;
					}
				}
				else
				{
					// move old file on by a pixel
					fseek(inFile, sizeof(struct pixel), SEEK_CUR);
				}
			}
		}
		else
		{
			// move old file on by width + padding
			fseek(inFile, oldWidth*sizeof(struct pixel) + oldPadding, SEEK_CUR);
		}

		// move old file on by padding
		fseek(inFile, oldPadding, SEEK_CUR);

		// add padding to new file
		for (int k = 0; k < newPadding; k++)
		{
			fputc(0x00, outFile);
		}
	}

	// free memory allocated to current pixel storage
	free(curPixel);

	// close the output file, checking for error
	if (fclose(outFile) != 0)
	{
		fprintf(stderr, "Unable to close output file: %s.\n", outFileName);
		return EXIT_FAILURE;
	}

	// if program gets to here, everything is okay
	return EXIT_SUCCESS;
}