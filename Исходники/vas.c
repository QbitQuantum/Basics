// main method - program entry point
int main()
{
    char cmd[81]; // array of chars(a string)
    char* cmdTokens[20]; // array of strings
    int count; // number of times to execute command
    int parallel; // whether to run in parallel or sequentially
    int timeout; // max seconds to run set of each command
    
    while (TRUE) 
    { // main shell input loop
        
        // begin parsing code 
        printf("vas> ");
        fgets(cmd, sizeof(cmd), stdin);
        if (cmd[0] == '\n') continue;
	readCmdTokens(cmd, cmdTokens);
	if(strcmp(cmdTokens[0],"exit")==0)
	   exit(0); 
 	do{
	   printf("  count> ");
	   scanf("%d",&count);
	   while(getchar()!='\n');
	  }while(count<0);
	printf("  [p]arallel or [s]equential> ");
	parallel = (readChar() == 'p') ? TRUE : FALSE;
	if(parallel==FALSE)	
	{
	   do{	
	      printf("  timeout> ");
	      scanf("%d",&timeout);
	      while(getchar()!='\n');
	   }while(timeout<0);
	}
        // end parsing code
        
        
	if(parallel==FALSE)  //sequential with timeout
	{	
	   int i,stat;
	   time_t t;
	   pid_t wpid;
	   for(i=0;i<count;i++)
	   {
	      pid_t p;
	      p=fork();
	      if(p<0)printf("\nProcess creation failed");   
	      else if(p>0)  //parent process
	      {
		int waittime=0;		
		do    	      //parent waiting
		{
		   wpid=waitpid(p,&stat,WNOHANG);
		   if(wpid==0)
		   {
		      if(waittime<timeout)
		      {
			   sleep(1);
			   waittime+=1;
		      }
		      else
			   kill(p,SIGKILL);  //kill child on timeout
		   }
		 }while(wpid==0 && waittime<=timeout);
		 if(WIFSIGNALED(stat))printf("\nTimeout\n");
	       }
	       else    //child process
	       {
		  t=time(NULL);
		  char* time;
	 	  time=ctime(&t);		
		  printf("\nProcess with ID: %d starts at time: %s",getpid(),time);	 	
		  if(execvp(cmdTokens[0], cmdTokens)<0)
		    printf("\nCannot execute %s",cmdTokens[0]);
	       }
	     }
	   }
	/*if(parallel==FALSE)    //sequential w/o timeout
	{
	   pid_t p[10];
	   int i;
	   for(i=0;i<count;i++)
	   {
		p[i]=fork();
	   	if(p[i]<0)printf("\nFork failed");
		else if(p[i]>0)wait();  //parent process
		else    //child process
		{
		   time_t t;
		   t=time(NULL);
		   char* time;
		   time=ctime(&t);
		   printf("\nProcess with ID: %d starts at time: %s",getpid(),time);
		   if(execvp(cmdTokens[0],cmdTokens)<0)printf("\nCannot execute %s",cmdTokens[0]);
	 	}
	   }
	}*/   //sequential ends
	
 	/*else   //parallel with timeout
	{ 
	   int i,stat;
	   pid_t wpid;
	   #pragma omp parallel private(i) shared(cmdTokens)   //creating threads
	   {		
		#pragma omp for		//parallel for
		for(i=0;i<count;i++)
		{
		   pid_t p;
		   p=fork();
		   if(p<0)printf("\nfork failed");
		   else if(p>0)   //parent process
		   {
			int waittime=0;
			do       //parent process waiting
			{
			   wpid=waitpid(p,&stat,WNOHANG);
			   if(wpid==0)
			   {
				if(waittime<timeout)
				{
				   sleep(1);
				   waittime++;
				}
				else
				{
				   kill(p,SIGKILL);   //kill child process on timeout
				   //wait();
				}
			   }
			   else break;
			}while(wpid==0 && waittime<=timeout);
			if(WIFSIGNALED(stat))printf("\nTimeout\n");
		   }
		   else   //child process
		   {
		      time_t t;
		      t=time(NULL);
		      char* time;
	 	      time=ctime(&t);		
		      printf("\nProcess with ID: %d starts at time: %s",getpid(),time);	 	
		      if(execvp(cmdTokens[0], cmdTokens)<0)
		      {   
			printf("\nCannot execute %s",cmdTokens[0]);
			//exit(0);
		      }
		   }
	        }
		
	   }
	}*/   //parallel ends	

	else   //parallel w/o timeout
	{ 
	   int i;
	   pid_t p[100];
	   #pragma omp parallel private(i) shared(cmdTokens)   //creating threads
	   {		
		#pragma omp for		//parallel for
		for(i=0;i<count;i++)
		{
		  
		   p[i]=fork();
		   if(p[i]<0)printf("\nfork failed");
		   else if(p[i]>0) wait();   //parent process
		   else   //child process
		   {
		      time_t t;
		      t=time(NULL);
		      char* time;
	 	      time=ctime(&t);		
		      printf("\nProcess with ID: %d starts at time: %s",getpid(),time);	 	
		      if(execvp(cmdTokens[0], cmdTokens)<0)
		      {   
			printf("\nCannot execute %s",cmdTokens[0]);
			//exit(0);
		      }
		   }
	        }
		
	   }
	}   //parallel ends
	
    }   //while ends
    
}