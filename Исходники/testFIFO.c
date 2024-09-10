int main(int argc, char* argv[] ) {

	FILE* fp;
	/* Remove all existing log files */

	remove(FIFO_PIPE);
	
	
	int pid;		//Initialize first process to ID 1
	
	int msgId, namedPipe;	
	if (access(FIFO_PIPE, F_OK) == -1) {
		printf("Creating named pipe...\n");
		namedPipe = mkfifo(FIFO_PIPE, 0777); 
		if (namedPipe != 0) {
			/* the fifo name */
			/* check if fifo already /* if not then, create the fifo*/
			printf("Could not create fifo %s\n", FIFO_PIPE);
			exit(EXIT_FAILURE); 
		}
		printf("Named pipe created successfully: %s\n",FIFO_PIPE);
	}

	pid = (int)fork();

	if(pid == 0) {
		/* Child 1 section */

		

		printf("Opening FIFO named pipe..\n");
		/* Open the named pipe for read only on child process 2 */
		namedPipe = open(FIFO_PIPE, O_RDONLY);
		printf("Opening success..\n");
		
		//fclose(fp);
		
		fp = fopen("TESTLOG.txt", "a+");					/* Open a log file */
		printf("Parent Process 1: reading from Child 3..\n");
		while(read(namedPipe, tmpBuffer, sizeof(tmpBuffer))) {	/* Read all the buffers from pipe */
			
			sscanf(tmpBuffer, "%d%[^\n]",&msgId, buffer);				/* Break the message into the ID and message */
			printf("MSG: %d, %s\n", msgId, buffer);
			if(msgId == 1) {											/* Message is belongs to the child */
				strcat(buffer, KEEP_MSG);								/* Append message will "keep" word*/
			} else {													/* Message is NOT belongs to the child */
				//write(pipeFd[1], tmpBuffer, sizeof(tmpBuffer));			/* Forward the message to next child */
				strcat(buffer, FWD_MSG);								/* Append message will "forward" word*/
			}
			fprintf(fp, "%d%s\n",msgId,buffer);				/* Write the messages into the log file */
		}
		printf("Close file PP LOG\n");
		fclose(fp);

		return 0;

	}
	else {
		/* Parent or root section */
		
		printf("PARENT: Opening FIFO named pipe..\n");
		/* Open the named pipe for read only on child process 2 */
		namedPipe = open(FIFO_PIPE, O_WRONLY);
		
		printf("PARENT: Opened FIFO successfully.\n");
		
		/* Write to Childs from Message File*/
		fp = fopen(C2_TXT, "r");	/* Open Message File */
		while(fgets(tmpBuffer, (sizeof(tmpBuffer) + 2), fp)) {			/* Read all the messages from the file */
			printf("%s\n", tmpBuffer );
			write(namedPipe, tmpBuffer, sizeof(tmpBuffer));
		}	
		//c2Status = 1;		/* File is logged */
		printf("PARENT: Close file\n");
		fclose(fp);
		
	}
        	
	return EXIT_SUCCESS;
}