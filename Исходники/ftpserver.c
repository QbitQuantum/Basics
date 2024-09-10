/* CHILD PROCEDURE, WHICH ACTUALLY DOES THE FILE TRANSFER */
doftp(int newsd)
  {
        
    int i,fsize,fd,msg_ok,fail,fail1,req,c,ack;
    int no_read ,num_blks , num_blks1,num_last_blk,num_last_blk1,tmp;
    char fname[MAXLINE];
    char out_buf[MAXSIZE];
    FILE *fp;
       
     no_read = 0;
     num_blks = 0;
     num_last_blk = 0; 
 
     
     /* START SERVICING THE CLIENT */
   
     /* get command code from client.*/
     /* only one supported command: 100 -  get a file */
     req = 0;
     if((readn(newsd,(char *)&req,sizeof(req))) < 0)
 {
printf("server: read error %d\n",errno);exit(0);
}
     req = ntohs(req);
     printf("server: client request code is: %d\n",req);
     if (req!=REQUESTFILE) {
 
 printf("server: unsupported operation. goodbye\n");
         /* reply to client: command not OK  (code: 150) */
         msg_ok = COMMANDNOTSUPPORTED; 
         msg_ok = htons(msg_ok);
         if((writen(newsd,(char *)&msg_ok,sizeof(msg_ok))) < 0)
            {
printf("server: write error :%d\n",errno);exit(0);
}
         exit(0);
          
}
 
     /* reply to client: command OK  (code: 160) */
     msg_ok = COMMANDSUPPORTED; 
     msg_ok = htons(msg_ok);
     if((writen(newsd,(char *)&msg_ok,sizeof(msg_ok))) < 0)
             {
printf("server: write error :%d\n",errno);exit(0);
}
   
    fail = FILENAMEOK;
    if((read(newsd,fname,MAXLINE)) < 0) {
 
        printf("server: filename read error :%d\n",errno);
        fail = BADFILENAME ;
         
}
    
     /* IF SERVER CANT OPEN FILE THEN INFORM CLIENT OF THIS AND TERMINATE */
     if((fp = fopen(fname,"r")) == NULL) /*cant open file*/
        fail = BADFILENAME;
 
     tmp = htons(fail);
     if((writen(newsd,(char *)&tmp,sizeof(tmp))) < 0)
        {
printf("server: write error :%d\n",errno);exit(0);   
}
     if(fail == BADFILENAME) {
printf("server cant open file\n");
                            close(newsd);exit(0);
}
     printf("server: filename is %s\n",fname);
   
    req = 0;
    if ((readn(newsd,(char *)&req,sizeof(req))) < 0)
             {
printf("server: read error :%d\n",errno);exit(0);
}
    printf("server: start transfer command, %d, received\n", ntohs(req));
 
    
   /*SERVER GETS FILESIZE AND CALCULATES THE NUMBER OF BLOCKS OF 
     SIZE = MAXSIZE IT WILL TAKE TO TRANSFER THE FILE. ALSO CALCULATE
     NUMBER OF BYTES IN THE LAST PARTIALLY FILLED BLOCK IF ANY. 
     SEND THIS INFO TO CLIENT, RECEIVING ACKS */
    printf("server: starting transfer\n");
    fsize = 0;ack = 0;   
    while ((c = getc(fp)) != EOF) {
fsize++;
}
    num_blks = fsize / MAXSIZE; 
    num_blks1 = htons(num_blks);
    num_last_blk = fsize % MAXSIZE; 
    num_last_blk1 = htons(num_last_blk);
    if((writen(newsd,(char *)&num_blks1,sizeof(num_blks1))) < 0)
             {
printf("server: write error :%d\n",errno);exit(0);
}
    printf("server: told client there are %d blocks\n", num_blks);  
    if((readn(newsd,(char *)&ack,sizeof(ack))) < 0)
        {
printf("server: ack read error :%d\n",errno);exit(0); 
}          
    if (ntohs(ack) != ACK) {
 
      printf("client: ACK not received on file size\n");
      exit(0);
       
}
    if((writen(newsd,(char *)&num_last_blk1,sizeof(num_last_blk1))) < 0)
       {
printf("server: write error :%d\n",errno);exit(0);
}
    printf("server: told client %d bytes in last block\n", num_last_blk);  
    if((readn(newsd,(char *)&ack,sizeof(ack))) < 0)
        {
printf("server: ack read error :%d\n",errno);exit(0); 
}
    if (ntohs(ack) != ACK) {
 
      printf("server: ACK not received on file size\n");
      exit(0);
       
}
    rewind(fp);    
     
   
    /* ACTUAL FILE TRANSFER STARTS  BLOCK BY BLOCK*/      
        
   
  for(i= 0; i < num_blks; i ++) {
  
      no_read = fread(out_buf,sizeof(char),MAXSIZE,fp);
      if (no_read == 0) {
printf("server: file read error\n");exit(0);
}
      if (no_read != MAXSIZE)
              {
printf("server: file read error : no_read is less\n");exit(0);
}
      if((writen(newsd,out_buf,MAXSIZE)) < 0)
                 {
printf("server: error sending block:%d\n",errno);exit(0);
}
      if((readn(newsd,(char *)&ack,sizeof(ack))) < 0)
                 {
printf("server: ack read  error :%d\n",errno);exit(0);
}
      if (ntohs(ack) != ACK) {
 
          printf("server: ACK not received for block %d\n",i);
          exit(0);
           
}
      printf(" %d...",i);
       
}
 
   if (num_last_blk > 0) {
  
      printf("%d\n",num_blks);
      no_read = fread(out_buf,sizeof(char),num_last_blk,fp); 
      if (no_read == 0) {
printf("server: file read error\n");exit(0);
}
      if (no_read != num_last_blk) 
            {
printf("server: file read error : no_read is less 2\n");exit(0);
}
      if((writen(newsd,out_buf,num_last_blk)) < 0)
                 {
printf("server: file transfer error %d\n",errno);exit(0);
}
      if((readn(newsd,(char *)&ack,sizeof(ack))) < 0)
         {
printf("server: ack read  error %d\n",errno);exit(0);
}
      if (ntohs(ack) != ACK) {
 
          printf("server: ACK not received last block\n");
          exit(0);
           
}
       
}
    else printf("\n");
                                                   
   /* FILE TRANSFER ENDS */
   printf("server: FILE TRANSFER COMPLETE on socket %d\n",newsd);
   fclose(fp);
   close(newsd);
   
}