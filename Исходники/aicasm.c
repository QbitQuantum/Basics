void
output_listing(char *ifilename)
{
	char buf[1024];
	FILE *ifile;
	struct instruction *cur_instr;
	patch_t *cur_patch;
	symbol_node_t *cur_func;
	int *func_values;
	int instrcount;
	int instrptr;
	int line;
	int func_count;
	int skip_addr;

	instrcount = 0;
	instrptr = 0;
	line = 1;
	skip_addr = 0;
	if ((ifile = fopen(ifilename, "r")) == NULL) {
		perror(ifilename);
		stop(NULL, EX_DATAERR);
	}

	/*
	 * Determine which options to apply to this listing.
	 */
	for (func_count = 0, cur_func = SLIST_FIRST(&patch_functions);
	    cur_func != NULL;
	    cur_func = SLIST_NEXT(cur_func, links))
		func_count++;

	func_values = NULL;
	if (func_count != 0) {
		func_values = (int *)malloc(func_count * sizeof(int));

		if (func_values == NULL)
			stop("Could not malloc", EX_OSERR);
		
		func_values[0] = 0; /* FALSE func */
		func_count--;

		/*
		 * Ask the user to fill in the return values for
		 * the rest of the functions.
		 */
		
		
		for (cur_func = SLIST_FIRST(&patch_functions);
		     cur_func != NULL && SLIST_NEXT(cur_func, links) != NULL;
		     cur_func = SLIST_NEXT(cur_func, links), func_count--) {
			int input;
			
			fprintf(stdout, "\n(%s)\n", cur_func->symbol->name);
			fprintf(stdout,
				"Enter the return value for "
				"this expression[T/F]:");

			while (1) {

				input = getchar();
				input = toupper(input);

				if (input == 'T') {
					func_values[func_count] = 1;
					break;
				} else if (input == 'F') {
					func_values[func_count] = 0;
					break;
				}
			}
			if (isatty(fileno(stdin)) == 0)
				putchar(input);
		}
		fprintf(stdout, "\nThanks!\n");
	}

	/* Now output the listing */
	cur_patch = STAILQ_FIRST(&patches);
	for (cur_instr = STAILQ_FIRST(&seq_program);
	     cur_instr != NULL;
	     cur_instr = STAILQ_NEXT(cur_instr, links), instrcount++) {

		if (check_patch(&cur_patch, instrcount,
				&skip_addr, func_values) == 0) {
			/* Don't count this instruction as it is in a patch
			 * that was removed.
			 */
                        continue;
		}

		while (line < cur_instr->srcline) {
			fgets(buf, sizeof(buf), ifile);
				fprintf(listfile, "\t\t%s", buf);
				line++;
		}
		fprintf(listfile, "%03x %02x%02x%02x%02x", instrptr,
#if BYTE_ORDER == LITTLE_ENDIAN
			cur_instr->format.bytes[0],
			cur_instr->format.bytes[1],
			cur_instr->format.bytes[2],
			cur_instr->format.bytes[3]);
#else
			cur_instr->format.bytes[3],
			cur_instr->format.bytes[2],
			cur_instr->format.bytes[1],
			cur_instr->format.bytes[0]);
#endif
		fgets(buf, sizeof(buf), ifile);
		fprintf(listfile, "\t%s", buf);
		line++;
		instrptr++;
	}
	/* Dump the remainder of the file */
	while(fgets(buf, sizeof(buf), ifile) != NULL)
		fprintf(listfile, "\t\t%s", buf);

	fclose(ifile);
}