//************************************************************************************
//
// Socket Transmit to Socket
//
//************************************************************************************
void transmitdata(LPVOID data)
{
     SOCKET fd1, fd2;
     transocket *sock;
     struct timeval timeset;
     fd_set readfd,writefd;
     int result,i=0;
     char read_in1[MAXSIZE],send_out1[MAXSIZE];
     char read_in2[MAXSIZE],send_out2[MAXSIZE];
     int read1=0,totalread1=0,send1=0;
     int read2=0,totalread2=0,send2=0;
     int sendcount1,sendcount2;
     int maxfd;
     struct sockaddr_in client1,client2;
     int structsize1,structsize2;
     char host1[20],host2[20];
     int port1=0,port2=0;
     char tmpbuf[100];

     sock = (transocket *)data;
     fd1 = sock->fd1;
     fd2 = sock->fd2;

     memset(host1,0,20);
     memset(host2,0,20);
     memset(tmpbuf,0,100);

     structsize1=sizeof(struct sockaddr);
     structsize2=sizeof(struct sockaddr);
     
     if(getpeername(fd1,(struct sockaddr *)&client1,&structsize1)<0)
     {
           strcpy(host1, "fd1");
     }
     else
     {      
//            printf("[+]got, ip:%s, port:%d\r\n",inet_ntoa(client1.sin_addr),ntohs(client1.sin_port));
           strcpy(host1, inet_ntoa(client1.sin_addr));
           port1=ntohs(client1.sin_port);
     }

     if(getpeername(fd2,(struct sockaddr *)&client2,&structsize2)<0)
     {
           strcpy(host2,"fd2");
     }
     else
     {      
//            printf("[+]got, ip:%s, port:%d\r\n",inet_ntoa(client2.sin_addr),ntohs(client2.sin_port));
           strcpy(host2, inet_ntoa(client2.sin_addr));
           port2=ntohs(client2.sin_port);
     }

     printf("[+] Start Transmit (%s:%d <-> %s:%d) ......\r\n\n", host1, port1, host2, port2);
 
     maxfd=max(fd1,fd2)+1;
     memset(read_in1,0,MAXSIZE);
     memset(read_in2,0,MAXSIZE);
     memset(send_out1,0,MAXSIZE);
     memset(send_out2,0,MAXSIZE);
 
     timeset.tv_sec=TIMEOUT;
     timeset.tv_usec=0;

     while(1)
     {
           FD_ZERO(&readfd);
           FD_ZERO(&writefd);
       
           FD_SET((UINT)fd1, &readfd);
           FD_SET((UINT)fd1, &writefd);
           FD_SET((UINT)fd2, &writefd);
           FD_SET((UINT)fd2, &readfd);
       
           result=select(maxfd,&readfd,&writefd,NULL,&timeset);
           if((result<0) && (errno!=EINTR))
           {
                 printf("[-] Select error.\r\n");
                 break;
           }
           else if(result==0)
           {
                 printf("[-] Socket time out.\r\n");
                 break;
           }
           
           if(FD_ISSET(fd1, &readfd))
           {
                 /* must < MAXSIZE-totalread1, otherwise send_out1 will flow */
                 if(totalread1<MAXSIZE)
               {
                       read1=recv(fd1, read_in1, MAXSIZE-totalread1, 0);
                       if((read1==SOCKET_ERROR) || (read1==0))
                       {
                             printf("[-] Read fd1 data error,maybe close?\r\n");
                             break;
                       }
                 
                       memcpy(send_out1+totalread1,read_in1,read1);
                       sprintf(tmpbuf,"\r\nRecv %5d bytes from %s:%d\r\n", read1, host1, port1);
                       printf(" Recv %5d bytes %16s:%d\r\n", read1, host1, port1);
                       makelog(tmpbuf,strlen(tmpbuf));
                       makelog(read_in1,read1);
                       totalread1+=read1;
                       memset(read_in1,0,MAXSIZE);
                 }
           }

           if(FD_ISSET(fd2, &writefd))
           {
                 int err=0;
                 sendcount1=0;
                 while(totalread1>0)
                 {
                       send1=send(fd2, send_out1+sendcount1, totalread1, 0);
                       if(send1==0)break;
                       if((send1<0) && (errno!=EINTR))
                       {
                             printf("[-] Send to fd2 unknow error.\r\n");
                             err=1;
                             break;
                       }
                       
                       if((send1<0) && (errno==ENOSPC)) break;
                       sendcount1+=send1;
                       totalread1-=send1;

                       printf(" Send %5d bytes %16s:%d\r\n", send1, host2, port2);
                 }
               
                 if(err==1) break;
                 if((totalread1>0) && (sendcount1>0))
                 {
                       /* move not sended data to start addr */
                       memcpy(send_out1,send_out1+sendcount1,totalread1);
                       memset(send_out1+totalread1,0,MAXSIZE-totalread1);
                 }
                 else
                 memset(send_out1,0,MAXSIZE);
           }
           
           if(FD_ISSET(fd2, &readfd))
           {
                 if(totalread2<MAXSIZE)
                 {
                       read2=recv(fd2,read_in2,MAXSIZE-totalread2, 0);
                       if(read2==0)break;
                       if((read2<0) && (errno!=EINTR))
                       {
                             printf("[-] Read fd2 data error,maybe close?\r\n\r\n");
                             break;
                       }

                       memcpy(send_out2+totalread2,read_in2,read2);
                       sprintf(tmpbuf, "\r\nRecv %5d bytes from %s:%d\r\n", read2, host2, port2);
                       printf(" Recv %5d bytes %16s:%d\r\n", read2, host2, port2);
                       makelog(tmpbuf,strlen(tmpbuf));
                 makelog(read_in2,read2);
                 totalread2+=read2;
                 memset(read_in2,0,MAXSIZE);
                 }
           }

           if(FD_ISSET(fd1, &writefd))
           {
                 int err2=0;
               sendcount2=0;
               while(totalread2>0)
               {
                     send2=send(fd1, send_out2+sendcount2, totalread2, 0);
                     if(send2==0)break;
                     if((send2<0) && (errno!=EINTR))
                     {
                           printf("[-] Send to fd1 unknow error.\r\n");
                             err2=1;
                           break;
                     }
                     if((send2<0) && (errno==ENOSPC)) break;
                     sendcount2+=send2;
                     totalread2-=send2;
                       
                       printf(" Send %5d bytes %16s:%d\r\n", send2, host1, port1);
               }
                 if(err2==1) break;
             if((totalread2>0) && (sendcount2 > 0))
                 {
                       /* move not sended data to start addr */
                       memcpy(send_out2, send_out2+sendcount2, totalread2);
                       memset(send_out2+totalread2, 0, MAXSIZE-totalread2);
                 }
                 else
                       memset(send_out2,0,MAXSIZE);
           }

           Sleep(5);
     }
 
     closesocket(fd1);
     closesocket(fd2);
//      if(method == 3)
//            connectnum --;
     
     printf("\r\n[+] OK! I Closed The Two Socket.\r\n");
}