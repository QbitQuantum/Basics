int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	char HtmlDoc[50000];
	char buffer[BUFSIZ + 1];
	char url[BUFSIZ + 1];
	int count = 0;

	printf("URL:\n");
	gets(url);

	char urlString[BUFSIZ + 1];
	strcpy(urlString, "curl -s ");
	strcat(urlString, url);

	fp = popen(urlString, "r");

	char * tempSrc;
	char *pQ1;
	char *pQ2;
	char tempWord[BUFSIZ + 1];
	char * tempTags;
	int numBetween;

	//Reads in the data from the URL
	while (!feof(fp)) {
		numBetween = 0;

		fgets(buffer, BUFSIZ, fp);

		strcat(HtmlDoc, buffer);

		tempSrc = strstr(buffer, "src=");

		if ((tempSrc != NULL) && (isspace(*(tempSrc - 1)))) {
			count++;
			int i = 1;

		}

	}

	pclose(fp);

	printf("Ready\n");

	char command = 'n';
	int done = 0;

	while (done == 0) {

		command = *gets(buffer);
		// A switch that waits for a command to print things
		switch (command) {

		//Prints number of valid src attributes
		case 'c':
			printf("%d\n", count);
			printf("Ready\n");
			break;

			//Prints number of tags
		case 't':
			printTags(HtmlDoc);

			printf("Ready\n");
			break;

			// Prints the URLS
		case 'u':
			printURLS(HtmlDoc);
			printf("Ready\n");
			break;
		case 'f':
			printf("f");
			printf("Ready\n");
			break;

			//Quits the program
		case 'q':

			tempTags = strstr(buffer, "<");

			printf("Complete\n");
			done = 1;
			break;
		}

	}

}