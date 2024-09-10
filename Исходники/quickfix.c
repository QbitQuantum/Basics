/*
 * Read the errorfile into memory, line by line, building the error list.
 * Return FAIL for error, OK for success.
 */
	int
qf_init()
{
	char_u 			namebuf[CMDBUFFSIZE + 1];
	char_u			errmsg[CMDBUFFSIZE + 1];
	int				col;
	int				type;
	int				valid;
	long			lnum;
	int				enr;
	FILE			*fd;
	struct qf_line	*qfp = NULL;
	struct qf_line	*qfprev = NULL;		/* init to make SASC shut up */
	char_u			*pfmt, *fmtstr;
#ifdef UTS2
	char_u			*(adr[7]);
#else
	void			*(adr[7]);
#endif
	int				adr_cnt = 0;
	int				maxlen;
	int				i;

	if (p_ef == NULL || *p_ef == NUL)
	{
		emsg(e_errorf);
		return FAIL;
	}
	if ((fd = fopen((char *)p_ef, "r")) == NULL)
	{
		emsg2(e_openerrf, p_ef);
		return FAIL;
	}
	qf_free();
	qf_index = 0;
	for (i = 0; i < 7; ++i)
		adr[i] = NULL;

/*
 * The format string is copied and modified from p_efm to fmtstr.
 * Only a few % characters are allowed.
 */
		/* get some space to modify the format string into */
		/* must be able to do the largest expansion 7 times (7 x 3) */
	maxlen = STRLEN(p_efm) + 25;
	fmtstr = alloc(maxlen);
	if (fmtstr == NULL)
		goto error2;
	for (pfmt = p_efm, i = 0; *pfmt; ++pfmt, ++i)
	{
		if (pfmt[0] != '%')				/* copy normal character */
			fmtstr[i] = pfmt[0];
		else
		{
			fmtstr[i++] = '%';
			switch (pfmt[1])
			{
			case 'f':		/* filename */
					adr[adr_cnt++] = namebuf;

			case 'm':		/* message */
					if (pfmt[1] == 'm')
						adr[adr_cnt++] = errmsg;
					fmtstr[i++] = '[';
					fmtstr[i++] = '^';
					if (pfmt[2])
						fmtstr[i++] = pfmt[2];
					else
#ifdef MSDOS
						fmtstr[i++] = '\r';
#else
						fmtstr[i++] = '\n';
#endif
					fmtstr[i] = ']';
					break;
			case 'c':		/* column */
					adr[adr_cnt++] = &col;
					fmtstr[i] = 'd';
					break;
			case 'l':		/* line */
					adr[adr_cnt++] = &lnum;
					fmtstr[i++] = 'l';
					fmtstr[i] = 'd';
					break;
			case 'n':		/* error number */
					adr[adr_cnt++] = &enr;
					fmtstr[i] = 'd';
					break;
			case 't':		/* error type */
					adr[adr_cnt++] = &type;
					fmtstr[i] = 'c';
					break;
			case '%':		/* %% */
			case '*':		/* %*: no assignment */
					fmtstr[i] = pfmt[1];
					break;
			default:
					EMSG("invalid % in format string");
					goto error2;
			}
			if (adr_cnt == 7)
			{
				EMSG("too many % in format string");
				goto error2;
			}
			++pfmt;
		}
		if (i >= maxlen - 6)
		{
			EMSG("invalid format string");
			goto error2;
		}
	}
	fmtstr[i] = NUL;

	while (fgets((char *)IObuff, CMDBUFFSIZE, fd) != NULL && !got_int)
	{
		if ((qfp = (struct qf_line *)alloc((unsigned)sizeof(struct qf_line))) == NULL)
			goto error2;

		IObuff[CMDBUFFSIZE] = NUL;	/* for very long lines */
		namebuf[0] = NUL;
		errmsg[0] = NUL;
		lnum = 0;
		col = 0;
		enr = -1;
		type = 0;
		valid = TRUE;

		if (sscanf((char *)IObuff, (char *)fmtstr, adr[0], adr[1], adr[2], adr[3],
												adr[4], adr[5]) != adr_cnt)
		{
			namebuf[0] = NUL;			/* something failed, remove file name */
			valid = FALSE;
			STRCPY(errmsg, IObuff);		/* copy whole line to error message */
			if ((pfmt = STRRCHR(errmsg, '\n')) != NULL)
				*pfmt = NUL;
#ifdef MSDOS
			if ((pfmt = STRRCHR(errmsg, '\r')) != NULL)
				*pfmt = NUL;
#endif
		}

		if (namebuf[0] == NUL)			/* no file name */
			qfp->qf_fnum = 0;
		else
			qfp->qf_fnum = buflist_add(namebuf);
		if ((qfp->qf_text = strsave(errmsg)) == NULL)
			goto error1;
		qfp->qf_lnum = lnum;
		qfp->qf_col = col;
		qfp->qf_nr = enr;
		qfp->qf_type = type;
		qfp->qf_valid = valid;

		if (qf_count == 0)		/* first element in the list */
		{
			qf_start = qfp;
			qfp->qf_prev = qfp;	/* first element points to itself */
		}
		else
		{
			qfp->qf_prev = qfprev;
			qfprev->qf_next = qfp;
		}
		qfp->qf_next = qfp;		/* last element points to itself */
		qfp->qf_cleared = FALSE;
		qfprev = qfp;
		++qf_count;
		if (qf_index == 0 && qfp->qf_valid)		/* first valid entry */
		{
			qf_index = qf_count;
			qf_ptr = qfp;
		}
		breakcheck();
	}
	free(fmtstr);
	if (!ferror(fd))
	{
		if (qf_index == 0)		/* no valid entry found */
		{
			qf_ptr = qf_start;
			qf_index = 1;
			qf_nonevalid = TRUE;
		}
		else
			qf_nonevalid = FALSE;
		fclose(fd);
		qf_jump(0, 0);			/* display first error */
		return OK;
	}
	emsg(e_readerrf);
error1:
	free(qfp);
error2:
	fclose(fd);
	qf_free();
	return FAIL;
}