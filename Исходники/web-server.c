int checkHostHeader(char buffer[]){

        char *finalHost = (char *)malloc(1000);
        strcat(finalHost,getHostName());
	if(!strcmp(finalHost, "serendipity"))	
        strcat(finalHost, ".dcs.gla.ac.uk");
	else
		finalHost = "localhost";

        char *tempbuffer = calloc(strlen(buffer)+1, sizeof(char));
	if(!tempbuffer)	printf("Error: %s\n",  strerror(errno));

        strcpy(tempbuffer, buffer);

        return 1;

}