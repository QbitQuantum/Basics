int fork()
{
	PROC *p;  int i, child, pid;  u16 segment;

	pid = kfork(0);   // kfork() but do NOT load any Umode image for child
	if (pid < 0){     // kfork failed
		return -1;
	}
	p = &proc[pid];   // we can do this because of static pid

	for (i=0; i<NFD; i++){
		p->fd[i] = running->fd[i];

		if (p->fd[i] != 0){
			p->fd[i]->refCount++;

			if (p->fd[i]->mode == READ_PIPE)
				p->fd[i]->pipe_ptr->nreader++;

			if (p->fd[i]->mode == WRITE_PIPE){
				p->fd[i]->pipe_ptr->nwriter++;
			}
		}
	}

	segment = (pid+1)*0x2000;
	copyImage(running->uss, segment, 32*1024);
	p->uss = segment;
	p->usp = 0x2000 - 24;

	// YOUR CODE to make the child runnable in User mode
	p->kstack[SSIZE -1] =(int)goUmode;
	/**** ADD these : copy file descriptors ****/

	// clean the registers and set flag and uCs and uDs to runnings values
	for (i = 1; i < 13; i++) {
		child = 0x2000 - i*2;
		switch(i){
			case 1: put_word(segment, segment, child); break;
			case 2: put_word(segment, segment, child); break;
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10: put_word(0,segment, child); break;
			case 11:
			case 12: put_word(segment, segment, child); break;
		}
	}

	return(p->pid);
}