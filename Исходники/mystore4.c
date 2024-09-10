//current_sockfd == file descriptor of pipe from client
//buffer == input from client
//nread == num chars of input
void server_process(int current_sockfd, char *buffer, int nread){

      printf("message from client: %s\n", buffer);
      //Essentially original mystore3 main function,
      //with return statements eliminated
   
      char inputCopy[strlen(buffer)];
      strcpy(inputCopy, buffer+1);
      char *fields[5];
      //int nfields;

      




	

      if (!Process(inputCopy)) {
	if (errmsg[0] != '\0')
	  printf("%s\n",errmsg);
	else
	  printf("|status: ERROR: No command-line arguments, error in arguments, or error in writing to FIFO\n\nVersion: %s\n%s|\n",
		 version,Requests);
      }

      if (!readData()) {
	if (errmsg[0] != '\0')
	  printf("|status: ERROR: %s|\n", errmsg);
	else
	  printf("|status: ERROR: Error reading mystore.dat\n\n%s|\n", Requests);
     }

      strcpy(inputCopy, buffer+1);
      SeparateIntoFields(inputCopy, fields, 5);


      if (command == ADD && !add(fields[2],fields[3])) {
	if (errmsg[0] != '\0')
	  printf("|status: ERROR: %s|\n", errmsg);
	else
	  printf("|status: ERROR: Failure to add new item|\n");
      }

     		 
      if (command == STAT) {
	status();
      }

      
      if (command == DISPLAY && !display(fields[2])) {
	if (errmsg[0] != '\0')
	  printf("|status: ERROR: %s|\n", errmsg);
	else
	  printf("|status: ERROR: Cannot display %s|\n",fields[2]);
      }

      
      if (command == DELETE && !delete(fields[2])) {
	if (errmsg[0] != '\0')
	  printf("|status: ERROR: %s|\n", errmsg);
	else
	  printf("|status: ERROR: Cannot delete %s|\n", fields[2]);
      }

        
      if (command == EDIT && !edit(fields[2])) {
	if (errmsg[0] != '\0')
	  printf("|status: ERROR: %s|\n", errmsg);
	else
	  printf("|status: ERROR: cannot edit %s|\n",fields[2]);
      }

      if (rewrite)
	if (!writeData()) {
	  if (errmsg[0] != '\0')
	    printf("|status: ERROR: %s|\n", errmsg);
	  else
	    printf("|status: ERROR: Could not write the data, file may be destroyed|\n");
	}


}