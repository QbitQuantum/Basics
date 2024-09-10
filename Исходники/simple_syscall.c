int sys_getpid(int *retval){
	pid_t pid;
	pid=getPid();
	*retval=(int)pid;
	//kprintf("\n in sys_getpid fun::%d",pid);
	/*if(syscall is successfull){
		return 0;
	}
	return -1; */
	return pid;
}