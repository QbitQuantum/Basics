void
rechist(void)
{
    Char buf[BUFSIZE], hbuf[BUFSIZE], *hfile;
    int fp, ftmp, oldidfds;
    struct varent *shist;

    if (!fast) {
	/*
	 * If $savehist is just set, we use the value of $history
	 * else we use the value in $savehist
	 */
	if ((shist = adrof(STRsavehist)) != NULL) {
	    if (shist->vec[0][0] != '\0')
		(void)Strcpy(hbuf, shist->vec[0]);
	    else if ((shist = adrof(STRhistory)) && shist->vec[0][0] != '\0')
		(void)Strcpy(hbuf, shist->vec[0]);
	    else
		return;
	}
	else
  	    return;

  	if ((hfile = value(STRhistfile)) == STRNULL) {
  	    hfile = Strcpy(buf, value(STRhome));
  	    (void) Strcat(buf, STRsldthist);
  	}

  	if ((fp = open(short2str(hfile), O_WRONLY | O_CREAT | O_TRUNC,
	    0600)) == -1) 
  	    return;

	oldidfds = didfds;
	didfds = 0;
	ftmp = SHOUT;
	SHOUT = fp;
	dumphist[2] = hbuf;
	dohist(dumphist, NULL);
	SHOUT = ftmp;
	(void)close(fp);
	didfds = oldidfds;
    }
}