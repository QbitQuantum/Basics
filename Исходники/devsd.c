static long
sdwrite(Chan* c, void* a, long n, vlong off)
{
	char *f0;
	int i, atacdb, proto, ataproto;
	uchar *u;
	uvlong end, start;
	Cmdbuf *cb;
	SDifc *ifc;
	SDreq *req;
	SDunit *unit;
	SDev *sdev;

	switch(TYPE(c->qid)){
	default:
		error(Eperm);
	case Qtopctl:
		cb = parsecmd(a, n);
		if(waserror()){
			free(cb);
			nexterror();
		}
		if(cb->nf == 0)
			error("empty control message");
		f0 = cb->f[0];
		cb->f++;
		cb->nf--;
		if(strcmp(f0, "config") == 0){
			/* wormhole into ugly legacy interface */
			legacytopctl(cb);
			poperror();
			free(cb);
			break;
		}
		/*
		 * "ata arg..." invokes sdifc[i]->wtopctl(nil, cb),
		 * where sdifc[i]->name=="ata" and cb contains the args.
		 */
		ifc = nil;
		sdev = nil;
		for(i=0; sdifc[i]; i++){
			if(strcmp(sdifc[i]->name, f0) == 0){
				ifc = sdifc[i];
				sdev = nil;
				goto subtopctl;
			}
		}
		/*
		 * "sd1 arg..." invokes sdifc[i]->wtopctl(sdev, cb),
		 * where sdifc[i] and sdev match controller letter "1",
		 * and cb contains the args.
		 */
		if(f0[0]=='s' && f0[1]=='d' && f0[2] && f0[3] == 0){
			if((sdev = sdgetdev(f0[2])) != nil){
				ifc = sdev->ifc;
				goto subtopctl;
			}
		}
		error("unknown interface");

	subtopctl:
		if(waserror()){
			if(sdev)
				decref(&sdev->r);
			nexterror();
		}
		if(ifc->wtopctl)
			ifc->wtopctl(sdev, cb);
		else
			error(Ebadctl);
		poperror();
		poperror();
		if(sdev)
			decref(&sdev->r);
		free(cb);
		break;

	case Qctl:
		cb = parsecmd(a, n);
		sdev = sdgetdev(DEV(c->qid));
		if(sdev == nil)
			error(Enonexist);
		unit = sdev->unit[UNIT(c->qid)];

		qlock(&unit->ctl);
		if(waserror()){
			qunlock(&unit->ctl);
			decref(&sdev->r);
			free(cb);
			nexterror();
		}
		if(unit->vers != c->qid.vers)
			error(Echange);

		if(cb->nf < 1)
			error(Ebadctl);
		if(strcmp(cb->f[0], "part") == 0){
			if(cb->nf != 4)
				error(Ebadctl);
			if(unit->sectors == 0 && !sdinitpart(unit))
				error(Eio);
			start = strtoull(cb->f[2], 0, 0);
			end = strtoull(cb->f[3], 0, 0);
			sdaddpart(unit, cb->f[1], start, end);
		}
		else if(strcmp(cb->f[0], "delpart") == 0){
			if(cb->nf != 2 || unit->part == nil)
				error(Ebadctl);
			sddelpart(unit, cb->f[1]);
		}
		else if(unit->dev->ifc->wctl)
			unit->dev->ifc->wctl(unit, cb);
		else
			error(Ebadctl);
		qunlock(&unit->ctl);
		decref(&sdev->r);
		poperror();
		free(cb);
		break;

	case Qraw:
		proto = SDcdb;
		ataproto = 0;
		atacdb = 0;
		sdev = sdgetdev(DEV(c->qid));
		if(sdev == nil)
			error(Enonexist);
		unit = sdev->unit[UNIT(c->qid)];
		qlock(&unit->raw);
		if(waserror()){
			qunlock(&unit->raw);
			decref(&sdev->r);
			nexterror();
		}
		switch(unit->state){
		case Rawcmd:
			/* sneaky ata commands */
			u = a;
			if(n > 1 && *u == 0xff){
				proto = SData;
				ataproto = u[1];
				a = u + 2;
				atacdb = Ahdrsz;
				n -= Ahdrsz;
			}		
			if(n < 6 || n > sizeof(req->cmd))
				error(Ebadarg);
			req = smalloc(sizeof(SDreq));
			req->unit = unit;
			if(waserror()){
				free(req);
				nexterror();
			}
			memmove(req->cmd, a, n);
			poperror();
			req->clen = n;
		/*	req->flags = SDnosense;	*/
			req->status = ~0;
			req->proto = proto;
			req->ataproto = ataproto;
			unit->req = req;
			unit->state = Rawdata;
			n += atacdb;
			break;

		case Rawstatus:
			unit->state = Rawcmd;
			free(unit->req);
			unit->req = nil;
			error(Ebadusefd);

		case Rawdata:
			unit->state = Rawstatus;
			req = unit->req;
			req->write = 1;
			n = sdrio(req, a, n);
		}
		poperror();
		qunlock(&unit->raw);
		decref(&sdev->r);
		break;
	case Qpart:
		return sdbio(c, 1, a, n, off);
	case Qextra:
		return extrarw(1, c, a, n, off);
	}

	return n;
}