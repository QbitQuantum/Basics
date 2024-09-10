/** parse declaration (syntax analize) */
void dcl(void) {
	int ns;

	/** count stars */
	for (ns = 0; gettoken() == '*'; )
		ns++;

	/** 3. check last called gettoken() results */
	if (tokentype == ERR) {
		printf("error[2]: some error symbol inserted\n");
		return;
	}

	dirdcl();

	/** 3. check dirdcl() results (assume error message already printed) */
	if (tokentype == ERR)
		return;

	while (ns-- > 0)
		strcat(out, " pointer to");
}