/*
 * fword --
 *	Move forward by words.
 */
static int
fword(SCR *sp, VICMD *vp, enum which type)
{
	enum { INWORD, NOTWORD } state;
	VCS cs;
	u_long cnt;

	cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1;
	cs.cs_lno = vp->m_start.lno;
	cs.cs_cno = vp->m_start.cno;
	if (cs_init(sp, &cs))
		return (1);

	/*
	 * If in white-space:
	 *	If the count is 1, and it's a change command, we're done.
	 *	Else, move to the first non-white-space character, which
	 *	counts as a single word move.  If it's a motion command,
	 *	don't move off the end of the line.
	 */
	if (cs.cs_flags == CS_EMP || (cs.cs_flags == 0 && ISBLANK(cs.cs_ch))) {
		if (ISMOTION(vp) && cs.cs_flags != CS_EMP && cnt == 1) {
			if (ISCMD(vp->rkp, 'c'))
				return (0);
			if (ISCMD(vp->rkp, 'd') || ISCMD(vp->rkp, 'y')) {
				if (cs_fspace(sp, &cs))
					return (1);
				goto ret;
			}
		}
		if (cs_fblank(sp, &cs))
			return (1);
		--cnt;
	}

	/*
	 * Cyclically move to the next word -- this involves skipping
	 * over word characters and then any trailing non-word characters.
	 * Note, for the 'w' command, the definition of a word keeps
	 * switching.
	 */
	if (type == BIGWORD)
		while (cnt--) {
			for (;;) {
				if (cs_next(sp, &cs))
					return (1);
				if (cs.cs_flags == CS_EOF)
					goto ret;
				if (cs.cs_flags != 0 || ISBLANK(cs.cs_ch))
					break;
			}
			/*
			 * If a motion command and we're at the end of the
			 * last word, we're done.  Delete and yank eat any
			 * trailing blanks, but we don't move off the end
			 * of the line regardless.
			 */
			if (cnt == 0 && ISMOTION(vp)) {
				if ((ISCMD(vp->rkp, 'd') ||
				    ISCMD(vp->rkp, 'y')) &&
				    cs_fspace(sp, &cs))
					return (1);
				break;
			}

			/* Eat whitespace characters. */
			if (cs_fblank(sp, &cs))
				return (1);
			if (cs.cs_flags == CS_EOF)
				goto ret;
		}
	else
		while (cnt--) {
			state = cs.cs_flags == 0 &&
			    inword(cs.cs_ch) ? INWORD : NOTWORD;
			for (;;) {
				if (cs_next(sp, &cs))
					return (1);
				if (cs.cs_flags == CS_EOF)
					goto ret;
				if (cs.cs_flags != 0 || ISBLANK(cs.cs_ch))
					break;
				if (state == INWORD) {
					if (!inword(cs.cs_ch))
						break;
				} else
					if (inword(cs.cs_ch))
						break;
			}
			/* See comment above. */
			if (cnt == 0 && ISMOTION(vp)) {
				if ((ISCMD(vp->rkp, 'd') ||
				    ISCMD(vp->rkp, 'y')) &&
				    cs_fspace(sp, &cs))
					return (1);
				break;
			}

			/* Eat whitespace characters. */
			if (cs.cs_flags != 0 || ISBLANK(cs.cs_ch))
				if (cs_fblank(sp, &cs))
					return (1);
			if (cs.cs_flags == CS_EOF)
				goto ret;
		}

	/*
	 * If we didn't move, we must be at EOF.
	 *
	 * !!!
	 * That's okay for motion commands, however.
	 */
ret:	if (!ISMOTION(vp) &&
	    cs.cs_lno == vp->m_start.lno && cs.cs_cno == vp->m_start.cno) {
		v_eof(sp, &vp->m_start);
		return (1);
	}

	/* Adjust the end of the range for motion commands. */
	vp->m_stop.lno = cs.cs_lno;
	vp->m_stop.cno = cs.cs_cno;
	if (ISMOTION(vp) && cs.cs_flags == 0)
		--vp->m_stop.cno;

	/*
	 * Non-motion commands move to the end of the range.  Delete
	 * and yank stay at the start, ignore others.
	 */
	vp->m_final = ISMOTION(vp) ? vp->m_start : vp->m_stop;
	return (0);
}