/**
 * @brief Writes decompressed text to file.
 * @details write_to_file receives a pointer to a vector of words, a filename, and the number of words. It writes the content of the string vector to a file. It returns -1 if there was an error and 0 if the operation was succesful. If the file received doesn't have a .palz extension, it will be replaced. Otherwise, a new file, with the same name but no .palz extension, will be created.
 * 
 * @param words Pointer to data which will be saved in the file.
 * @param filename Name of the original (compressed) file.
 * @param int Number of words in the dictionary.
 * @return Returns 0 on success.
 */
int write_to_file (char** words, char *filename, FILE* compressed, unsigned int numberOfWords, int function) {
	
	FILE *newDoc = tmpfile();
	unsigned int code = 0;

	//Decompress
	int bytes = bytes_for_int(numberOfWords+15);
	unsigned int prev_code = 0;
	while (running && fread(&code, bytes , 1, compressed)>0) {

		if(code > numberOfWords+14) {
			fprintf(stderr, "Failed: %s is corrupted\n", filename);
			if(function ==1) {
				exit(1);
			} else {
				return 0;
			}
		}
		//detect repetitions
		if (code == 0 ) {
			//check if prev code exists and is separator
			//read next line
			fread(&code, bytes , 1, compressed);
			while (code != 0) {
				fputs (words[prev_code], newDoc);
				code--;
				}
				
			}//code is not a repetition
			else {
				fputs (words[code], newDoc);
				prev_code = code;
			}
	}

	if (!feof(compressed)){
		fprintf(stderr, "fread() on %s failed.\n", filename);
	}


	//Searches and removes .palz extension if it exists
	char *ptr = NULL;
	ptr = strrchr(filename, '.');
	if (ptr != NULL && strcasecmp(ptr, ".palz") == 0 && running == 1)
	{
		*ptr = 0; 
	}

	//Write to file
	FILE *outFile = NULL;
	rewind(newDoc);
	outFile = fopen(filename, "w");

	//Copy from the temporary file to the permanent file
	char buffer[8096];
	int n;
	while( (n=fread(buffer, 1, 8096, newDoc)) > 0) {
	 	fwrite(buffer, 1, n, outFile);
	}
	fflush(outFile);
	fclose(newDoc);


	//Return the compression ratio
	float outFileSize;
	float compressedSize;
	compressedSize = ftell(compressed);
	outFileSize = ftell(outFile);
	printf("Compression ratio: %s %4.2f%%\n", filename, compression_ratio(compressedSize, outFileSize));

	if ((fclose(outFile) != 0) || ((fclose(compressed) != 0) && (running == 1))) {
		printf("fclose() failed.\n");
		exit(1);
	}
	
	return 0; //success
}