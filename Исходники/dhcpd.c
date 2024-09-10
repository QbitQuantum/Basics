int sfn_print(char* buffer,u_char *s, u_char *ep)
{
	register int ret;
	u_char c;

	ret = 1;			/* assume truncated */
	while (ep == NULL || s < ep) {
		c = *s++;
		if (c == '\0') {
			ret = 0;
			break;
		}
		if (!isascii(c)) {
			c = toascii(c);
			sprintf(buffer,"%sM",buffer);
			sprintf(buffer,"%s-",buffer);
		}
		if (!isprint(c)) {
			c ^= 0x40;	/* DEL to ?, others to alpha */
			sprintf(buffer,"%s^",buffer);
		}
		sprintf(buffer,"%s%s",buffer,&c);
	}
	return(ret);
}