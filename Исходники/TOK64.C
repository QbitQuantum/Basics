void process_mult (FILE *in, int overwrite, int casemode, int colmode)
{
	Basrec_type rec;
	int processing = FALSE, i, j, eol, len;
	char file_out [MAXPATH], casetext [MAXLINE], fext [MAXEXT];
	FILE *out;

	while (getline (line, MAXLINE, in) != EOF)
	{
		i = 0;
		eol = strlen (line);
		while (i < eol && isspace (line [i])) i ++;
		for (j = i; j < eol; j++) casetext [j] = tolower (line [j]);
		casetext [j] = 0;
		len = strlen (START_PROC);

		if (! strncmp (& (casetext [i]), START_PROC, len))
		{
			if (processing)
			{
				end_prg (out);
				fclose (out);
				processing = FALSE;
				fprintf (stderr, " done.\n");
			}

			i += len;

			if (sscanf (& (line [i]), "%s", file_out) == 1)
			{
				if (! extension (file_out, fext, MAXEXT -1))
					strncat (file_out, PRG_EXT, MAXPATH - 1);
				else if (! strcmp (fext, TXT_EXT))
				{
					fclose (in);
					fprintf (stderr, "%s: not expecting \"%s\" as output.\n",
						program, file_out);
					exit (EXITBAD);
				}

				if (! exit_exists (overwrite, in, file_out))
					if ((out = fopen (file_out, "wb")) == NULL)
					{
						fprintf (stderr, "%s: Can't open %s for output\n",
							program, file_out);
						fclose (in);
						exit (EXITBAD);
					}
					else
					{
						fprintf (stderr, "==> %s ...", file_out);
						processing = TRUE;
						set_addy (BASREC_NULL);
						tokenize (BASREC_NULL, CH_NULL, TRUE, TRUE);
						start_prg (out);
					}
			}
			else
			{
				fprintf (stderr, "%s: no output filename given\n",
					program);
				fclose (in);
				exit (EXITBAD);
			}
		}
		else if (! strncmp (& (casetext [i]), STOP_PROC, strlen (STOP_PROC)))
		{
			if (processing)
			{
				end_prg (out);
				fclose (out);
				processing = FALSE;
				fprintf (stderr, " done.\n");
			}
		}
		else if (processing)
		{
			if (tokenize (&rec, line, casemode, colmode))
			{
				set_addy (&rec);
				outprg (out, &rec);
			}
		}
	}

	return;
}