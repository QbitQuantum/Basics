void
editfhdr(ElfObject &eo, char *)
{
	char s[BUFSIZ];

	// start of file headers editing
	printf("editing file headers:\n");

	// start interactive loop
	for (int done=0; !done; )
	{
		// get cmd from user
		printf("fhdr cmd: ");
		rmvnlgets(s);
		tokenize(s, " \t");
		char *pt = gettoken(1);

		// what is the command
		if (pt == NULL || *pt == '\0')
		{
			review(eo);
		}
		else if (*pt == '?' || *pt == 'h')
		{
			printmenu();
		}
		else if (*pt == 'r')
		{
			review(eo);
		}
		else if (*pt == 'u')
		{
			update(eo);
		}
		else if (*pt == 'q')
		{
			done = 1;
		}
		else
		{
			printf("unknown cmd.\n");
		}
	}
	return;
}