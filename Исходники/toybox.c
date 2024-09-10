int read_bigcharset(char *fname)
{
	BigC	*bigc;
	Strp	*sp;
	int	fd;

	if ((fd = open(fname,O_RDONLY)) < 0)
	{
		Strcat(fname,FONT_EXTENSION);
		if ((fd = open(fname,O_RDONLY)) < 0)
			return(-1);
	}

	orig_fontlist = fontlist;
	orig_charlines = charlines;
	orig_charheight = charheight;
	orig_spacewidth = spacewidth;
	orig_kerning = kerning;

	charlines = 0;
	spacewidth = 0;
	charheight = 0;
	kerning = 0;

	readline(fd,&read_bigcharset_callback);		/* readline closes fd */

	/*
	 *  free the old font if there is one
	 */
	while(orig_fontlist)
	{
		bigc = orig_fontlist;
		orig_fontlist = bigc->next;
		while(bigc->data)
		{
			sp = bigc->data;
			bigc->data = sp->next;
			Free((char**)&sp);
		}
		Free((char**)&bigc);
	}

	return(0);
}