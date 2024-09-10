 char *
lcon_name_ASL(ASL *asl, int n)
{
	char buf[32], **np, *rv;
	static char badlconname[] = "**lcon_name(bad n)**";

	if (n < 0 || n >= n_lcon)
		return badlconname;
	if (!asl->i.lconnames)
		get_row_names(asl);
	np = asl->i.lconnames + n;
	if (!(rv = *np)) {
		*np = rv = (char*)mem(Sprintf(buf,"_slogcon[%d]",n+1)+1);
		strcpy(rv, buf);
		}
	return rv;
	}