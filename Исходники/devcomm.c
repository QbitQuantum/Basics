static int
comm_getcur(			/* get and return cursor position */
	int	*xp,
	int	*yp
)
{
	int	c;

	putc(COM_GETCUR, devout);
	fflush(devout);
	if (getc(devin) != COM_GETCUR)
		reply_error("getcur");
	c = getc(devin);
	*xp = getw(devin);
	*yp = getw(devin);
	return(c);
}