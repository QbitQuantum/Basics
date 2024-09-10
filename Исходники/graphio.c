/* _agstrcanon:
 * Canonicalize an ordinary string if necessary.
 */
static char* 
_agstrcanon (char* arg, char* buf)
{
    char *s = arg;
    unsigned char uc;
    char *p = buf;
    int cnt = 0;
    int has_special = FALSE;
    int maybe_num;

    if (ISEMPTYSTR(arg))
	return "\"\"";
    *p++ = '\"';
    uc = *(unsigned char *) s++;
    maybe_num = (isdigit(uc) || (uc == '.'));
    while (uc) {
	if (uc == '\"') {
	    *p++ = '\\';
	    has_special = TRUE;
	} else {
	    if (!ISALNUM(uc))
		has_special = TRUE;
	    else if (maybe_num && (!isdigit(uc) && (uc != '.')))
		has_special = TRUE;
	}
	*p++ = (char) uc;
	uc = *(unsigned char *) s++;
	cnt++;
	if (cnt % SMALLBUF == 0) {
	    *p++ = '\\';
	    *p++ = '\n';
	    has_special = TRUE;
	}
    }
    *p++ = '\"';
    *p = '\0';
    if (has_special)
	return buf;

    /* use quotes to protect tokens (example, a node named "node") */
    if (agtoken(arg) >= 0)
	return buf;
    return arg;
}