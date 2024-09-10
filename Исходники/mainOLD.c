void pipedecryption(FILE *input, int CoreNumber){

int ProcessCount = 0;
fd_set rfds;
fd_set wfds;
// we are only using the number of cores - because we restrict one to the parent
int ProcessTotal = CoreNumber-1;
int ProcessArr[ProcessTotal];
FD_ZERO(&rfds);
FD_ZERO(&wfds);
// timeval is used for the SELECT function
struct timeval tv;
tv.tv_sec = 100;
tv.tv_usec = 0; 
 
int EncryptionDirectoryPipe[ProcessTotal][2];
int ProcessReadyPipe[ProcessTotal][2];
int ProcessStatus = 1;
int RRcount = 0;
char* directory[2050];
int directorysize;
time_t ltime;



for(int i = 0; i < ProcessTotal; i++){
        // create the pipes. Include error handling if it fails.
        if(pipe(EncryptionDirectoryPipe[i])||pipe(ProcessReadyPipe[i]))
        {
            printf("[%s] Parent #%i failed to pipe. Exiting.\n",CurrTime(ltime), getpid());
            exit(-1);
        }
 
        int ChildID = fork();
        if (ChildID){           // parent process
        FD_SET(ProcessReadyPipe[i][1],&wfds);
        FD_SET(EncryptionDirectoryPipe[i][1],&wfds);
        FD_SET(ProcessReadyPipe[i][0],&rfds);
        // close the writing end of the pipe, we willl be reading from the child for its status
        close(ProcessReadyPipe[i][1]);
        // close reading end, we will be writing to the child processes
        close(EncryptionDirectoryPipe[i][0]);
        // add the child into the ProcessArr to keep track of processes created
        ProcessArr[i] = ChildID;
}
 
 
        else if (ChildID == 0){         // child process
        // close appropriate ends of the pipe for the child process
        close(ProcessReadyPipe[i][0]);
        close(EncryptionDirectoryPipe[i][1]);

        while(1){
        // read from the pipe the length of the incoming msg into dirsize. If its null, the pipe is empty, 
        // so finish the loop with a break.
        int dirsize = 0;
        int readstatus = read(EncryptionDirectoryPipe[i][0], &dirsize,sizeof(int));
        if (readstatus==0){
                break;}
        // get the incoming msg using the size dirsize given in the privious msg
        // create character array with null termination, then zero it out
        char directorybuffer[dirsize+1];
        bzero(&directorybuffer, dirsize+1);
        read(EncryptionDirectoryPipe[i][0], directorybuffer,dirsize);
        // parse the directory into input and output pointers respectfully
        char *inouttemp = strtok(directorybuffer, " ");
        char *input = inouttemp;
        inouttemp = strtok(NULL, " ");
        char *output = inouttemp;
        output = strtok(output, "\n");
        // run decryption
        printf("[%s] Child Process ID #%i will decrypt %s. \n",CurrTime(ltime),getpid(),input);
        if(decrypt(input,output) > 0)
        printf("[%s] Process ID #%i decrypted %s successfully. \n",CurrTime(ltime),getpid(),input);
        if
        // Case for FCFS: send msg to parent saying its ready.
        write(ProcessReadyPipe[i][1],&ProcessStatus,sizeof(ProcessStatus));
        }
        // Process is done all jobs. Close its writing pipe.
        printf("closing all work, jobs are done \n");
        close(ProcessReadyPipe[i][1]);
        exit(0);
        }
        else{