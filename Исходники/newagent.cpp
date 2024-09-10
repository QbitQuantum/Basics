int newagent::start_process(const char *command,int & error_code,const char * local_dir,const char * user,const char * password) {
    error_code=0;
#ifdef _WIN32
    PROCESS_INFORMATION process;
    STARTUPINFO si;
    HANDLE res=0;
    bool ok=false;
    HANDLE other_user=0;
#ifdef _DEBUG
    if (!strcmp(command,"forceerror")) *((int *)0)=5;
#endif
    memset(&si,0,sizeof(si));
    si.cb          = sizeof(si);
    si.lpTitle     = (char*)command;
    si.wShowWindow = SW_SHOWDEFAULT;
    si.dwFlags     = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOWNORMAL;
    char current_dir[256]=" ;103<;01",c_dir[256];
    if (local_dir&&*local_dir) {
        strcpy(c_dir,local_dir);
    }
    else {    
        if (!is_debug_session&&read_key("03",(unsigned char *)current_dir,sizeof(current_dir))) {
            char * finger=current_dir;
            int bs=4;
            while (*finger&&bs) {
                if (*finger=='\\') bs--;
                finger++;
            }
            if (*finger) sprintf(c_dir,maped_drive"\\%s",finger); else sprintf(c_dir,maped_drive"\\");
        } 
        else 
            strcpy(c_dir,".");
        
    }
    if (is_debug_session) {
        ok=(bool)CreateProcess(NULL,(char*)command,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,c_dir,&si,&process);
        if (!ok) error_code=GetLastError();
    } 
    else {
        if (!local_dir&&!drive_maped) do_map_drive(error_code);
        if(!error_code) {
            HANDLE uh=server_user;
            if (user&&*user) {
                logonu(other_user,unscr((char*)user),unscr((char*)password),error_code);
                uh=other_user;
            }
            if (!error_code) {
                if (!ImpersonateLoggedOnUser(uh)) error_code=GetLastError();
                if (!error_code) {
                    char saved_dir[256];
                    if (!GetCurrentDirectory(sizeof(saved_dir),saved_dir)) {
                        logfile("GetCurrentDirectory failed\r\n");
                        error_code=GetLastError();
                    }
                    else {
                        if (!SetCurrentDirectory(c_dir)) {
                            error_code=GetLastError();
                            if (error_code==2) error_code=267;
                            logfile ("SetCurrentDirectory failed %s %i\r\n",c_dir,error_code);
                        }
                        else {
                            ok=(bool)CreateProcessAsUser( uh,NULL,(char*)command,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,c_dir,&si,&process);
                            if (!ok) error_code=GetLastError();
                            if (ok&&!SetCurrentDirectory(saved_dir))  {
                                logfile("restore current dirctory failed %s\r\n",saved_dir);
                                error_code=GetLastError();
                            }
                        } 
                    }             
                    RevertToSelf();
                }
            }
        }
    }
    if (ok) {
        res=process.hProcess;
        CloseHandle(process.hThread);
        logfile("Process started: %s\r\n",command);
    }
    else {
        logfile("Process failed: %s error(%i) %s\r\n",command,error_code,c_dir);
    }
    if (other_user) CloseHandle(other_user);
    if (ok) 
        return (int)res;
    else
        return 0;
    
#else
    //  if (is_debug_session)
    {
        long res;
        _chdir(cur_dir);
        pid_t pid;
        if (invoke_program(command, res, false, NULL, NULL, &pid))
            return pid;
        printf("invoke_program error %d\n", res);
        error_code=res;
        logfile("Process failed: %s error(%i) %s\r\n",command,error_code,cur_dir);
        /* not sure these should be freed here
        free(user);
        free(password);
        */
        return 0;
    }
#endif
}