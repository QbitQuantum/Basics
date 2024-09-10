main() {
pid_t pid;
int e;
char *env[] = { "TERM=xterm", (char *)0 };	
	
	pid=fork();
	if(pid==0){
		execle("/usr/bin/clear","clear", (char *)0,env);
	}
	else{
		wait(&e);
		exit(1);
	}		
}