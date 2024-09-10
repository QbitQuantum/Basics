// Prompts for a file to open the map
// If anything fails the function returns 1, else 0 is returned
int openMapFile(void)
{
	printf("Enter file name: %s", mapFolder);
	// Input entered
	char * fileN = (char*)malloc(32 * sizeof(char));
	if (scanf("%s", fileN) == 1) {
		// Lets extract the extension
		// Pointer to the last dot
		char * p = NULL;
		char * p1 = strchr(fileN, '.');
		while (p1 != NULL) {
			p = p1;
			p1 = strchr(p1 + 1, '.');
		}
		if (p != NULL) {
			if (strstr(p + 1, "map") != NULL && strlen(p + 1) == 3) {
				// File path is folder path + file name
				filePath = (char *)malloc((strlen(mapFolder) + strlen(fileN) + 1) * sizeof(char));
				strcpy(filePath, mapFolder);
				strcat(filePath, fileN);
				// File name
				fileName = (char *)malloc((strlen(fileN) + 1) * sizeof(char));
				strcpy(fileName, fileN);

				// Try to open file in read-binay mode
				fp = fopen(filePath, "rb");
				int exists = 0;
				if (fp != NULL) {
					// File already exists, lets try to read its content
					if (loadMapFromFile(fp, &Map)) {
						// Failed
						printf("Error loading map from file \"%s\". Invalid or corrupted .map file\n", filePath);
					}
					else {
						// Succeeded
						exists = 1;
						printf("Successfully loaded map from file\n");
					}
				}
				else {
					// No file found
					printf("No such vaid file found, creating one: \"%s\"\n", filePath);
				}

				// Open the file in write-binary mode (this also creates the file if it doesn't exist)
				if (exists) {
					fp = freopen(filePath, "wb", fp);
				}
				else {
					fp = fopen(filePath, "wb");
					// Init our Map
					int size[3] = {50, 50, 50};
					initMap(&Map, size);
				}

				if (fp != NULL) {
					// Save the map in case the user forgets to save it
					saveMapToFile(fp, Map);
					// Everything went well
					printf("Done.\n");
					return 0;
				}

				// Something bad happened
				printf("Could not open file \"%s\"\n", filePath);
				return 1;
			}
			// Extension found but it's not .map
			printf("Invalid file extension: \"%s\"\n", p);
			return 1;
		}
		// No dot found so there is no extension
		printf("No file extension in given name\n");
		return 1;
	}
	// Input failed?
	return 1;
}