/** Flush output buffer to display **/
int ttflush()
{
	int len;

	/* Compute length of write */
	len = outbuft - outbuf;
	if (len == 0)
		return(0);

	/* Reset buffer position */
	outbuft = outbuf;

	/* Perform write to screen */
	FWRITE(mpetermout, outbuf, -len, 0320);
#ifdef DEBUG
	if (ccode() != CCE) {
		printf("FWRITE fails\n");
	}
#endif
	return 0;
}