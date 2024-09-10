int main(void)
{
    int lfd,cfd,len,i,cli_len,j;
    int serv_port=SERV_PORT;
    pid_t pid;
    char buf[1024],cli_ip[128];
    struct sockaddr_in ser_addr,cli_addr;

    struct sigaction act;
    act.sa_flags=0;
    act.sa_handler=do_sig;
    sigemptyset(&act.sa_mask);

    sigaction(SIGCHLD,&act,NULL);

    lfd=socket(AF_INET,SOCK_STREAM,0);

    bzero(&ser_addr,sizeof(ser_addr));

    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons((short)serv_port);
    ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    bind(lfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));

    listen(lfd,128);
    j=0;

    while(1){
        cli_len=sizeof(cli_addr);
        cfd=accept(lfd,(struct sockaddr*)&cli_addr,&cli_len);
       if(cfd<0){
           if((errno==ECONNABORTED)||(errno=EINTR)){
               continue;
           }else {
            break;
           }
        } 
        printf("client is connect  %d :%s[%d]\n",j++,inet_ntop(AF_INET,&cli_addr.sin_addr.s_addr,cli_ip,sizeof(cli_ip)),ntohs(cli_addr.sin_port));

        pid=fork();
        if(pid==0){
            close(lfd);
            while(1){
                len=read(cfd,buf,sizeof(buf));
                  if(len<=0){
                  break;
                  }
                write(STDOUT_FILENO,buf,len);
                for(i=0;i<len;i++){
                    buf[i]=toupper(buf[i]);
                }
                write(cfd,buf,len);
            }
            close(cfd);
            exit(1);
        }
        else if(pid>0) {
            close(cfd);
        }
        else {
            perror("fork");
            exit(1);
        }

    }
    close(lfd);
    return 0;
} 