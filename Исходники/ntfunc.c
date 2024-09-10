int nt_try_fast_exec(struct command *t) {
	register Char  **pv, **av;
	register Char *dp,*sav;
	register char **tt;
	register char *f;
	register struct varent *v;
	register int hashval,i;
	register int slash;
	int rc = 0, gflag;
	Char *vp;
	Char   *blk[2];

	vp = varval(STRNTslowexec);
	if (vp != STRNULL)
		return 1;

	blk[0] = t->t_dcom[0];
	blk[1] = 0;

	// don't do backtick
	if(Strchr(t->t_dcom[0],'`') )
		return 1;


	gflag = tglob(blk);
	if (gflag) {
		pv = globall(blk, gflag);
		if (pv == 0) {
			return 1;
		}
	}
	else
		pv = saveblk(blk);

	trim(pv);

	epath = Strsave(pv[0]);
	v = adrof(STRpath);
	if (v == 0 && epath[0] != '/' && epath[0] != '.') {
		blkfree(pv);
		return 1;
	}
	slash = any(short2str(epath),'/');
	/*
	 * Glob the argument list, if necessary. Otherwise trim off the quote bits.
	 */
	av = &t->t_dcom[1];
	gflag = tglob(av);
	if (gflag) {
		av = globall(av, gflag);/*FIXRESET*/
		if (av == 0) {
			blkfree(pv);
			return 1;
		}
	}
	else
		av = saveblk(av);

	blkfree(t->t_dcom);
	t->t_dcom = blkspl(pv, av);
	xfree((ptr_t) pv);
	xfree((ptr_t) av);
	av = t->t_dcom;
	//trim(av);

	if (*av == NULL || **av == '\0')
		return 1;

	xechoit(av);/*FIXRESET*/		/* Echo command if -x */
	if (v == 0 || v->vec[0] == 0 || slash)
		pv = abspath;
	else
		pv = v->vec;

	sav = Strspl(STRslash,*av);
	hashval = hashval_extern(*av);

	i = 0;
	do {
#pragma warning(disable:4310)
		if (!slash && ABSOLUTEP(pv[0]) && havhash) {
#pragma warning(default:4310)
			if (!bit_extern(hashval,i)){
				pv++;i++;
				continue;
			}
		}
		if (pv[0][0] == 0 || eq(pv[0],STRdot)) {

			tt = short2blk(av);
			f = short2str(*av);

			rc = nt_texec(f, tt);

			blkfree((Char**)tt);
			if (!rc)
				break;
		}
		else {
			dp = Strspl(*pv,sav);
			tt = short2blk(av);
			f = short2str(dp);

			rc = nt_texec(f, tt);

			blkfree((Char**)tt);
			xfree((ptr_t)dp);
			if (!rc)
				break;
		}
		pv++;
		i++;
	}while(*pv);
	return rc;
}