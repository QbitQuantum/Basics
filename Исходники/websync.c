int
get_results(int count)
{
  int sockfd, n, i, clilen;
  int max = 0;
  int min = 0;
  struct hostent *serverent;
  struct sockaddr_in servaddr, cliaddr;        printf("Getting Results\n\n\n");
       
  results_data = malloc(sizeof(SWAMP_RESULTS));  
  totals = malloc(sizeof(FINAL_RESULTS));
  bzero(totals, sizeof(*totals));  

  clilen = sizeof(cliaddr);
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  bzero( &servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

   
  if(n =  bind(sockfd, (struct sockaddr *)&servaddr,  sizeof(servaddr) ) < 0)
    printf("Error on bind:%d\n", errno);

    for( i=1; i<=count; i++){
  
    n = recvfrom(sockfd, results_data, sizeof(*results_data), 0, (struct sockaddr *)&cliaddr, &clilen);

    serverent = gethostbyaddr(  (char *)&cliaddr.sin_addr, 4, AF_INET );

    printf("Results from: %s\n", (*serverent).h_name  );
    printf(" Bytes:%d\n usecs:%d\n bytes/sec:%d\n pages/sec:%f\n",  ntohl(results_data->filesize), 
             ntohl(results_data->usecs), ntohl(results_data->bpms), 
             (1000*((double)(ntohl(results_data->webpages))/ntohl(results_data->usecs))) ); 
    printf ("Done (webpages %d, inpackets %d, outpackets %d)\n\n", ntohl(results_data->webpages), 
             ntohl(results_data->inpackets), ntohl(results_data->outpackets));
  
    /* Tally final results */  
    totals->filesize   += ntohl(results_data->filesize); 
    totals->usecs      += ntohl(results_data->usecs);
    totals->webpages   += ntohl(results_data->webpages);
    totals->inpackets  += ntohl(results_data->inpackets);
    totals->outpackets += ntohl(results_data->outpackets);
    
    if( i == 1){
      min = ntohl(results_data->usecs);
      max = ntohl(results_data->usecs);
    }
    else{
      if(min > ntohl(results_data->usecs))
         min =  ntohl(results_data->usecs);
      else if(max < ntohl(results_data->usecs))
         max = ntohl(results_data->usecs);
    }
   }
 
    /* Print out combined totals */
    printf("----------------------------------\n TOTALS:\n");
    printf("Total Bytes: %d\n", totals->filesize);
    printf("Mininum usecs: %d\n", min);
    printf("Maximum usecs: %d\n", max);
    printf("Average usces: %d\n", totals->usecs/count);
    printf("Pages/sec (max secs): %f\n", (1000*((double)totals->webpages)/max) );
    printf("Bytes/sec (max secs): %f\n\n",(1000*((double)totals->filesize)/max) );
    printf("Webpages: %d\n", totals->webpages);
    printf("Inpackets: %d\n", totals->inpackets);
    printf("Outpackets: %d\n", totals->outpackets);
	  
 return(0);
}