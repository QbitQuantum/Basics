// Parameters are taken from EV_SET (see kevent(2))
static int
enqueue_kqueue_change(poller *p,uintptr_t ident,short filter,u_short flags,
			u_int fflags,intptr_t data,void *udata){
	// This unlikely event could occur if, for instance, every fd is being
	// used, and on the last sysdep_poll() every one had event changes,
	// and then a verdict was injected while the poller was blocked.... or
	// (far more likely) in the case of programming error, heheh
	if(p->kchanges >= p->csize){
		typeof(p->csize) tmpcsize = p->csize * 2;
		typeof(*p->cv) *tmpcv;

		// If we've not yet been initialized, or reset, don't start
		// growing buffers...that's a serious problem. Should this be
		// changed, insert a p->csize check around the Kevent() failure
		// case involving vector dump and reuse of implied first slot!
		if(p->csize == 0){
			bitch("Used with uninitialized poller\n");
			return -1;
		}
		if((tmpcv = Realloc("kchange vector",p->cv,sizeof(*tmpcv) * tmpcsize)) == NULL){
			// If the realloc failed, dump the current vector...
			if(Kevent(p->kq,p->cv,p->kchanges,NULL,0,NULL)){
				inc_stateexceptions();
				return -1;
			}
			// Reinitialize the buffer. We're assured that there's
			// room for at least one of us now by p->csize check
			p->kchanges = 0;
		}else{
			p->cv = tmpcv;
			p->csize = tmpcsize;
		}
	}
	EV_SET(&p->cv[p->kchanges++],ident,filter,flags,fflags,data,udata);
	return 0;
}