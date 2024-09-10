int SndToSock(int sockfd,struct sockaddr_in * addr,char buffer[])
{
        int len = sizeof(struct sockaddr_in);
        sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)addr,len); 
        return 0;
}