static long	 
rtcread(Chan *c, void *buf, long n, vlong off)
{
	ulong offset = off;
	ulong t;
	char *b;

	if(c->qid.type & QTDIR)
		return devdirread(c, buf, n, rtcdir, nrtc, devgen);

	switch((ulong)c->qid.path){
	case Qrtc:
		t = m->iomem->rtc;
		n = readnum(offset, buf, n, t, 12);
		return n;
	case Qswitch:
		return readnum(offset, buf, n, archoptionsw(), 12);
	case Qintstat:
		b = malloc(2048);
		if(waserror()){
			free(b);
			nexterror();
		}
		intrstats(b, 2048);
		t = readstr(offset, buf, n, b);
		poperror();
		free(b);
		return t;
	case Qporta:
	case Qportb:
	case Qportc:
		return readport(c->qid.path, offset, buf, n);
	case Qnvram:
		if(offset < 0 || offset >= conf.nvramsize)
			return 0;
		if(offset + n > conf.nvramsize)
			n = conf.nvramsize - offset;
		memmove(buf, (char*)conf.nvrambase+offset, n);
		return n;
	}
	error(Egreg);
	return 0;		/* not reached */
}