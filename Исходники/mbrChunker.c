/*
 * Input:  file pointer, hex string from the command line,
 * and the file size.
 * Output:  Nothing (stdout)
 */
void hxsearch(FILE *fptr, char *hexstring, long long filesize_bytes,
		long blocksize) {

	char pattern_buffer[HEXSTRING_MAX] = { 0 };
	char chunk[blocksize];
	unsigned int byte;
	int res;
	int z = 0;
	int current_search = 0;
	// char *parsebuffer;
	long long int master_counter = 0;
	int arraysize = 0;
	int len = 0;
	int pos = 0;
	int counter = 0;
	int bytes_read = 0;
	int runs = 0;
	int matches = 0;
	size_t offsetctr = 0;
	char *chunkptr;
	long long sz = 0;
	len = strlen(hexstring);

	arraysize = sizeof(hexstring) / sizeof(char);
	off_t fs = getfilesize(fptr);
	sz = fs;

	printf("Parsing Hex string \"%s\" now.\n\n", hexstring);
	while ((res = sscanf(&hexstring[pos], "%2x", &byte)) == 1) {
		//printf("\nres=%d, byte=%d(%02x)\n", res, byte, byte);
		pattern_buffer[counter] = byte;
		pos += 2;
		counter++;
	}

	printf("Results:\n\n");
	while ((bytes_read = fread(chunk, sizeof(unsigned char), sizeof(chunk),
			fptr)) > 0) {
		chunkptr = chunk;
		for (z = 0; z < bytes_read; z++) {
			if (*chunkptr == pattern_buffer[current_search]) {
				current_search++;
				if (current_search > (counter - 1)) {
					current_search = 0;
					printf(
							"Hex string %s was found at starting byte location:  %lld\n",
							hexstring, (long long int) (offsetctr - 1));
					matches++;
				}
			} else {
				current_search = 0;
			}
			chunkptr++;
			// printf("[%d]: %02X\n", offsetctr, chunk[z] & 0xff);
			offsetctr++;
		}
		master_counter += bytes_read;
		runs++;
		//printf("buffer run = %d\n", runs);

	}
	printf("\n\nQuick statistics:\n");
	printf("=====================\n");
	printf("Number of bytes that have been read:  %lld\n", master_counter);
	printf("Number of signature matches found:  %d\n", matches);
	printf("Total number of bytes in hex string:  %d\n", counter);
	printf("Block size of each buffer:  %ld\n", blocksize);
	printf("Number of buffers searched:  %d\n", runs);

	fclose(fptr);
	exit(0);

}