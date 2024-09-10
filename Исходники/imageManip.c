/*
*Contains algorithm to turn an image into ASCII art!
*Parameters:
*filename: the file to write our art to.
*pixAmount: the amount of pixels per character (in a square)
*img: a pointer to our image in memory.
*
*return 0 if no errors were encountered, 1 otherwise.
*/
int ascii(Image* img, char* filename, int pixAmount) {
	// if we don't have a file in memory, say so.
	if(img->data == NULL) {
	fprintf(stderr, "Error, no file currently in memory\n");
		return 1;
	}
	//first we need to pixelate
	pixelate(img, pixAmount);
	//then turn it into grayscale
	toGrayscale(img);
	//our file to write to
	FILE* fout= fopen(filename, "w");
	// our indicator of brightness
	int brightness = 0;
	//the character we want to use to write
	char c = ' ';
	//for each "square" of our image
	for(int j=0; j<(img->rowNum/pixAmount); j++) {
		for(int i=0; i<(img->colNum/pixAmount); i++) {
			//our brightness value is equal to the actual brightness over 8, because we're 
			//using 31 different characters to create our image.
			brightness =(int)((img->data[pixAmount*((j*img->colNum)+i)].r)/(2.34375));
			//mapping brightness to character
			c = toASCII(brightness);
			//printing the character twice so we can have a square image.
			fprintf(fout,"%c%c",c,c);
			
		}
		//print a line break.
		fprintf(fout,"\n");
	}
	//close our file!			
	fclose(fout);
	
	return 0;	
	
}