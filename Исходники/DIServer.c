int
main(int argc, char *argv[])
{
	pid_t 	pid;
	int		status;
  int   ServerFD[2];
  int   ServerFD2[2];
  char  *data = "accept";
  char  *data2 = "reject";
  char  *terminate = "terminate";
  char  pubbuf[1025];
  char  pubbufend[1025];
  char  pubbufterm[1025];
  char  subbuf[1025];
  char  subbufend[1025];
  char  subbufterm[1025];

  pipe(ServerFD);
  pipe(ServerFD2);
	pid = fork();

	if(pid == 0){//this is the child of the main process, the DIServer
    int i;
		//n is # of publisher
		int n = atoi(argv[1]);
		//m is number of subscribers
		int m = atoi(argv[2]);
    //t are topics	
    int t = atoi(argv[3]);
    pthread_t pubthreads[n];
    pthread_t subthreads[m];
    int   rc;
    int   rc2;
    void  *pubthreadstatus;
    void  *subthreadstatus;

    pthread_attr_t pubattr;
    pthread_attr_t subattr;

    pthread_attr_init(&pubattr);
    pthread_attr_setdetachstate(&pubattr, PTHREAD_CREATE_JOINABLE);

    pthread_attr_init(&subattr);
    pthread_attr_setdetachstate(&subattr, PTHREAD_CREATE_JOINABLE);

    pthread_mutex_init(&mutexlock,NULL);


    Record record[n+m];
		/*need to use n and m to create child procs of the 
		DIServer, publishers and subscriers*/
		//loop to create publisher procs and stroe pid in array;
		pid_t pubpid;
		pid_t subpid;

		//map space for the pub array
		pubpids = mmap(0, MAX_PIDS*sizeof(pid_t), PROT_READ|PROT_WRITE,
              MAP_SHARED | MAP_ANONYMOUS, -1, 0);
		 if (!pubpids) {
    		perror("mmap failed");
    		exit(1);
 		 }
  		memset((void *)pubpids, 0, MAX_PIDS*sizeof(pid_t)); 		 
 		 //map space for sub array
		subpids = mmap(0, MAX_PIDS*sizeof(pid_t), PROT_READ|PROT_WRITE,
              MAP_SHARED | MAP_ANONYMOUS, -1, 0);
		 if (!subpids) {
    		perror("mmap failed");
    		exit(1);
 		 }
  		memset((void *)subpids, 0, MAX_PIDS*sizeof(pid_t));

  		//loop to creat forked pubs
  		for(i=0;i<n;i++)
  		{
        //create the record struct
        //create the publisher struct
        int z;
        Publisher pub;
        pub.pubConnect = "Pub Connect";
        pub.pubTopic = "Topic 1";//topic of interest
        pub.pubEnd = "End";
        pub.pubterm = "terminate";
        pipe(pub.fileDescriptor);
  			pubpid = fork();
        int articles;
        char article[12];
  			if(pubpid == 0)
  			{
          //doPublisher(n);
          write(pub.fileDescriptor[1], pub.pubConnect, strlen(pub.pubConnect));
          if ((z = read(ServerFD[0], pubbuf, 1024)) >= 0) {
              pubbuf[z] = 0; /* terminate the string */ 
              //printf("pub read %d bytes from the DIServer pipe: \"%s\"\n", z, pubbuf);
              if (strcmp(pubbuf, data) == 0)
              {
                write(pub.fileDescriptor[1], pub.pubTopic, strlen(pub.pubTopic));
                if ((z = read(ServerFD[0], pubbufend, 1024)) >= 0) {
                  pubbufend[z] = 0;
                  //printf("pub read %d bytes from the DIServer pipe: \"%s\"\n", z, pubbufend);
                  if (strcmp(pubbufend, data) == 0){
                    write(pub.fileDescriptor[1], pub.pubEnd, strlen(pub.pubEnd));
                    if((z = read(ServerFD[0], pubbufend, 1024)) >= 0) {
                     // printf("pub read %d bytes from the DIServer pipe: \"%s\"\n", z, pubbufend);
                      /*if (strcmp(pubbufend, data)==0){
                        for (articles = 0; articles<10;articles++){
                          if(articles%2 != 0){
                            sprintf(article, "Topic 1 Article %d", articles);
                            write(pub.fileDescriptor[1], article, strlen(article));
                          }
                        }
                      }*/
                    }

                  }
                  else{
                    write(pub.fileDescriptor[1], pub.pubterm, strlen(pub.pubterm));
                    continue;
                 }
                }
              }
              else{
                write(pub.fileDescriptor[1], pub.pubterm, strlen(pub.pubterm));
                continue;
              }

          } 
          else 
              perror("read");
          //if reads accept then write to publisher pipe 
  				exit(0);
  			}
  			else if (pubpid < 0){
  				perror("fork failed");
  			}
        
  			else{//back to the DIServer

          record[i].pipe = pub.fileDescriptor;
          record[i].type = "Publisher";
          record[i].pid = i+1;
          record[i].selectTopics = pub.pubTopic;
          record[i].serverPipe = ServerFD;
          rc=pthread_create(&pubthreads[i],&pubattr,pubThr_fn,(void *) &record[i]);
          if(rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
          }
          pthread_attr_destroy(&pubattr);
          rc = pthread_join(pubthreads[i], &pubthreadstatus);
          // want to create the thread here, then handle all of reading a writng of pipes in thread handler}
  		  }
      }

  		//loop to create forked subs;
      for(i=0;i<m;i++)
      {
        //create the subscriber struct
        int z;
        Subscriber sub;
        sub.subConnect = "Sub Connect";
        sub.subTopic = "Topic 1"; //topic of interest
        sub.subEnd = "End";
        sub.subterm = "terminate";
        pipe(sub.fileDescriptor);
        subpid = fork();
        if(subpid == 0)
        {
          //doPublisher(n);
          write(sub.fileDescriptor[1], sub.subConnect, strlen(sub.subConnect));
          if ((z = read(ServerFD2[0], subbuf, 1024)) >= 0) {
              subbuf[z] = 0; /* terminate the string */ 
              //printf("sub read %d bytes from the DIServer pipe: \"%s\"\n", z, subbuf);
              if (strcmp(subbuf, data) == 0)
              {
                write(sub.fileDescriptor[1], sub.subTopic, strlen(sub.subTopic));
                if ((z = read(ServerFD2[0], subbufend, 1024)) >= 0) {
                  subbufend[z] = 0;
                 // printf("sub read %d bytes from the DIServer pipe: \"%s\"\n", z, subbufend);
                  if (strcmp(subbufend, data) == 0){
                    write(sub.fileDescriptor[1], sub.subEnd, strlen(sub.subEnd));
                    if((z = read(ServerFD2[0], subbufend, 1024)) >= 0) {
                      //printf("sub read %d bytes from the DIServer pipe: \"%s\"\n", z, subbufend);
                    }
                  }
                  else{
                    write(sub.fileDescriptor[1], sub.subterm, strlen(sub.subterm));
                    continue;
                 }
                }
              }
              else{
                write(sub.fileDescriptor[1], sub.subterm, strlen(sub.subterm));
                continue;
              }

          } 
          else 
              perror("read");
          //if reads accept then write to publisher pipe 
          exit(0);
        }
        else if (subpid < 0){
          perror("fork failed");
        }
        else{//back to the DIServer
          record[i+n].pipe = sub.fileDescriptor;
          record[i+n].type = "Subscriber";
          record[i+n].pid = i+1;
          record[i+n].selectTopics = sub.subTopic;
          record[i+n].serverPipe = ServerFD2;

          rc2 = pthread_create(&subthreads[i],&subattr,subThr_fn,(void *) &record[i+n]);
          if(rc2){
            printf("ERROR; return code from pthread_create() is %d\n", rc2);
            exit(-1);
          }
          pthread_attr_destroy(&subattr);
          rc2 = pthread_join(subthreads[i], &subthreadstatus);


        }
      }
      /*
      pthread_attr_destroy(&subattr);
      for(i=0;i<n;i++){
        printf("here\n");
        rc = pthread_join(pubthreads[i], &pubthreadstatus);
        if (rc) {
          printf("ERROR; return code from pthread_join() is %d\n", rc);
          exit(-1);
        }
      }
      pthread_attr_destroy(&subattr);
      for(i=0;i<m;i++){
        printf("here\n");
        rc2 = pthread_join(subthreads[i], &subthreadstatus);
        if (rc2) {
          printf("ERROR; return code from pthread_join() is %d\n", rc2);
          exit(-1);
        }
      }
      */
      /*this works because the way code is written, if it 
      makes it here all connections have been made*/
      //printf("all pubs and subs have connected to server\n");
      for(i = 0; i<n+m; i++){
        printf("Type:%s, ID: %d, Topic: %s\n", record[i].type, record[i].pid, record[i].selectTopics);
      }
      //begin termination

      write(ServerFD[1], terminate, strlen(terminate));
      close(ServerFD[1]);
      for(i = 0; i<n+m; i++){
        printf("%s-%d: terminated\n", record[i].type,record[i].pid);
      }
      //printf("%s\n", );
      pthread_exit(NULL);

	
}
	else
		wait(&status);
		//main process just needs to wait for everything else to be done.


	return(0);
}