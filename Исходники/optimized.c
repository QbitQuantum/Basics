int main(int argc, char **argv) 
{
    int listenfd;
    int * connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

/******************************
    Section to setup the DLL
******************************/

    // This will be the function stub used for addition
    // This would be any service that we want. 
    // For test purposes, we are keeping it simple
    // Later we will extend it to add even more 
    // Services
    char * add_service = "adder_lib.so";

    dlhandle = dlopen ("./cgi-bin/adder_lib.so", RTLD_LAZY);

    // This handle will be used to access particular functions
    // Within the library marked. 
    //dlhandle = dlopen(add_service, RTLD_LAZY); // No need to have staticly
                                          // linked to program specified
                                          // in "service".

    if (dlhandle == NULL)  {
        printf("Service %s Not Found:  %s\n", add_service, dlerror());
    }
    
    // Now we shall get the add function stub
    functionstub = dlsym(dlhandle, "add");

    if (!functionstub)  {
        printf("Problem calling add_function(): %s\n", dlerror());
    }
    
    // The function stub will be available to all the threads for use.

/******** Section Ends *********/

    /* Check command line args */
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(1);
    }

    listenfd = Open_listenfd(argv[1]);
    while (1) {
	clientlen = sizeof(clientaddr);
    connfd = (int *) malloc( sizeof( int ) ) ;
	*connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); //line:netp:tiny:accept
        Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, 
                    port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
	//doit(connfd);                                             //line:netp:tiny:doit
    pthread_t pth;  
    pthread_create(&pth,NULL,doit, connfd);
    }
}