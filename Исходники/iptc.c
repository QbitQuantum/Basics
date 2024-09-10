/* {{{ php_iptc_put1
 */
static int php_iptc_put1(FILE *fp, int spool, unsigned char c, unsigned char **spoolbuf)
{
	if (spool > 0)
		PUTC(c);

	if (spoolbuf) *(*spoolbuf)++ = c;

  	return c;
}