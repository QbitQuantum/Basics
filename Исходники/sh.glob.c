static void
expbrace(Char ***nvp, Char ***elp, int size)
{
    Char **vl, **el, **nv, *s;

    vl = nv = *nvp;
    if (elp != NULL)
	el = *elp;
    else
	el = vl + blklen(vl);

    for (s = *vl; s; s = *++vl) {
	Char  **vp, **bp;

	/* leave {} untouched for find */
	if (s[0] == '{' && (s[1] == '\0' || (s[1] == '}' && s[2] == '\0')))
	    continue;
	if (Strchr(s, '{') != NULL) {
	    Char  **bl = NULL;
	    int     len;

	    if ((len = globbrace(s, &bl)) < 0)
		stderror(ERR_MISSING, -len);
	    xfree(s);
	    if (len == 1) {
		*vl-- = *bl;
		xfree(bl);
		continue;
	    }
	    if (&el[len] >= &nv[size]) {
		size_t l, e;
		l = &el[len] - &nv[size];
		size += GLOBSPACE > l ? GLOBSPACE : l;
		l = vl - nv;
		e = el - nv;
		nv = xrealloc(nv, size * sizeof(Char *));
		*nvp = nv; /* To keep cleanups working */
		vl = nv + l;
		el = nv + e;
	    }
	    /* nv vl   el     bl
	     * |  |    |      |
	     * -.--..--	      x--
	     *   |            len
	     *   vp
	     */
	    vp = vl--;
	    *vp = *bl;
	    len--;
	    for (bp = el; bp != vp; bp--)
		bp[len] = *bp;
	    el += len;
	    /* nv vl    el bl
	     * |  |     |  |
	     * -.-x  ---    --
	     *   |len
	     *   vp
	     */
	    vp++;
	    for (bp = bl + 1; *bp; *vp++ = *bp++)
		continue;
	    xfree(bl);
	}

    }
    if (elp != NULL)
	*elp = el;
}