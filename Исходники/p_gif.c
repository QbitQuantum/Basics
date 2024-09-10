static pdf_bool
pdf_data_source_GIF_fill(PDF *p, PDF_data_source *src)
{
#define c_size	image->info.gif.c_size
#define t_size	image->info.gif.t_size
#define i_buff	image->info.gif.i_buff
#define i_bits	image->info.gif.i_bits
#define o_buff	image->info.gif.o_buff
#define o_bits	image->info.gif.o_bits

    pdf_image *		image = (pdf_image *) src->private_data;
    FILE *		fp = image->fp;
    int			n_bytes = getc(fp);	/* # of bytes to read	*/
    unsigned char *	o_curr = src->buffer_start;
    int			c_mask = (1 << c_size) - 1;
    char		filenamebuf[PDF_FILENAMELEN];
    pdf_bool		flag13 = pdf_false;

    src->bytes_available = 0;

    if (n_bytes == EOF)
    {
	strncpy(filenamebuf, image->filename, PDF_FILENAMELEN-1);
	filenamebuf[PDF_FILENAMELEN-1] = '\0';

	pdf_cleanup_image(p, image - p->images);
	pdf_error(p, PDF_IOError, "Unexpected end of GIF file '%s'",
		filenamebuf);
    }

    if (n_bytes == 0)
	return pdf_false;

    for (/* */ ; /* */ ; /* */)
    {
	int w_bits = c_size;	/* number of bits to write */
	int code;

	/* get at least c_size bits into i_buff	*/
	while (i_bits < c_size)
	{
	    if (n_bytes-- == 0)
	    {
		src->bytes_available = (size_t) (o_curr - src->buffer_start);
		return pdf_true;
	    }
	    i_buff |= getc(fp) << i_bits;	/* EOF will be caught later */
	    i_bits += 8;
	}
	code = i_buff & c_mask;
	i_bits -= c_size;
	i_buff >>= c_size;

	if (flag13 && code != 256 && code != 257)
	{
	    strncpy(filenamebuf, image->filename, PDF_FILENAMELEN-1);
	    filenamebuf[PDF_FILENAMELEN-1] = '\0';

	    pdf_cleanup_image(p, image - p->images);
	    pdf_error(p, PDF_IOError,
		"LZW code size overflow in GIF file '%s'", filenamebuf);
	}

	if (o_bits > 0)
	{
	    o_buff |= code >> (c_size - 8 + o_bits);
	    w_bits -= 8 - o_bits;
	    *(o_curr++) = (unsigned char) o_buff;
	}
	if (w_bits >= 8)
	{
	    w_bits -= 8;
	    *(o_curr++) = (unsigned char) (code >> w_bits);
	}