static void
cecrdr(void *vp)
{
	Proc *up = externup();
	Block *bp;
	Conn *cp;
	If *ifc;
	Pkt *p;

	ifc = vp;
	if(waserror())
		goto exit;

	discover(ifc, 0);
	for(;;){
		bp = ifc->d->bread(ifc->dc, 1514, 0); // do we care about making the MTU non magic?
		if(bp == nil)
			nexterror();
		p = (Pkt *)bp->rp;
		if(p->etype[0] != 0xbc || p->etype[1] != 0xbc){
			freeb(bp);
			continue;
		}
		trace(bp);
		cp = findconn(p->src, p->conn);
		if(cp == nil){
			cecprint("cec: out of connection structures\n");
			freeb(bp);
			continue;
		}
		if (waserror()){
			freeb(bp);
			qunlock(cp);
			continue;
		}
		switch(p->type){
		case Tinita:
			if(cp->bp){
				cecprint("cec: reset with bp!? ask quanstro\n");
				freeb(cp->bp);
				cp->bp = 0;
			}
			inita(cp, ifc, p);
			break;
		case Tinitb:
			cecprint("cec: unexpected initb\n");
			break;
		case Tinitc:
			if(cp->state == Cinitb){
				ack(cp);
				if(cp->passwd[0]){
					cp->state = Clogin;
					conputs(cp, "password: "******"cec: unexpected offer\n"); from ourselves.
			break;
		case Treset:
			if(cp->bp)
				freeb(cp->bp);
			cp->bp = 0;
			cp->state = Cunused;
			break;
		default:
			cecprint("bad cec type: %d\n", p->type);
			break;
		}
		nexterror();
	}

exit:
	for(cp = conn; cp < conn+nelem(conn); cp++)
		if(cp->ifc == ifc){
			if(cp->bp)
				freeb(cp->bp);
			memset(cp, 0, sizeof *cp);
			break;
		}

	memset(ifc, 0, sizeof *ifc);
	pexit("cec exiting", 1);
}