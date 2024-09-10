/* PID: procexec(const commandline[])
 * Executes a program. Returns an "id" representing the new process (or 0 on
 * failure).
 */
static cell AMX_NATIVE_CALL n_procexec(AMX *amx, const cell *params)
{
  TCHAR *pgmname;
  #if defined __WIN32__ || defined _WIN32 || defined WIN32
    BOOL IsWinNT;
    OSVERSIONINFO VerInfo;
    STARTUPINFO si;
    SECURITY_ATTRIBUTES sa;
    SECURITY_DESCRIPTOR sd;
    PROCESS_INFORMATION pi;
  #elif defined _Windows
    HINSTANCE hinst;
  #elif defined __LINUX__ || defined __FreeBSD__ || defined __OpenBSD__
  	pid_t pid;
  #endif

  amx_StrParam(amx,params[1],pgmname);

  #if defined __WIN32__ || defined _WIN32 || defined WIN32
    /* most of this code comes from a "Borland Network" article, combined
     * with some knowledge gained from a CodeProject article
     */
    closepipe();

    VerInfo.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
    GetVersionEx(&VerInfo);
    IsWinNT = VerInfo.dwPlatformId==VER_PLATFORM_WIN32_NT;

    if (IsWinNT) {       //initialize security descriptor (Windows NT)
      InitializeSecurityDescriptor(&sd,SECURITY_DESCRIPTOR_REVISION);
      SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
      sa.lpSecurityDescriptor = &sd;
    } else {
      sa.lpSecurityDescriptor = NULL;
    } /* if */
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;         //allow inheritable handles

    if (!CreatePipe(&newstdin,&write_stdin,&sa,0)) { //create stdin pipe
      amx_RaiseError(amx, AMX_ERR_NATIVE);
      return 0;
    } /* if */
    if (!CreatePipe(&read_stdout,&newstdout,&sa,0)) { //create stdout pipe
      closepipe();
      amx_RaiseError(amx, AMX_ERR_NATIVE);
      return 0;
    } /* if */

    GetStartupInfo(&si);      //set startupinfo for the spawned process
    si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOWNORMAL;
    si.hStdOutput = newstdout;
    si.hStdError = newstdout;     //set the new handles for the child process
    si.hStdInput = newstdin;

    /* spawn the child process */
    if (!CreateProcess(NULL,(TCHAR*)pgmname,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi)) {
      closepipe();
      return 0;
    } /* if */
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    Sleep(100);
    return pi.dwProcessId;
  #elif defined _Windows
    hinst=WinExec(pgmname,SW_SHOW);
    if (hinst<=32)
      hinst=0;
    return (cell)hinst;
  #elif defined __LINUX__ || defined __FreeBSD__ || defined __OpenBSD__
    /* set up communication pipes first */
    closepipe();
    if (pipe(pipe_to)!=0 || pipe(pipe_from)!=0) {
      closepipe();
      amx_RaiseError(amx, AMX_ERR_NATIVE);
      return 0;
    } /* if */

    /* attempt to fork */
    if ((pid=fork())<0) {
      closepipe();
      amx_RaiseError(amx, AMX_ERR_NATIVE);
      return 0;
    } /* if */

    if (pid==0) {
      /* this is the child process */
      #define MAX_ARGS  10
      TCHAR *args[MAX_ARGS];
      int i;
      dup2(pipe_to[0],STDIN_FILENO);    /* replace stdin with the in side of the pipe */
      dup2(pipe_from[1],STDOUT_FILENO); /* replace stdout with the out side of the pipe */
      close(pipe_to[0]);                /* the pipes are no longer needed */
      close(pipe_to[1]);
      close(pipe_from[0]);
      close(pipe_from[1]);
      pipe_to[0]=-1;
      pipe_to[1]=-1;
      pipe_from[0]=-1;
      pipe_from[1]=-1;
      /* split off the option(s) */
      assert(MAX_ARGS>=2);              /* args[0] is reserved */
      memset(args,0,MAX_ARGS*sizeof(TCHAR*));
      args[0]=pgmname;
      for (i=1; i<MAX_ARGS && args[i-1]!=NULL; i++) {
        if ((args[i]=strchr(args[i-1],' '))!=NULL) {
          args[i][0]='\0';
          args[i]+=1;
        } /* if */
      } /* for */
      /* replace the child fork with a new process */
      if(execvp(pgmname,args)<0)
        return 0;
    } else {
      close(pipe_to[0]);                /* close unused pipes */
      close(pipe_from[1]);
      pipe_to[0]=-1;
      pipe_from[1]=-1;
    } /* if */
    return pid;
  #else
    return (system(pgmname)==0);
  #endif
}