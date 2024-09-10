int main (int argc, char **argv)
{
	cups_file_t	*fp_input =  NULL;			/* input file: stdin or physical file */	
    char   line[LINE_SIZE] = {0};
	
	get_LogLevel();
	setbuf (stderr, NULL);
	fprintf (stderr, "HP PS filter starting : %s \n", *argv);
	
	int i =  0;
	/* Logging cups filter arguments */
	for (   i = 0; i < argc; i++)
	{
		fprintf (stderr, "DEBUG: hppsfilter: argv[%d] = %s\n", i, argv[i]);
	}
	
	/* Logging debug information and creating outfile for debug */
	if (g_savepsfile & SAVE_PS_FILE)
	{
		/* opening ps debug file */
		open_dbg_outfile(argv[1]);
	}
	
	/* Check command-line...  */
	if (argc < 6 || argc > 7)
	{
		fputs("ERROR: hppsfilter job-id user title copies options [file]\n", stderr);
		return (1);
	}

	/* If we have 7 arguments, print the file named on the command-line.
	* Otherwise, send stdin instead...  */
	if (argc == 6)
		fp_input = cupsFileStdin();
	else
	{
		/* Try to open the print file...    */
		if ((fp_input = cupsFileOpen(argv[6], "r")) == NULL)
		{
  			fprintf(stderr, "ERROR: Unable to open print file \"%s\" - %s\n",
              argv[6], strerror);
  			return (1);
		}
	}

	int len  =  0;
	int ibodwritten = 0;
	int ireqire_bod = require_bod();
    while ( ( len = cupsFileGetLine(fp_input, line, sizeof(line) )) > 0)
    {
		hpwrite (line, len);
		/* if BOD is reqire, writting BOD command */
		if ( !ibodwritten && (!strncmp(line, "@PJL JOB NAME", 13)) && ireqire_bod)
		{
			fprintf (stderr, "HP PS filter: Matched start PJL\n");				
			ibodwritten = 1;
			emmit_bod_command();
		}
    }

    if ( (argc == 7) && (fp_input != NULL) )
        cupsFileClose (fp_input);
	
	if(g_fp_outdbgps != NULL)
	{
	    fclose (g_fp_outdbgps);		
	}
			   
	fprintf (stderr, "HP PS filter Ends\n");	
    return 0;
}