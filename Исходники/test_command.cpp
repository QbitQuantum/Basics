int 
main(int argc, char *argv[])
{
  char *filename_p = 0;
  char ** argv_;
  
  argv_ = new char* [argc];
  int k = 0;
  
  DEBUG0 (DEBUG_L_CALL, "DEBUG: parsing arguments\n");
  for (int i = 0; i < argc; i++)
   {
     if (!argv[i])           { break; }
     if (argv[i][0] != '-')  { argv_[k++] = strdup(argv[i]); continue; }
     int j = 1;
     if (argv[i][1] == '-')  {
       if (argv[i][2] == 0)  { break; } // handle -- end of options
       j = 2;                   // handle --argument
     }
     if (strstr((argv[i] + j), "ORB"))  { continue; }
     if (! strcmp((argv[i] + j), "help") || strchr((argv[i] + j), 'h'))
      {                         // -h or --help
        cout << argv[0] << version << endl
             << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
             << endl
             << "\t-h             : This help text"  << endl
             << "\t-v             : Prints out the version"  << endl
             << "\t-file Filename : Probe to Execute"  << endl
             << "\t-f    Filename : Probe to Execute"  << endl
          ;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
        cout << argv[0] << ": Version "<< version << endl;
        exit (0);
      }

     if (! strcmp((argv[i] + j), "file") || strchr((argv[i] + j), 'f'))
      {
        filename_p = strdup(argv[++i]);
        continue;
      }
     argv_[k++] = strdup(argv[i]);
   }
  if(!filename_p)
   {
     std::cerr << "Error: Failed to feploy probe: missing path" << std::endl;
     exit(EXIT_FAILURE);;
   } /* end of if(!this->filename_p) */
  if(argv_[0])
   {
     free (argv_[0]);
   } /* end of if(argv_[0]) */
  argv_[0] = strdup(filename_p);
  
  /// The control pipe
  int ctrlpipe[2];
  /// The data pipe
  int datapipe[2];

#if defined(_WIN32)
  if ( _pipe( ctrlpipe, BUFSIZ+8192, O_BINARY | O_NOINHERIT ) < 0 )
   {
     perror("Error while creating the ctrlpipe");
     return -1;
   } /* end of if(pipe(this->ctrlpipe)) */
  
  if ( _pipe( datapipe, BUFSIZ+8192, O_BINARY | O_NOINHERIT ) < 0 )
   {
     perror("Error while creating the datapipe");
     return -1;
   } /* end of if(pipe(this->datapipe) < 0) */
#else
  
  if(pipe(ctrlpipe) < 0)
   {
     perror("Error while creating the ctrlpipe");
     return -1;
   } /* end of if(pipe(this->ctrlpipe)) */
  if(pipe(datapipe) < 0)
   {
     perror("Error while creating the datapipe");
     return -1;
   } /* end of if(pipe(this->datapipe) < 0) */
#endif
  
  try
   {
#if defined(_WIN32)

     char buff[BUFSIZ + 8192];
     int n, hStdOut, hStdIn, nExitCode = STILL_ACTIVE;
     HANDLE hProcess;

     DEBUG0 (4, "Saving the stdin and stdout file descriptors\n");

     hStdOut = _dup(_fileno(stdout));
     hStdIn = _dup(_fileno(stdin));

     DEBUG0 (4, "Using _dup2 on datapipe write and ctrlpipe read ends\n");

     if(_dup2(datapipe[1], _fileno(stdout)) != 0)
       perror("Error in using dup2 on datapipe[1]");

     if(_dup2(ctrlpipe[0], _fileno(stdin)) != 0)
       perror ("Error in using dup2 on ctrlpipe[0]");

     DEBUG0 (4, "Closing the datapipe write and ctrlpipe read ends\n");

     close(datapipe[1]);
     close(ctrlpipe[0]);

     DEBUG0 (4, "Spawning the process \n");

     hProcess = (HANDLE)_spawnvp(P_NOWAIT, filename_p ,argv_);  

     DEBUG0 (4, 
	     "Changing original file descriptors back to stdin and stdout\n");
     if(_dup2(hStdOut, _fileno(stdout)) != 0)
      {
	perror("Error in making hStdOut as stdout\n");
	exit(1);
      }
     
     if(_dup2(hStdIn, _fileno(stdin)) != 0)
      {
	perror ("Error in making hStdIn as stdin\n");
	exit(1);
      }

     DEBUG0 (4, "Closing the original file descriptors\n");

     close(hStdOut);
     close(hStdIn);

     strcpy(buff,"start\n");
     n = strlen(buff);

     DEBUG0 (4, "DEBUG: In NT parent: writing start");

     ssize_t nleft    = n;
     ssize_t nwritten = 0;
     char *ptr = buff;
  
     while(nleft > 0)
      {
	if((nwritten = write(ctrlpipe[1], ptr, nleft)) <= 0)
	 {
	   if(errno == EINTR)
	    {
	      nwritten = 0;
	    } /* end of if(errno == EINTR) */
	   else
	    {
	      perror ("Error while writing start on to pipe");
	    } /* end of else */
	 } /* end of if((nwritten = write(sockfd, ptr, nleft)) <= 0) */
	nleft -= nwritten;
	ptr += nwritten;
      } /* end of while(nleft > 0) */

     string message;
     string raw_data;
     DEBUG0 (4, "DEBUG: In parent: reading");

     if (hProcess)
      {
	while (nExitCode == STILL_ACTIVE)
	 {
	   n = read (datapipe[0], buff, BUFSIZ + 8192);
	   buff[n] = 0;
	   DEBUG2 (2, "DEBUG: Read %d bytes --> \n%s", n, buff);
	   raw_data.append(buff);

	   string::size_type index =
	     raw_data.find(STDC::QMS::Citizen::delimiter);
	   while(index != string::npos)
	    {
	      // we have at least one complete message in here
	      message.assign(raw_data, 0, index);
	      raw_data.erase(0, index + strlen(STDC::QMS::Citizen::delimiter));
	      index = raw_data.find(STDC::QMS::Citizen::delimiter);
	      std::cerr << "Probe says: " << message << std::endl;
	    } /* end of while(message.find(delimiter) != string::npos) */

	   if(!GetExitCodeProcess(hProcess,(unsigned long*)&nExitCode))
             perror ("Error in getting Child process exit status");

	 } /* end of while((n = read(datapipe[0], buff, BUFSIZ + 8192) ) > 0)*/

	DEBUG0 (4, "*******Child Exited********\n");

      } // end of if (hProcess)
  

     DEBUG0 (6, "DEBUG: In parent: finished reading");
  
#else
  
     int childpid = fork();
     if(childpid < 0)
      {
	perror("Fork Failed");
	return childpid;
      } /* end of if(childpid < 0) */
  
     if(childpid == 0)
      {				// in the child

	DEBUG0 (4, "DEBUG:  Handling descriptors in the child");
	if (close(ctrlpipe[1]) != 0)
	  perror ("close");
	if (close(datapipe[0]) != 0)
	  perror ("close");
     
	DEBUG0 (2, "Continuous_Pipe_Proxy:: Handling stdin in the child");
	if (ctrlpipe[0] != STDIN_FILENO ) {
	  if ( dup2 ( ctrlpipe[0], STDIN_FILENO ) != STDIN_FILENO ) {
	    fprintf(stderr, "Problem with STDIN dup2\n");
	    return (-1);
	  }
	  if (close ( ctrlpipe[0]) != 0)
	    perror("close");
	}	
     
	DEBUG0 (2, "Continuous_Pipe_Proxy:: Handling stdout in the child");
	if ( datapipe[1] != STDOUT_FILENO ) { 
	  if ( dup2 ( datapipe[1], STDOUT_FILENO ) != STDOUT_FILENO ) {
	    // Problems
	    fprintf(stderr, "Problem with STDOUT dup2\n");
	    return (-1);
	  }
	  if (close ( datapipe[1]) != 0)
	    perror("close datapipe[0]");
	}
     
	DEBUG1 (2, "DEBUG: Continuous_Pipe_Proxy::deploy exec %s",
		filename_p);
	// DEBUG!!!
	if(!argv_)
	 {
	   fprintf(stderr, "No arguments!!!\n");
	   return (-1);
	 } /* end of if(!this->argv_) */
#ifndef SILENT_MODE
	else
	 {
	   int i = 0;
	   std::cerr << "\tCommand: '";
	   while(argv_[i])
	    {
	      std::cerr << argv_[i++] << " ";
	    } /* end of while(this->argv_[i]) */
	   std::cerr << "'" << std::endl;
	 } /* end of else */
#endif
	int ret = execvp(filename_p, argv_);
	perror("Failed execve");
	DEBUG1 (8, "DEBUG: Failed execve %d", ret);
      } /* end of if(int childpid = fork()) */
     else
      {				// in the parent
	DEBUG0 (4, "DEBUG:  Handling descriptors in parent");
	if (close(ctrlpipe[0]) != 0)
	  perror ("close");
	if (close(datapipe[1]) != 0)
	  perror ("close");

	char buff[BUFSIZ + 8192];
	ssize_t length ;
	ssize_t n ;

	DEBUG0 (6, "DEBUG: In parent: writing start");

	strcpy (buff, "start\n");
	length = strlen(buff);
	ssize_t nleft    = length;
	ssize_t nwritten = 0;
	char *ptr = buff;
  
	while(nleft > 0)
	 {
	   if((nwritten = write(ctrlpipe[1], ptr, nleft)) <= 0)
	    {
	      if(errno == EINTR)
	       {
		 nwritten = 0;
	       } /* end of if(errno == EINTR) */
	      else
	       {
		 perror ("Error while writing start on to pipe");
	       } /* end of else */
	    } /* end of if((nwritten = write(sockfd, ptr, nleft)) <= 0) */
	   nleft -= nwritten;
	   ptr += nwritten;
	 } /* end of while(nleft > 0) */
     
	string message;
	string raw_data;
	bool done = false;
	DEBUG0 (4, "DEBUG: In parent: reading");
	while(!done)
	 {
	   n = read(datapipe[0], buff, BUFSIZ + 8192);
	   if(n < 0)
	    {
	      if(errno == EINTR)
	       {
		 continue;
	       } /* end of if(errno == EINTR) */
	      else
	       {
		 break;
	       } /* end of else */
	    } /* end of if(n < 0) */
	   if(n == 0)
	    {
	      break;
	    } /* end of if(n == 0) */
	
	   buff[n] = 0;
	   DEBUG2 (2, "DEBUG: Read %d bytes --> \n%s", n, buff);
	   raw_data.append(buff);

	   string::size_type index = 
	     raw_data.find(STDC::QMS::Citizen::delimiter);
	   while(index != string::npos)
	    {
	      // we have at least one complete message in here
	      message.assign(raw_data, 0, index);
	      raw_data.erase(0, index + strlen(STDC::QMS::Citizen::delimiter));
	      index = raw_data.find(STDC::QMS::Citizen::delimiter);
	      std::cerr << "Probe says: " << message << std::endl;
	    } /* end of while(message.find(delimiter) != string::npos) */
	 } /* end of while((n = read(datapipe[0], buff, BUFSIZ + 8192) ) > 0)*/
	if(n == -1)
	 {
	   perror("read from child\n");
	 } /* end of if(n == -1) */

	DEBUG0 (6, "DEBUG: In parent: finished reading");

	int status = 0;
	pid_t pid_ret;
	while((pid_ret = waitpid(childpid, &status, WNOHANG) )  > 0 )
	 {
	   DEBUG1(4, "DEBUG: Exited Childpid ->%d", pid_ret);
	   if(WIFEXITED(status))
	    {
	      DEBUG0(4, "DEBUG: Child Exited Normally");
	    } /* end of if(WIFEXITED(status)) */
	   else
	    {
	      DEBUG1(6, "DEBUG: Child Exited Abnormally with status %d",
		     WEXITSTATUS(status));
	      if(WIFSIGNALED(status))
	       {
		 DEBUG1(6, "DEBUG: Child got signal %d",
			WTERMSIG(status));
	       } /* end of if(WIFSIGNALED(status)) */	
	    } /* end of else if(WIFEXITED(status)) */
	 } /* end of while(pid_ret = waitpid(childpid, &status, 0)) */

	DEBUG0 (4, "DEBUG: Parent closing file descriptors");
	if (close(ctrlpipe[1]) != 0)
	  perror ("close");
	if (close(datapipe[0]) != 0)
	  perror ("close");	
     
      } /* end of else */
#endif
   }
  catch (...)
   {
     std::cerr << "caught an exception while deploying"
               << std::endl;
     exit(EXIT_FAILURE);
   }

  exit(EXIT_SUCCESS);
}