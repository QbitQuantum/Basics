static int
readprocfdinit(void)
{
	/* construct info from /proc/$pid/fd */
	char buf[8192];
	Fdinfo *fi;
	int fd, pfd, pid, n, tot, m;
	char *s, *nexts;

	memset(buf, 0, sizeof buf);
	pfd = _OPEN("#c/pid", 0);
	if(pfd < 0)
		return -1;
	if(_PREAD(pfd, buf, 100, 0) < 0){
		_CLOSE(pfd);
		return -1;
	}
	_CLOSE(pfd);
	pid = strtoul(buf, 0, 10);
	strcpy(buf, "#p/");
	_ultoa(buf+3, pid);
	strcat(buf, "/fd");
	pfd = _OPEN(buf, 0);
	if(pfd < 0)
		return -1;
	memset(buf, 0, sizeof buf);
	tot = 0;
	for(;;){
		n = _PREAD(pfd, buf+tot, sizeof buf-tot, tot);
		if(n <= 0)
			break;
		tot += n;
	}
	_CLOSE(pfd);
	if(n < 0)
		return -1;
	buf[sizeof buf-1] = '\0';
	s = strchr(buf, '\n');	/* skip current directory */
	if(s == 0)
		return -1;
	s++;
	m = 0;
	for(; s && *s; s=nexts){
		nexts = strchr(s, '\n');
		if(nexts)
			*nexts++ = '\0';
		errno = 0;
		fd = strtoul(s, &s, 10);
		if(errno != 0)
			return -1;
		if(fd >= OPEN_MAX)
			continue;
		if(fd == pfd)
			continue;
		fi = &_fdinfo[fd];
		fi->flags = FD_ISOPEN;
		while(*s == ' ' || *s == '\t')
			s++;
		if(*s == 'r'){
			m |= 1;
			s++;
		}
		if(*s == 'w'){
			m |= 2;
		}
		if(m==1)
			fi->oflags = O_RDONLY;
		else if(m==2)
			fi->oflags = O_WRONLY;
		else
			fi->oflags = O_RDWR;
		if(strlen(s) >= 9 && strcmp(s+strlen(s)-9, "/dev/cons") == 0)
			fi->flags |= FD_ISTTY;
	}
	return 0;
}