static int read_string_inner(UI *ui, UI_STRING *uis, int echo, int strip_nl)
	{
	static int ps;
	int ok;
	char result[BUFSIZ];
	int maxsize = BUFSIZ-1;
#if !defined(OPENSSL_SYS_WIN16) && !defined(OPENSSL_SYS_WINCE)
	char *p;

	intr_signal=0;
	ok=0;
	ps=0;

	pushsig();
	ps=1;

	if (!echo && !noecho_console(ui))
		goto error;
	ps=2;

	result[0]='\0';
#ifdef OPENSSL_SYS_MSDOS
	if (!echo)
		{
		noecho_fgets(result,maxsize,tty_in);
		p=result; /* FIXME: noecho_fgets doesn't return errors */
		}
	else
		p=fgets(result,maxsize,tty_in);
#else
	p=fgets(result,maxsize,tty_in);
#endif
	if(!p)
		goto error;
	if (feof(tty_in)) goto error;
	if (ferror(tty_in)) goto error;
	if ((p=(char *)strchr(result,'\n')) != NULL)
		{
		if (strip_nl)
			*p='\0';
		}
	else
		if (!read_till_nl(tty_in))
			goto error;
	if (UI_set_result(ui, uis, result) >= 0)
		ok=1;

error:
	if (intr_signal == SIGINT)
		ok=-1;
	if (!echo) fprintf(tty_out,"\n");
	if (ps >= 2 && !echo && !echo_console(ui))
		ok=0;

	if (ps >= 1)
		popsig();
#else
	ok=1;
#endif

	OPENSSL_cleanse(result,BUFSIZ);
	return ok;
	}