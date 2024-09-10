void JNICALL Java_java_lang_Runtime_00024SubProcess_createProcess0 (JNIEnv *env, jobject obj, jobjectArray cmdarray, jobjectArray envp, jstring dir, jlongArray la){
    jobject jo; 

     const char *strChain;
     int i;

     char *cmdDir = NULL;
     char *strCmd = NULL; 

     // Get the working directory of the subprocess:
     if ( dir != NULL ) {
         char* str = (char *)env->GetStringUTFChars(dir, 0);
         cmdDir = (char *)malloc(1+strlen(str)); // + NUL symbol
         *cmdDir = '\0';
         strcat(cmdDir, str);
         env->ReleaseStringUTFChars(dir, str);
     }  

     // Get the the command to call and its arguments (it must be non-null):
     int lenargv = 0;
     lenargv = env->GetArrayLength(cmdarray);
     char *argv[lenargv+1];
     for ( i = 0; i < lenargv; i++ ) {
         jo = env->GetObjectArrayElement((jobjectArray)((jobject)cmdarray), (jsize) i);
         strChain = env->GetStringUTFChars((jstring) jo, 0);
         strCmd = (char *)malloc(1+strlen(strChain)); // + NUL symbol
         *strCmd = '\0';
         strcat(strCmd, strChain);
         argv[i] = strCmd;
         env->ReleaseStringUTFChars((jstring) jo, strChain);
     }
     argv[lenargv] = (char *) 0; // NULL pointer

     // Get the array, each element of which has environment variable settings:
     int lenEnvp = 0;
     if (envp != NULL) {
         lenEnvp += env->GetArrayLength(envp);
     }
     char *strEnvpBeginAA[lenEnvp + 1];
     if (envp != NULL) {
         for ( i = 0; i < lenEnvp; i++ ) {
             jo = env->GetObjectArrayElement((jobjectArray)((jobject)envp), (jsize) i);
             strChain = env->GetStringUTFChars((jstring) jo, 0);
             strCmd = (char *)malloc(1+strlen(strChain)); // + NUL symbol
             *strCmd = '\0';
             strcat(strCmd, strChain);
             strEnvpBeginAA[i] = strCmd;
             env->ReleaseStringUTFChars((jstring) jo, strChain);
         }
     }

     strEnvpBeginAA[lenEnvp] = (char *) 0; // NULL pointer

     //define stdI/O/E for future process:
     int fildesO[2] = {-1,-1};
     int fildesE[2] = {-1,-1};
     int fildesI[2] = {-1,-1};
     // Controlling pipe.
     // Child process if successfully executed will close the handle (by system)
     // If execv failed the write(..) call will write 4 bytes in this stream.
     // Thus we can distinguish executed proccesses and failed ones.
     int fildesInfo[2] = {-1,-1};

     if (pipe(fildesO) == -1
             || pipe(fildesI) == -1
             || pipe(fildesE) == -1
             || pipe(fildesInfo) == -1) {
         if (fildesO[0] != -1) close(fildesO[0]);
         if (fildesO[1] != -1) close(fildesO[1]);
         if (fildesE[0] != -1) close(fildesE[0]);
         if (fildesE[1] != -1) close(fildesE[1]);
         if (fildesI[0] != -1) close(fildesI[0]);
         if (fildesI[1] != -1) close(fildesI[1]);
         if (fildesInfo[0] != -1) close(fildesInfo[0]);
         if (fildesInfo[1] != -1) close(fildesInfo[1]);
         Error("Stdin/stdout pipes creation failed:", env, la); 
         Error(strerror(errno), env, la); 
         return;
     }
     int spid = fork();
 
     if (spid == -1) {
         close(fildesI[0]);
         close(fildesI[1]);
         close(fildesO[0]);
         close(fildesO[1]);
         close(fildesE[0]);
         close(fildesE[1]);
         close(fildesInfo[0]);
         close(fildesInfo[1]);
         Error("Fork failed\n", env, la); 
     }

     if (spid==0) {
         ///// Child process code ///////////////
         dup2(fildesI[0], 0);
         dup2(fildesO[1], 1);
         dup2(fildesE[1], 2);
         close(fildesI[0]);
         close(fildesI[1]);
         close(fildesO[0]);
         close(fildesO[1]);
         close(fildesE[0]);
         close(fildesE[1]);
         close(fildesInfo[0]);
         long close_on_exec = FD_CLOEXEC; // set close on exec bit
         fcntl(fildesInfo[1], F_SETFD, close_on_exec);

         // Get the working directory of the subprocess:
         if ( cmdDir != NULL ) {
             int res = chdir(cmdDir);
             if (res == -1) {
                 write(fildesInfo[1], &errno, sizeof(int));
                 INFO("chdir failed: " << strerror(errno));
                 kill(getpid(), 9);
             }
             free(cmdDir);
         }

         char *newArgv[lenargv+2];
         if (lenEnvp == 0) {
             execvp(argv[0], argv);
             if (errno == ENOEXEC) {
               // give another try
               for (i=0; i<lenargv; i++) {
                 strCmd = (char *)malloc(1+strlen(argv[i])); // + NUL symbol
                 *strCmd = '\0';
                 strcat(strCmd, argv[i]);
                 newArgv[i+1] = strCmd;
               }
               newArgv[0] = strdup("/bin/sh");
               newArgv[lenargv+1] = (char *)0;
               execvp(newArgv[0], newArgv);
             }
         } else {
             execve(argv[0], argv, strEnvpBeginAA);
             if (errno == ENOEXEC) {
               // give another try
               for (i=0; i<lenargv; i++) {
                 strCmd = (char *)malloc(1+strlen(argv[i])); // + NUL symbol
                 *strCmd = '\0';
                 strcat(strCmd, argv[i]);
                 newArgv[i+1] = strCmd;
               }
               newArgv[0] = strdup("/bin/sh");
               newArgv[lenargv+1] = (char *)0;
               execve(newArgv[0], newArgv, strEnvpBeginAA);
             }

             if(strchr(argv[0], '/') == NULL) {
                 char* curDir = NULL;
                 char* cmdPath = NULL;
                 char* dirs = NULL;
                 if ((dirs = getenv("PATH")) != NULL) {
                     int len = 0;
                     curDir = strtok(dirs, ":");
                     while(curDir != NULL) {
                         if((len = strlen(curDir)) != 0) {
                             cmdPath = (char *)malloc(len+1+strlen(argv[0])+1);
                             *cmdPath = '\0';
                             strcat(strcat(strcat(cmdPath, curDir), "/"), argv[0]);
                             if (fopen(cmdPath, "r") != NULL) {
                                 execve(cmdPath, argv, strEnvpBeginAA);
                                 //XXX: should we inform only of a last error among all possible execve atempts?
                             }
                             free(cmdPath);
                         }
                         curDir = strtok(NULL, ":");
                     }
                 }
             }
         }
         write(fildesInfo[1], &errno, sizeof(int));
         INFO("Process initiation failed: " << strerror(errno));
         for (i=0; i<lenargv+1; i++) {
           if (newArgv[i] != NULL) {
             free(newArgv[i]);
           }
         }
         // kill self
         kill(getpid(), 9);
     }
     ///// End of child process code ////////////

     close(fildesO[1]);
     close(fildesI[0]);
     close(fildesE[1]);
     close(fildesInfo[1]);

     for (i=0; i<lenargv; i++) {
       if (argv[i] != NULL) {
         free(argv[i]);
       }
     }

     for (i=0; i<lenEnvp; i++) {
       if (strEnvpBeginAA[i] != NULL) {
         free(strEnvpBeginAA[i]);
       }
     }

     // get execution status from child
     int errno_child;
     int res = read(fildesInfo[0], &errno_child, sizeof(int));
     if (res == 4) {
         Error("Process initiation failed", env, la);
         Error(strerror(errno_child), env, la);
         close(fildesO[0]);
         close(fildesI[1]);
         close(fildesE[0]);
         close(fildesInfo[0]);
         return;
     }

   jboolean jb = true;
   jlong *lp = (jlong*)env->GetLongArrayElements(la, &jb);
   lp[0] = (jlong) spid; // new process number 
   lp[1] = (jlong) fildesI[1];
   lp[2] = (jlong) fildesO[0];
   lp[3] = (jlong) fildesE[0];
   fcntl(fildesO[0], F_SETFL, 0); //XXX:to set !O_NONBLOCK because it is sometimes set by default and it should be investigated
   fcntl(fildesE[0], F_SETFL, 0); //XXX:to set !O_NONBLOCK because it is sometimes set by default and it should be investigated
   env->ReleaseLongArrayElements(la, lp, 0);

   close(fildesInfo[0]);
}