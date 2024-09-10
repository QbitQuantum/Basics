/* Setup(..) function is simply used to 'setup' the standard features of 
 * the netpipe modules.  tcp,netpipe-related stuff.  This does no actual
 * 'setup' of any InfiniBand stuff, other than passing/storing
 * the parameters from the command line.... the 'initIB' function
 * is called from here though to do IB initialization.
 */
void Setup(ArgStruct *p)
{

 int one = 1;
 int sockfd;
 struct sockaddr_in *lsin1, *lsin2;      /* ptr to sockaddr_in in ArgStruct */
 char *host;
 struct hostent *addr;
 struct protoent *proto;		/* protocol entry */
 int send_size, recv_size, sizeofint = sizeof(int);
 struct sigaction sigact1;
#if WANT_DEBUG
 char logfilename[80];
#endif

 /* Sanity check */
 if( p->prot.commtype == NP_COMM_RDMAWRITE && 
     p->prot.comptype != NP_COMP_LOCALPOLL ) {
   fprintf(stderr, "Error, RDMA Write may only be used with local polling.\n");
   fprintf(stderr, "Try using RDMA Write With Immediate Data with vapi polling\n");	/* vapi polling? */
   fprintf(stderr, "or event completion\n");
   exit(-1);
 }
 
 if( p->prot.commtype != NP_COMM_RDMAWRITE && 
     p->prot.comptype == NP_COMP_LOCALPOLL ) {
   fprintf(stderr, "Error, local polling may only be used with RDMA Write.\n");
   fprintf(stderr, "Try using vapi polling or event completion\n");
   exit(-1);
 }

#if WANT_DEBUG
 /* Open log file */
 sprintf(logfilename, ".iblog%d", 1 - p->tr);
 logfile = fopen(logfilename, "w");
#endif

 host = p->host;                           /* copy ptr to hostname */ 

 lsin1 = &(p->prot.sin1);		  /* setup the socket structure #1 */
 lsin2 = &(p->prot.sin2);		 /* setup socket structure #2 */
					/* more setup stuff */
 bzero((char *) lsin1, sizeof(*lsin1));
 bzero((char *) lsin2, sizeof(*lsin2));
					/* tcp checks */
 if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
   printf("NetPIPE: can't open stream socket! errno=%d\n", errno);
   exit(-4);
 }

					/* another tcp check */
 if(!(proto = getprotobyname("tcp"))){
   printf("NetPIPE: protocol 'tcp' unknown!\n");
   exit(555);
 }

 if (p->tr){                                  /* if client i.e., Sender */


   if (atoi(host) > 0) {                   /* Numerical IP address */
     lsin1->sin_family = AF_INET;
     lsin1->sin_addr.s_addr = inet_addr(host);

   } else {
      
     if ((addr = gethostbyname(host)) == NULL){		/* get the hostname */
       printf("NetPIPE: invalid hostname '%s'\n", host);
       exit(-5);
     }

     lsin1->sin_family = addr->h_addrtype;
     bcopy(addr->h_addr, (char*) &(lsin1->sin_addr.s_addr), addr->h_length);
   }

   lsin1->sin_port = htons(p->port);

 } else {                                 /* we are the receiver (server) */

   bzero((char *) lsin1, sizeof(*lsin1));
   lsin1->sin_family      = AF_INET;
   lsin1->sin_addr.s_addr = htonl(INADDR_ANY);
   lsin1->sin_port        = htons(p->port);
  		 
   /* re-use socket, common if netpipe aborts due to busted networks */
   one = 1;
   if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int))) {
       printf("NetPIPE: server: unable to setsockopt -- errno %d\n", errno);
       exit(-7);
   }

   if (bind(sockfd, (struct sockaddr *) lsin1, sizeof(*lsin1)) < 0){
     printf("NetPIPE: server: bind on local address failed! errno=%d\n", errno);
     exit(-6);
   }

 }

 if(p->tr)
   p->commfd = sockfd;
 else
   p->servicefd = sockfd;
/* ********** This is where the IB specific stuff begins ******** */
 

 /* Establish tcp connections */
 /* Connection management for IB is handled over tcp/ip connection */
 establish(p);

 /* Initialize OpenIB -> Mellanox Infiniband */

 if(initIB(p) == -1) {
   CleanUp(p);
   exit(-1);
 }
}   