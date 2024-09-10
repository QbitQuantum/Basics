/*
 *  convert a man page to html and output
 */
void
doconvert(char *uri, int vermaj)
{
	char *p;
	char file[256];
	char title[256];
	char err[ERRMAX];
	int pfd[2];
	Dir *d;
	Waitmsg *w;
	int x;

	if(strstr(uri, ".."))
		error("bad URI", "man page URI cannot contain ..");
	p = strstr(uri, "/intro");

	if(p == nil){
		while(*uri == '/')
			uri++;
		/* redirect section requests */
		snprint(file, sizeof(file), "/sys/man/%s", uri);
		d = dirstat(file);
		if(d == nil){
			strlwr(file);
			if(dirstat(file) != nil){
				snprint(file, sizeof(file), "/magic/man2html/%s", uri);
				strlwr(file);
				redirectto(file);
			}
			error(uri, "man page not found");
		}
		x = d->qid.type;
		free(d);
		if(x & QTDIR){
			if(*uri == 0 || strcmp(uri, "/") == 0)
				redirectto("/sys/man/index.html");
			else {
				snprint(file, sizeof(file), "/sys/man/%s/INDEX.html",
					uri+1);
				redirectto(file);
			}
			return;
		}
	} else {
		/* rewrite the name intro */
		*p = 0;
		snprint(file, sizeof(file), "/sys/man/%s/0intro", uri);
		d = dirstat(file);
		free(d);
		if(d == nil)
			error(uri, "man page not found");
	}

	if(vermaj){
		hokheaders(connect);
		hprint(hout, "Content-type: text/html\r\n");
		hprint(hout, "\r\n");
	}
	hflush(hout);

	if(pipe(pfd) < 0)
		error("out of resources", "pipe failed");

	/* troff -manhtml <file> | troff2html -t '' */
	switch(fork()){
	case -1:
		error("out of resources", "fork failed");
	case 0:
		snprint(title, sizeof(title), "Plan 9 %s", file);
		close(0);
		dup(pfd[0], 0);
		close(pfd[0]);
		close(pfd[1]);
		execl("/bin/troff2html", "troff2html", "-t", title, nil);
		errstr(err, sizeof err);
		exits(err);
	}
	switch(fork()){
	case -1:
		error("out of resources", "fork failed");
	case 0:
		snprint(title, sizeof(title), "Plan 9 %s", file);
		close(0);
		close(1);
		dup(pfd[1], 1);
		close(pfd[0]);
		close(pfd[1]);
		execl("/bin/troff", "troff", "-manhtml", file, nil);
		errstr(err, sizeof err);
		exits(err);
	}
	close(pfd[0]);
	close(pfd[1]);

	/* wait for completion */
	for(;;){
		w = wait();
		if(w == nil)
			break;
		if(w->msg[0] != 0)
			print("whoops %s\n", w->msg);
		free(w);
	}
}