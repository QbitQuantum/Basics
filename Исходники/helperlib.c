int
mhelperPerformCommand3(AuthorizationRef authorizationRef, 
                       const char *helperPath, MAHelperCommand command,
                       void(*output_callback)(const char*, void*),
                       void *callback_data,
                       int *fdret, char **error_message)
{
  int tohelper[2], fromhelper[2];
  int childStatus;
  int written;
  pid_t pid;
  int rc;
  int sv[2];
  int ok;
  AuthorizationExternalForm extAuth;
  
restart:
    ok= 1;
  childStatus= 0;
  
  if (error_message)
    *error_message= NULL;
  
  // authref --> bytestream
  if (authorizationRef && AuthorizationMakeExternalForm(authorizationRef, &extAuth))
    return MAHelperCommandInternalError;
  
  if (pipe(tohelper) < 0)
    return MAHelperCommandInternalError;
  
  if (pipe(fromhelper) < 0)
  {
    close(tohelper[0]);
    close(tohelper[1]);
    return MAHelperCommandInternalError;
  }
  
  if (fdret)
  {
    if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sv) < 0)
    {
      close(tohelper[0]);
      close(tohelper[1]);
      close(fromhelper[0]);
      close(fromhelper[1]);
      return MAHelperCommandInternalError;
    }
  }
  
  if ((pid = fork()) < 0)
  {
    if (fdret)
    {
      close(sv[0]);
      close(sv[1]);
    }
    close(tohelper[0]);
    close(tohelper[1]);
    close(fromhelper[0]);
    close(fromhelper[1]);
    return MAHelperCommandInternalError;
  }
  else if (pid == 0)
  {
    char *const envp[] = { NULL };
    char sockfd[32];
    
    if (fdret)
    {
      sprintf(sockfd, "%i", sv[1]);
      close(sv[0]);
    }
    close(0);
    dup2(tohelper[0], 0);
    close(tohelper[0]);
    close(tohelper[1]);
    
    close(1);
    dup2(fromhelper[1], 1);
#ifndef DO_DEBUG
    close(2);
    dup2(fromhelper[1], 2);
#endif
    close(fromhelper[0]);
    close(fromhelper[1]);
    
    if (fdret)
      execle(helperPath, helperPath, sockfd, NULL, envp, NULL);
    else
      execle(helperPath, helperPath, NULL, envp, NULL);
    _exit(MAHelperCommandHelperNotFound);
  }
  signal(SIGPIPE, SIG_IGN);
  
  close(tohelper[0]);
  close(fromhelper[1]);
  if (fdret)
    close(sv[1]);
  
  DEBUG("sending auth...");
  if (write(tohelper[1], &extAuth, sizeof(extAuth)) != sizeof(extAuth))
    ok= 0;
  else
  {
    DEBUG("sending command...");
    written= write(tohelper[1], &command, sizeof(MAHelperCommand));  
    if (written != sizeof(MAHelperCommand))
      ok= 0;
  }
  DEBUG("end sending.");
  if (ok && fdret)
  {
    char buffer[1024];
    
    // helper will send an error message in case of error
    // otherwise, an empty string and the fd later
    DEBUG("reading reply code...");
    *fdret= -1;
    // read reply code 
    if (read(fromhelper[0], buffer, sizeof(buffer)) < 0)
      ok= false;
    else
    {
      DEBUG("reply from helper was '%s'", buffer);
      if (buffer[0])
      {
        if (error_message)
          *error_message= strdup(buffer);
      }
      else
      {
        DEBUG("waiting for fd from socket...");
        // read the fd from the socket to the helper
        if (read_fd(sv[0], buffer, sizeof(buffer), fdret) < 0 || *fdret < 0)
        {
        }
        // this is the file name (not error)
        buffer[sizeof(buffer)-1]= 0;
        if (error_message)
          *error_message= strdup(buffer);
        
        DEBUG("fd arrived %i (%s)", *fdret, buffer);
      }
    }
  }
  
  if (ok && output_callback) 
  {
    char line[1024];
    int count;
    DEBUG("waiting for process to finish");
    while ((rc= waitpid(pid, &childStatus, WNOHANG)) == 0)
    {
      count= read(fromhelper[0], line, sizeof(line));
      if (count > 0)
      {
        line[count]= 0;
        (*output_callback)(line, callback_data);
      }
    }
  }
  else
  {
    DEBUG("waiting for error process to finish");
    rc= waitpid(pid, &childStatus, 0);
  }
  DEBUG("end");
  close(fromhelper[0]);
  if (fdret)
    close(sv[0]);
  close(tohelper[1]);
  
  if (WEXITSTATUS(childStatus) == MAHelperCommandNeedsRestart)
    goto restart;
	
  if (!ok)
    return MAHelperCommandInternalError;
  
  if (rc < 0)
    return MAHelperCommandInternalError;
  
  if (!WIFEXITED(childStatus))
    return MAHelperCommandInternalError;
  
  return WEXITSTATUS(childStatus);
}