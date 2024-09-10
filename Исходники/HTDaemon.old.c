/*	Send a string down a socket
**	---------------------------
**
**	The trailing zero is not sent.
**	There is a maximum string length.
*/
PUBLIC int HTWriteASCII ARGS2(int, soc, char *, s)
{
#ifdef NOT_ASCII
    char * p;
    char ascii[255];
    char *q = ascii;
    for (p=s; *p; p++) {
        *q++ = TOASCII(*p);
    }
    return NETWRITE(soc, ascii, p-s);
#else
    return NETWRITE(soc, s, strlen(s));
#endif
}