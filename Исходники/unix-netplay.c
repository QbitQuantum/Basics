/*
static uint32 de32(uint8 *morp)
{ 
 return(morp[0]|(morp[1]<<8)|(morp[2]<<16)|(morp[3]<<24));
}
*/
int FCEUD_NetworkConnect(void)
{
 struct sockaddr_in sockin;    /* I want to play with fighting robots. */
 struct hostent *phostentb;
 unsigned long hadr;
 int TSocket;
 int netdivisor;
  
 if(!netplayhost) return(0);

 if( (TSocket=socket(AF_INET,SOCK_STREAM,0))==-1)
 {
  puts("Error creating stream socket.");
  FCEUD_NetworkClose();
  return(0);
 }
 int tcpopt = 1;  
 if(setsockopt(TSocket, SOL_TCP, TCP_NODELAY, &tcpopt, sizeof(int)))
  puts("Nodelay fail");

 memset(&sockin,0,sizeof(sockin));
 sockin.sin_family=AF_INET;
 
 hadr=inet_addr(netplayhost);
 
 if(hadr!=INADDR_NONE)
  sockin.sin_addr.s_addr=hadr;
 else
 {
  puts("*** Looking up host name...");
  if(!(phostentb=gethostbyname((const char *)netplayhost)))
  {
   puts("Error getting host network information.");
   close(TSocket);
   FCEUD_NetworkClose();
   return(0);
  }
  memcpy(&sockin.sin_addr,phostentb->h_addr,phostentb->h_length);
 }
 
 sockin.sin_port=htons(tport);
 puts("*** Connecting to remote host...");
 if(connect(TSocket,(struct sockaddr *)&sockin,sizeof(sockin))==-1)
 {
   puts("Error connecting to remote host.");
   close(TSocket);
   FCEUD_NetworkClose();
  return(0);
 }
 Socket=TSocket;
 puts("*** Sending initialization data to server...");
 {
  uint8 *sendbuf;
  uint8 buf[5];
  uint32 sblen;

   sblen = 4 + 16 + 16 + 64 + 1 + (netplaynick?strlen(netplaynick):0);
   sendbuf = malloc(sblen);
   memset(sendbuf, 0, sblen);
                           
   en32(sendbuf, sblen - 4);
                           
   if(netgamekey)
   {
    struct md5_context md5;
    uint8 md5out[16];

    md5_starts(&md5);
    md5_update(&md5, CurGame->MD5, 16);
    md5_update(&md5, netgamekey, strlen(netgamekey));
    md5_finish(&md5, md5out);
    memcpy(sendbuf + 4, md5out, 16);
   }
   else
    memcpy(sendbuf + 4, CurGame->MD5, 16);

   if(netpassword)
   {
    struct md5_context md5;
    uint8 md5out[16];
   
    md5_starts(&md5);
    md5_update(&md5, netpassword, strlen(netpassword));
    md5_finish(&md5, md5out);
    memcpy(sendbuf + 4 + 16, md5out, 16);
   }
                        
   memset(sendbuf + 4 + 16 + 16, 0, 64);

   sendbuf[4 + 16 + 16 + 64] = netlocalplayers;

   if(netplaynick)
    memcpy(sendbuf + 4 + 16 + 16 + 64 + 1,netplaynick,strlen(netplaynick));

  send(Socket, sendbuf, sblen, 0);
  free(sendbuf);

  recv(Socket, buf, 1, MSG_WAITALL);
  netdivisor = buf[0];
 }

 puts("*** Connection established.");

 FCEUDnetplay = 1;
 FCEUI_NetplayStart(netlocalplayers, netdivisor);
 return(1);
}