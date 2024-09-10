/** Reads the opcode list and generates output code based on the spec */
void generateCodeTable (FILE *opcodes, FILE *code)
{
	char line[MAX_LINE];
	char last[MAX_LINE];
	char tmp[MAX_LINE];
	char name[MAX_LINE];
	char parm[5], subst[20];
	int i;
	char *p, *q;
	char **cmds;
	regmatch_t matches[MAX_MATCH];
	Item *item;

	printf("Generating opcode implementations...");
	last[0] = 0;
	do
	{			
		fgets(line, MAX_LINE, opcodes);
		trim(line);
		
		if (feof(opcodes))
			break;
				
		for (q = line, p = q+OPCODE_OFFSET; *p; *q++ = *p++);	/* Skip the hex part */
		*q = 0;
		
		/* Avoid duplicate opcodes */
		if (strcmp(last, line) == 0)
			continue;		
		strcpy(last, line);
			
		/* Find the appropriate pattern */
		for (i = 0; i < nItems; i++)
		{
			if (regexec(&items[i].re, line, MAX_MATCH, matches, REG_EXTENDED) == 0)
			{	
				if (matches[0].rm_so == 0 && matches[0].rm_eo == strlen(line))	/* Match only entire line (fixes problem with INC HL being matched to INC H */
				{
					/*printf("%s : match %s\n", &line, items[i].pat);*/
					break;
				}
			}
		}
		
		if (i >= nItems)
        {
			fatal2(line, " didn't match anything");
            continue;
        }
			
		item = &items[i];
		
		/* Print function stub */
		fixName(line, name);
        fprintf(code, "void Z80CPU::%s ()\n{\n", name);
				
		/* Substitute submatches in each output line and print the code */
		cmds = item->line;
		strcpy(parm, "%0");
		while (*cmds)
		{
			if (!printCall(*cmds, code))
			{
				strncpy(tmp, *cmds, MAX_LINE);
				q = tmp;
		
				for (i = 1; i < MAX_MATCH; i++)
				{
					parm[1] = i + '0';
					strncpy(subst, &line[matches[i].rm_so], matches[i].rm_eo - matches[i].rm_so);
					subst[matches[i].rm_eo - matches[i].rm_so] = 0;
					
					substStr(tmp, parm, subst);
				}
				fprintf(code, "%s\n", tmp);
			}
			
			cmds++;	
		}
		
		fprintf(code, "}\n\n\n");
	} while(1);
	printf("done\n");
}