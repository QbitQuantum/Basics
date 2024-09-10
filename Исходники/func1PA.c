// process 1 makes a header file for the compression file
// take a file name as a parameter
void processCompression1(char *fileName){

unsigned char length; // holds the length of the file name
unsigned int size; // size of the file
length = strlen(fileName); // finds the length

			size = fTell(fileName); // get the size of the file
			
			
			//printf("The string length: %d", length);
			//printf(" This is argument: %s", fileName);
			//printf(" FileSize %d\n", size);  
			
			
	fwrite(&length, 1, 1, archiveFileP); // write the file name length
	fwrite(fileName, 1, length, archiveFileP); // write the file name
	fwrite(&size, 1, 4, archiveFileP); // write the file size
			
}