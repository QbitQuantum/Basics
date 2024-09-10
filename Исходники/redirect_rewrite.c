int main(int argc, char **argv) {

	openlog("redirect_rewrite", LOG_PID|LOG_CONS, LOG_USER);

	compile_patterns();
	/* Allocate some memory */
	content = (char*) malloc(sizeof(char) * BUF_SIZE);
	memset (content,0,sizeof(char) * BUF_SIZE);
	/* Check if the memory couldn't be allocated; if it's the case, handle the problem as appropriate. */
	if (NULL == content) {
#ifdef DEBUG
		perror("Could not allocate memory");
#endif
		return EXIT_FAILURE;
	}
	unsigned int n = 0;
	unsigned int localAllocatedSize, oldSize;
	localAllocatedSize = allocatedSize;

	memset (content,0,sizeof(char) * localAllocatedSize);
	int c;
	while((c = fgetc(stdin)) != EOF){

		if(n==localAllocatedSize){
			oldSize = localAllocatedSize;
			localAllocatedSize += INCR_SIZE;
			allocatedSize = localAllocatedSize;
			content = (char*) realloc(content, sizeof(char) * localAllocatedSize);
			if (NULL == content) {
				perror("Could not allocate memory");
				exit(1);
			}
			if(oldSize<localAllocatedSize)
				memset (content+oldSize,0,sizeof(char) * INCR_SIZE);
		}

		/* Read line into contents */
		if (c != '\n'){
			content[n] = c;
			n++;
			continue;
		}
		n=0;

		//printf("[X]Content %s \n\n", content);

		/* Grab the text up to the space character */
		char* channel = strtok (content, " ");

		char* url;
		if(channel != NULL){
			url = match(channel);

			/* Grab more text up to the next space character
			 * and try to get a redirect url match */
			char* original_url;
			if(NULL == url){
				original_url = strtok (NULL, " ");
				if(NULL != original_url){
					url = match(original_url);
				}
				printf("%s ", channel);
			}
			if(NULL == url){
				printf("\n");
				fflush(stdout);
			}else{

				if(NULL != url){
					char buffer[2048];
					printf("302:%s\n", url);
					fflush(stdout);
					sprintf (buffer, "Redirecting: %s", url);
					syslog(LOG_INFO, buffer);
				}else{
					printf("\n");
					fflush(stdout);
				}
			}

		}else{
			syslog(LOG_INFO, "No url found");
		}
		memset (content,0,sizeof(char) * localAllocatedSize);
	}
	closelog();
	return EXIT_SUCCESS;
}