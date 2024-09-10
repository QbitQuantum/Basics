char *evaluateStringAsBashCommand(char *command, char *input) {
  char *res;
  int okay, errorOnInput;
  int exitcode;
  int pipesToBash[2];
  int pipesFromBash[2];
  pid_t pid;
  int childStatus;
  char readBuffer[READ_BUFFER_SIZE];
  int readLen;
  char *buf;
  int len;
  int i;

  if ((command == NULL) || (strlen(command) == 0)) {
    printMessage(1,"Warning in bashevaluate: no command provided\n");
    return NULL;
  }

  res = NULL;
  okay = 0;
  fflush(NULL);
  
  // Create two unnamed pipe
  if ((input != NULL) && (pipe(pipesToBash) == -1)) {
    // Error creating the pipe
    printMessage(1,"Warning in bashevaluate: error while creating a pipe");
  } else {
    if (pipe(pipesFromBash) == -1) {
      // Error creating the pipe
      printMessage(1, "Warning in bashevaluate: error while creating a pipe");
    } else {
      // Fork
      //
      // Flush before forking
      //
      fflush(NULL);
      if ((pid = fork()) == -1) {
	// Error forking
	printMessage(1, "Warning in bashevaluate: error while forking");
      } else {
	// Fork worked
	if (pid == 0) {
	  // I am the child
	  //
	  // Close the unneeded ends of the pipes.
	  //
	  if (input != NULL) close(pipesToBash[1]);
	  close(pipesFromBash[0]);
	  
	  // Connect my input and output to the pipe
	  //
	  if (input != NULL) {
	    if (dup2(pipesToBash[0],0) == -1) {
	      _exit(1);
	    }
	  }
	  if (dup2(pipesFromBash[1],1) == -1) {
	    _exit(1);
	  }
	  
	  // Execute bash
	  //
	  fflush(NULL);
	  execlp("sh","sh","-c",command,(char *) NULL);
	  fflush(NULL);

	  _exit(1);
	} else {
	  // I am the father
	  //
	  // Close the unneeded ends of the pipes.
	  //
	  if (input != NULL) close(pipesToBash[0]);
	  close(pipesFromBash[1]);
	  
	  // Do my job
	  //
	  errorOnInput = 0;
	  if (input != NULL) {
	    if (write(pipesToBash[1],input,
		      strlen(input) * sizeof(char)) == -1) {
	      printMessage(1,"Warning in bashevaluate: unable to write to bash");
	      errorOnInput = 1;
	    }
	    close(pipesToBash[1]);
	  }

	  fflush(NULL);

	  if (!errorOnInput) {
	    do {
	      readLen = read(pipesFromBash[0],readBuffer,READ_BUFFER_SIZE);
	      if (readLen > 0) {
		if (res == NULL) {
		  res = safeCalloc(readLen + 1, sizeof(char));
		  buf = res;
		} else {
		  len = strlen(res);
		  buf = safeCalloc(len + readLen + 1, sizeof(char));
		  strcpy(buf,res);
		  free(res);
		  res = buf;
		  buf += len;
		}
		for (i=0;i<readLen;i++) {
		  *buf = (readBuffer[i] == '\0') ? '?' : readBuffer[i];
		  buf++;
		}
	      }
	    } while (readLen == READ_BUFFER_SIZE);

	    // Wait for my child to exit
	    wait(&childStatus);
	    
	    // Read the rest of the pipe if it filled up again after 
	    // having been emptied already.
	    do {
	      readLen = read(pipesFromBash[0],readBuffer,READ_BUFFER_SIZE);
	      if (readLen > 0) {
		if (res == NULL) {
		  res = safeCalloc(readLen + 1, sizeof(char));
		  buf = res;
		} else {
		  len = strlen(res);
		  buf = safeCalloc(len + readLen + 1, sizeof(char));
		  strcpy(buf,res);
		  free(res);
		  res = buf;
		  buf += len;
		}
		for (i=0;i<readLen;i++) {
		  *buf = (readBuffer[i] == '\0') ? '?' : readBuffer[i];
		  buf++;
		}
	      }
	    } while (readLen == READ_BUFFER_SIZE);

	    if (WEXITSTATUS(childStatus) != 0) {
	      printMessage(1, "Warning in bashevaluate: the exit code of the child process is %d.\n", WEXITSTATUS(childStatus));
	    } else {
	      printMessage(2, "Information in bashevaluate: the exit code of the child process is %d.\n", WEXITSTATUS(childStatus));
	    }

	    close(pipesFromBash[0]);

	    okay = 1;
	    if (res == NULL) {
	      res = safeCalloc(2, sizeof(char));
	    }
	    len = strlen(res);
	    if (len >= 1) {
	      if (res[len-1] == '\n') res[len-1] = '\0';
	    }
	  }
	}
      }
    }
  }

  if (!okay) {
    if (res != NULL) free(res);
    res = NULL;
  }

  fflush(NULL);

  return res;
}