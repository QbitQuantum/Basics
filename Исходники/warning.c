/*
 *  send mail
 */
int
mail(Fs *f, char *rcvr, char *user, long et)
{
	int pid, i, fd;
	int pfd[2];
	char *ct, *p;
	Waitmsg *w;
	char buf[128];

	if(pipe(pfd) < 0){
		complain("out of pipes: %r");
		return 0;
	}

	switch(pid = fork()){
	case -1:
		complain("can't fork: %r");
		return 0;
	case 0:
		break;
	default:
		if(debug)
			fprint(2, "started %d\n", pid);
		close(pfd[0]);
		ct = ctime(et);
		p = strchr(ct, '\n');
		*p = '.';
		fprint(pfd[1], "User '%s's %s expires on %s\n", user, f->msg, ct);
		if(f != fs)
			fprint(pfd[1], "If you wish to renew contact your local administrator.\n");
		p = strrchr(f->keys, '/');
		if(p)
			p++;
		else
			p = f->keys;
		snprint(buf, sizeof buf, "/adm/warn.%s", p);
		fd = open(buf, OREAD);
		if(fd >= 0){
			while((i = read(fd, buf, sizeof(buf))) > 0)
				write(pfd[1], buf, i);
			close(fd);
		}
		close(pfd[1]);

		/* wait for warning to be mailed */
		for(;;){
			w = wait();
			if(w == nil)
				break;
			if(w->pid == pid){
				if(debug)
					fprint(2, "%d terminated: %s\n", pid, w->msg);
				if(w->msg[0] == 0){
					free(w);
					break;
				}else{
					free(w);
					return 0;
				}
			}else
				free(w);
		}
		return 1;
	}

	/* get out of the current namespace */
	newns("none", 0);

	dup(pfd[0], 0);
	close(pfd[0]);
	close(pfd[1]);
	putenv("upasname", "netkeys");
	if(debug){
		print("\nto %s\n", rcvr);
		execl("/bin/cat", "cat", nil);
	}
	execl("/bin/upas/send", "send", "-r", rcvr, nil);

	/* just in case */
	sysfatal("can't exec send: %r");

	return 0;		/* for compiler */
}