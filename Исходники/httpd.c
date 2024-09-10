/**
 * Reads and parses the file request lines received from the client. 
 * @param req: location where this method writes the requested 
 *             filename or directory.
 * @param buff: buffer where the HTTP request is stored.
 * @param response: instance of Struct HTTP_Response which this method will
 *				    populate based on the HTTP request in buff.
 */
void ExtractFileRequest(char *req, char *buff, HTTP_Response *response ) {

	int lastPos = (int)(strchr(buff, '\n') - buff) - 1; //Newline is \r\n
	                                                      
	/* We should now have the ending position to get the following line:
	 * "GET / HTTP/1.0"
	 * So split it based on space delimeter to get URL path 
	 * and HTTP version.
	 */

	//printf("entire buffer: %s\nLast pos: %d\n", buff, lastPos);
	//printf("End of first line position: %d\n", lastPos);

	char *tempBuff = malloc(strlen(buff));
	strcpy(tempBuff, buff);

	char *split, *savePtr;
	int i = 0;
	int total = 0;
	while (total < lastPos)
	{
		if (total == 0)
		{
			split = strtok_r(tempBuff, " ", &savePtr);
		}
		else
		{
			split = strtok_r(NULL, " ", &savePtr);
		}
		int size = strlen(split);
		
		switch(i)
		{
			case 0: //Method (GET, POST, HEAD...)
				response->HTTP_Type = malloc(size + 1);
				strcpy(response -> HTTP_Type, split);
				break;
			case 1: //File content path
				strcpy(req, split);
				break;
			case 2: //HTTP Protocol (ex HTTP/1.1)
				
				/* There is no space after the version number, 
				 * only a newline character. So split again. */
				split = strtok(split, "\r\n");
				size = strlen(split);
				response->versionNum = malloc(size + 1);
				strcpy(response -> versionNum, split);
				break;
		}
		total += size + 1; //+1 to account for space
		i++;	
		printf("Split string: %s, size: %d\n", split, size); 
	}
	// Find the Accept: ... line in the get response
	strcpy(tempBuff, buff);

	split = strstr(tempBuff, "Accept: ");
	split = split + strlen("Accept: ");  //Should put us right after Accept: statement
	char *content_type = strtok(split, "\n");
	
	/* If content_type only contains one element, strtok will return NULL.
	 * If content_type has multiple elements (seperated by commas), strtok will 
	 * null terminate the first comma, so content_type will point to only the first element */	 
	strtok(content_type, ",");
	
	printf("Content-type: %s\n", content_type);
	response -> contentType = malloc(strlen(content_type) + 1);
	strcpy(response -> contentType, content_type);

	char *result = "200";
	response -> resultCode = malloc(strlen(result) + 1);
    strcpy(response -> resultCode, result);

	char *stat = "OK";	
	response -> status = malloc(strlen(stat) + 1);
	strcpy(response -> status, stat);

	/*
	 * Check if content requested (req) contains any user variables
	 * GET request contains data in content URL,
	 * POST containst data at the end of the buffer
	 */
	
	char *t = NULL;
	char *userVarStart = NULL;
    if (strcmp(response -> HTTP_Type, "POST") == 0)
	{
		//Print buffer for debug
		printf("Header:\n%s\n\n", buff);

		// Check if POST request with data AFTER the header
		printf("POST Request. Checking for user data\n");
		t = strstr(buff, "\r\n\r\n"); //CRLF is new line
	}
	else if ((t = strchr(req, '?')) != NULL)
	{
		// GET request with data in URL
		printf("GET Request. Checking for user data\n");
		*t = '\0'; //NULL '?' so file request is seperated from the user vars
		t++;
	}
	
	if (t != NULL)
	{
		userVarStart = malloc(strlen(t) + 14);
		sprintf(userVarStart, "QUERY_STRING=%s", t);
		printf("User data: %s\nFile: %s\n\n", userVarStart, req);

		// Add the user variables to QUERY_STRING environment variable
	    putenv(userVarStart); 
	}
		
}