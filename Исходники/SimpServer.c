void perform_http(char *request, char *response, char *directory){
	/* variable declaration: */
	char http_code[4]; // holds the http code as a char array
	FILE *fp; // file pointer for the requested file
	char status[100]; // status of the http code
	char method[20]; // the method in the http request
	char location[200]; // the location of the file requested
	char temp_directory[MAX_STR_LEN] = {0}; //to hold the full directory of the desired file
	char http_version[10]; // the version of http being used
	char *token; // a pointer to tokenize the request
	char time_str[100]; // a char array to hold the current time in a specific format
	char *file_buf; // a char array to hold the contents of the requested file
	time_t cur_time; // gets and holds the current time
	
	/* tokenize the request to get "method", "location" and "http_version" */
	token = strtok(request, " ");
	strncpy(method, token, 20);
	
	token = strtok(NULL, " ");
	strncpy(location, token, 200);
	
	token = strtok(NULL, " ");
	strncpy(http_version, strtok(token, "\r"), 10);
	
	/* the location parsed is actually the full uri sent by the client,
	*  must get the actual location of the requested file from the end of the uri
	*/
	token = strtok(location, "/");
	// check if the first part of the uri is "http:" 
	if(strncmp(token, "http:", 5)==0){
		token = strtok(NULL, "/");
	}
	// get the next part of the uri (hostname)
	token = strtok(NULL, "\0");
	/* append a forward slash to "temp_directory"
	*  and then append the location of the requested file */
	strncpy(temp_directory, directory, strlen(directory));
	strncat(temp_directory, "/", 2);
	strncat(temp_directory, token, 200);
	
	//attempt to topen the requested file in the specified location
	fp = fopen(temp_directory, "r");

	// if the porgram fails to open the file, assing http code "404"
	if(fp == NULL)
	{
		strncpy(http_code, "404", 4);
		strncpy(status, "File not found", 15);
	}else
	{//otherwise assign code "200"
		strncpy(http_code, "200", 4);
		strncpy(status, "OK", 3);
	}
	if(strncmp(method, "GET", 4) != 0)
	{//check if the method in the request is implemented in this program
		// if it is not, assign http code "501"
		strncpy(http_code, "501", 4);
		strncpy(status, "Not implemented", 16);
		fp = NULL;
	}
	
	// if the file was successfully opened, read it
	if(fp != NULL)
	{
		if((file_buf = read_file(fp, file_buf)) == NULL)
		{
			// if the file is unreadable, assign http code 404
			strncpy(http_code, "404", 4);
			strncpy(status, "File not found", 15);
		}
		// close the file after reading
		fclose(fp);
	}
	
	// get the current time
	cur_time = time(0);
	// format it for ease of reading
	strftime(time_str, 100, "%a %d, %b %Y %T PST", localtime(&cur_time));
	
	/* start to construct the response with 
	*  information about the request,
	*  the date, and the server being used
	*/
	strncat(response, "---Response Header---\n", 22);
	strncat(response, http_version, strlen(http_version));
	strncat(response, " ", 2);
	strncat(response, http_code, 4);
	strncat(response, " ", 2);
	strncat(response, status, strlen(status));
	strncat(response, "\nDate: ", 8);
	strncat(response, time_str, strlen(time_str));
	strncat(response, "\nServer: Apache/2.2.31 (Unix) mod_jk/1.2.40\n\n", 45);
	
	// if the file was successfully read, concatenate it to the response
	strncat(response, "---Response Body---\n", 21);
	if(fp != NULL)
	{
		strncat(response, file_buf, strlen(file_buf));
	}
	
}