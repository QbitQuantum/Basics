static long
mousewrite(Chan *c, void *va, long n, vlong offset)
{
	char *p;
	Point pt;
	Cmdbuf *cb;
	Cmdtab *ct;
	char buf[64];
	int nn;

	p = va;
	switch((ulong)c->qid.path){
	case Qdir:
		error(Eisdir);

	case Qcursor:
		if(n < 2*4+2*2*16){
			curs = arrow;
			Cursortocursor(&arrow);
		}else{
			n = 2*4+2*2*16;
			curs.offset.x = BGLONG(p+0);
			curs.offset.y = BGLONG(p+4);
			memmove(curs.clr, p+8, 2*16);
			memmove(curs.set, p+40, 2*16);
			Cursortocursor(&curs);
		}
		qlock(&mouse.qlk);
		mouse.redraw = 1;
		qunlock(&mouse.qlk);
		return n;

	case Qmousectl:
		cb = parsecmd(va, n);
		if(waserror()){
			free(cb);
			nexterror();
		}

		ct = lookupcmd(cb, mousectlmsg, nelem(mousectlmsg));

		switch(ct->index){
		case CMswap:
			if(mouseswap)
				setbuttonmap("123");
			else
				setbuttonmap("321");
			mouseswap ^= 1;
			break;

		case CMscrollswap:
			scrollswap ^= 1;
			break;

		case CMbuttonmap:
			if(cb->nf == 1)
				setbuttonmap("123");
			else
				setbuttonmap(cb->f[1]);
			break;
		}

		free(cb);
		poperror();
		return n;

	case Qmouse:
		if(n > sizeof buf-1)
			n = sizeof buf -1;
		memmove(buf, va, n);
		buf[n] = 0;
		p = 0;
		pt.x = strtoul(buf+1, &p, 0);
		if(p == 0)
			error(Eshort);
		pt.y = strtoul(p, 0, 0);
		qlock(&mouse.qlk);
		if(ptinrect(pt, mouserect)){
			mouse.mstate.xy = pt;
			mouse.redraw = 1;
			mouse.track = 1;
		}
		qunlock(&mouse.qlk);
		setmouse(pt);
		return n;
	
	case Qsnarf:
		if(offset+n >= SnarfSize)
			error("too much snarf");
		if(n == 0)
			return 0;
		assert(mousedir[Qsnarf].qid.path == Qsnarf);
		mousedir[Qsnarf].qid.vers++;
		if(c->aux == nil)
			nn = 0;
		else
			nn = strlen(c->aux);
		if(offset+n > nn){
			nn = offset+n;
			p = smalloc(nn+1);
			if(c->aux){
				strcpy(p, c->aux);
				free(c->aux);
			}
			c->aux = p;
		}
		memmove(c->aux+offset, va, n);
		return n;
	}

	error(Egreg);
	return -1;
}