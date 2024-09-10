void 
msg_send(int fsockfd,char *fdest_ip,int fdest_port,char *fmsgbody,int fflag)
{
  socklen_t odrlen;
  struct sockaddr_un	odraddr;
  int i;
  char tempstr[100];
  
  bzero(&odraddr, sizeof(odraddr));	// fill in ODR's address 
  odraddr.sun_family = AF_LOCAL;
  strcpy(odraddr.sun_path, ODR_PATH);
  
  odrlen=sizeof(odraddr);       
 
  strcpy(tempstr,fdest_ip);
  memcpy (tempstr+15,&fdest_port,sizeof(int));
  memset(tempstr+20,2,1);   //Set byte 20 to 2 for msg type = 2
  strcpy(tempstr+21,fmsgbody);
  //strcpy(fmsgbody,tempstr);
  
  printf("\n Dest IP is %s",tempstr); 
  printf("\n Dest Port is %d",*( (int *) (tempstr+15) ) );
  printf("\n Msg type = %d",tempstr[20]);
  printf("\n Timestamp=%s",tempstr+21);
  
 
  Sendto(fsockfd, tempstr, 100, 0, (SA *) &odraddr, odrlen); 
  printf("\n Response sent to ODR service. Waiting for incoming messages...");
  
  
}            