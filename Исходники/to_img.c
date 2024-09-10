int
PicBuf_to_IMG (const GEN_PAR *pg, const OUT_PAR *po)
{
    FILE    *fd;            /* file descriptor                  */

    int     row_c;                  /* row counter              */
    int     Img_w = po->picbuf->nb; /* bytes per row            */
    int     Img_h = po->picbuf->nr; /* number of lines          */

    int	    percent = 0;	    /* progression indicator	*/

    int     Dpi_x = po->dpi_x;      /* dots per inch            */
    int     Dpi_y = po->dpi_y;

    int     vert_rep;       /* vertical repetitions             */

    Byte    act_byte;       /* actual byte                      */

    int     act_pos;        /* actual byte-position in the row  */
    int     first_pos = 0;  /* first pos. of bit string         */
    int     last_pos = 0;   /* last pos. of bit string          */
    int     i_pos;          /* loop index                       */

    int     open_BS;            /* was a bit string opened?     */

    int     empty_SR_len;       /* length of empty solid run    */
    int     full_SR_len;        /* length of full solid run     */
    int     PR_len;             /* length of pattern run        */
    int     BS_len;             /* length of bit string         */

    int     idummy;
    int	    err;
    double  ddummy;
    const   PicBuf* pbuf;

    err = 0;
    pbuf = po->picbuf;
    if (pbuf->depth > 1)
    {
	Eprintf ( "\nIMG mode does not support colors yet -- sorry\n");
	return ERROR;
    }

    /*                  */
    /* action message   */
    /*                  */
    if (!pg->quiet)
    {
	Eprintf ( "\n\nWriting IMG output: %d rows of %d bytes\n",
		pbuf->nr, pbuf->nb);
	Eprintf ("\n%s:\no open",
		*po->outfile == '-' ? "<stdout>" : po->outfile);
    }


    if (*po->outfile != '-')
    {
#ifdef VAX
	if ((fd = fopen(po->outfile, WRITE_BIN, "rfm=var","mrs=512")) == NULL)
	{
#else
	if ((fd = fopen(po->outfile, WRITE_BIN)) == NULL)
	{
#endif
		PError ("hp2xx -- opening output file");
		return ERROR;
	}
    }
    else	fd = stdout;


    /**
     ** write header (8 words)
     **/

    if (!pg->quiet)
	Eprintf ("\no write\n  - header");

    /* version number = 1   */
    if ((err = write_byte_IMG((Byte)0, fd)) != 0)
	goto IMG_exit;
    if ((err = write_byte_IMG((Byte)1, fd)) != 0)
	goto IMG_exit;

    /* length of header (in words) = 8  */
    if ((err = write_byte_IMG((Byte)0, fd)) != 0)
	goto IMG_exit;
    if ((err = write_byte_IMG((Byte)8, fd)) != 0)
	goto IMG_exit;

    /* number of bits/pixel (bit-planes) = 1    */
    if ((err = write_byte_IMG((Byte)0, fd)) != 0)
	goto IMG_exit;
    if ((err = write_byte_IMG((Byte)1, fd)) != 0)
	goto IMG_exit;

    /* length of pattern run (in bytes) = 2     */
    if ((err = write_byte_IMG((Byte)0, fd)) != 0)
	goto IMG_exit;
    if ((err = write_byte_IMG((Byte)2, fd)) != 0)
	goto IMG_exit;

    /* width of pixel in 1/1000 mm  */
    ddummy = (double)Dpi_x;
    ddummy = 25.4 / ddummy * 1000.0 / 256;
    act_byte = (Byte)ddummy;
    if ((err = write_byte_IMG (act_byte, fd)) != 0)
	goto IMG_exit;
    ddummy = (double)Dpi_x;
    ddummy = 25.4 / ddummy * 1000.0;
    idummy = (int)ddummy & 255;
    act_byte = (Byte)idummy;
    if ((err = write_byte_IMG (act_byte, fd)) != 0)
	goto IMG_exit;

    /* height of pixel in 1/1000 mm */
    ddummy = (double)Dpi_y;
    ddummy = 25.4 / ddummy * 1000.0 / 256;
    act_byte = (Byte)ddummy;
    if ((err = write_byte_IMG(act_byte, fd)) != 0)
	goto IMG_exit;
    ddummy = (double)Dpi_y;
    ddummy = 25.4 / ddummy * 1000.0;
    idummy = (int)ddummy & 255;
    act_byte = (Byte)idummy;
    if ((err = write_byte_IMG(act_byte, fd)) != 0)
	goto IMG_exit;

    /* width of row in pixel    */
    idummy = Img_w * 8 / 256;
    act_byte = (Byte)idummy;
    if ((err = write_byte_IMG(act_byte, fd)) != 0)
	goto IMG_exit;
    idummy = Img_w * 8;
    idummy = idummy & 255;
    act_byte = (Byte)idummy;
    if ((err = write_byte_IMG(act_byte, fd)) != 0)
	goto IMG_exit;

    /* number of rows */
    idummy = Img_h  / 256;
    act_byte = (Byte)idummy;
    if ((err = write_byte_IMG(act_byte, fd)) != 0)
	goto IMG_exit;
    idummy = Img_h;
    idummy = idummy & 255;
    act_byte = (Byte)idummy;
    if ((err = write_byte_IMG(act_byte, fd)) != 0)
	goto IMG_exit;

    if (!pg->quiet)
	Eprintf ("\n  - data: ");

    /**
     **  Loop over all lines
     **/

    for (row_c = 0; row_c < Img_h; row_c++)
    {
	/*      */
	/* ...  */
	/*      */
	if(!pg->quiet)
	{
	    if((int)(((float)row_c * 100.0) / (float)Img_h) >= (percent + 10))
	    {
		percent += 10;
		Eprintf ( "%d%% ",percent);
	    }
	}

	/*                                  */
	/* Determine vertical repetition    */
	/*                                  */
	if ((vert_rep = vert_rep_IMG(row_c, pbuf)) > 0)
	{
	    row_c += vert_rep;
	    if(!pg->quiet)
	    {
		if((int)(((float)row_c * 100.0) / (float)Img_h) >= (percent + 10))
		{
			percent += 10;
			Eprintf ( "%d%% ",percent);
		}
	    }
	    if ((err = write_VR_IMG((Byte)(vert_rep + 1), fd)) != 0)
		goto IMG_exit;
	}

	/**
	 **  Analyse actual row in detail
	 **/

	/* prepare bit string switch        */

	open_BS = FALSE;

	/* prepare byte position            */

	act_pos = 0;

	/**
	 ** Loop over all bytes in actual row
	 **/
	do {
	    if(open_BS == TRUE  )
	    {
		/* bit string was opened before */

		if (  (empty_SR_len = empty_SR_IMG(row_c, act_pos, pbuf)) > 3
		   || (full_SR_len = full_SR_IMG(row_c, act_pos, pbuf)) > 3
		   || (PR_len = PR_IMG(row_c, act_pos, pbuf)) > 2
		   || act_pos >= Img_w - 1
		   || last_pos - first_pos + 1 >= 254)
		{
		    /* it's worth to stop the bit string    */
		    open_BS = FALSE;

		    if (act_pos >= Img_w -1)    /* special case:    */
		    {
			last_pos = act_pos;     /* last byte in row */
			act_pos++;
		    }

		    BS_len = last_pos - first_pos + 1;
		    if ((err = write_BS_IMG((Byte)BS_len, fd)) != 0)
			goto IMG_exit;
		    for (i_pos = first_pos; i_pos <= last_pos; i_pos++)
		    {
			act_byte = get_byte_IMG(row_c, i_pos, pbuf);
			if ((err = write_byte_IMG(act_byte, fd)) != 0)
				goto IMG_exit;
		    }

		}
		else
		{
		    /* the bit string should continue   */
		    last_pos = act_pos;
		    act_pos++;
		}

	    } else {
		/* no bit string open   */

		if ((empty_SR_len = empty_SR_IMG(row_c, act_pos, pbuf)) > 0)
		{
		    act_pos += empty_SR_len;
		    if ((err = write_empty_SR_IMG((Byte)empty_SR_len, fd)) != 0)
			goto IMG_exit;

		}
	      else
		if ((full_SR_len = full_SR_IMG(row_c, act_pos, pbuf)) > 0)
		{
		    act_pos += full_SR_len;
		    if ((err = write_full_SR_IMG((Byte)full_SR_len, fd)) != 0)
			goto IMG_exit;

		}
	      else
		if ((PR_len = PR_IMG(row_c, act_pos, pbuf)) > 0)
		{
		    if ((err = write_PR_IMG((Byte)(PR_len + 1),
				 get_byte_IMG(row_c, act_pos, pbuf),
				 get_byte_IMG(row_c, act_pos +1 , pbuf),
				 fd)) != 0)
			goto IMG_exit;
		    act_pos += (PR_len + 1) * 2;

		}
	      else
		{    /* remaining: bit string, open it   */
		    open_BS = TRUE;
		    first_pos = act_pos;
		    last_pos  = act_pos;
		    if (act_pos < Img_w - 1)
			act_pos++;
		}

	    }
	} while (act_pos < Img_w);

    }

    if(!pg->quiet)
	if (percent < 100)
		Eprintf ( "100%%");
	Eprintf ( "\no close\n");

IMG_exit:
    if (fd != NULL && fd != stdout)
	if (fclose(fd) != 0)
	{
		PError("\nhp2xx -- closing IMG:");
		return ERROR;
	}
    if(!pg->quiet)
	Eprintf ( "\n(End of IMG)\n");
    return err;
}