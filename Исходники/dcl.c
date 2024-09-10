/* dcl:  parse a declarator */
int dcl(void)
{
	char tmp[1000];

	tmp[0] = '\0';
	while (tokentype == '*') {
		while (gettoken() == QUALIFIER) {
			strcat(tmp, " ");
			strcat(tmp, token);
		}
		strcat(tmp, " pointer to");
	}
	if (dirdcl() != 0)
		return 1;
	strcat(out, tmp);

	return 0;
}