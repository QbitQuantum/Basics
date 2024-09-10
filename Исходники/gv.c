GV *
Perl_gv_fetchpv(pTHX_ const char *nambeg, I32 add, I32 sv_type)
{
    register const char *name = nambeg;
    register GV *gv = 0;
    GV**gvp;
    I32 len;
    register const char *namend;
    HV *stash = 0;

    if (*name == '*' && isALPHA(name[1])) /* accidental stringify on a GV? */
	name++;

    for (namend = name; *namend; namend++) {
	if ((*namend == ':' && namend[1] == ':')
	    || (*namend == '\'' && namend[1]))
	{
	    if (!stash)
		stash = PL_defstash;
	    if (!stash || !SvREFCNT(stash)) /* symbol table under destruction */
		return Nullgv;

	    len = namend - name;
	    if (len > 0) {
		char smallbuf[256];
		char *tmpbuf;

		if (len + 3 < sizeof smallbuf)
		    tmpbuf = smallbuf;
		else
		    New(601, tmpbuf, len+3, char);
		Copy(name, tmpbuf, len, char);
		tmpbuf[len++] = ':';
		tmpbuf[len++] = ':';
		tmpbuf[len] = '\0';
		gvp = (GV**)hv_fetch(stash,tmpbuf,len,add);
		gv = gvp ? *gvp : Nullgv;
		if (gv && gv != (GV*)&PL_sv_undef) {
		    if (SvTYPE(gv) != SVt_PVGV)
			gv_init(gv, stash, tmpbuf, len, (add & GV_ADDMULTI));
		    else
			GvMULTI_on(gv);
		}
		if (tmpbuf != smallbuf)
		    Safefree(tmpbuf);
		if (!gv || gv == (GV*)&PL_sv_undef)
		    return Nullgv;

		if (!(stash = GvHV(gv)))
		    stash = GvHV(gv) = newHV();

		if (!HvNAME(stash))
		    HvNAME(stash) = savepvn(nambeg, namend - nambeg);
	    }

	    if (*namend == ':')
		namend++;
	    namend++;
	    name = namend;
	    if (!*name)
		return gv ? gv : (GV*)*hv_fetch(PL_defstash, "main::", 6, TRUE);
	}
    }