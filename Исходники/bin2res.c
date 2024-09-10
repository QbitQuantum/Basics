static int process_resources(const char* input_file_name, const char* specific_file_name, 
		      int inserting, int force_processing, int verbose)
{
    char buffer[2048], tmp_file_name[PATH_MAX];
    const char *res_file_name;
    time_t rc_last_update, res_last_update;
    FILE *fin, *fres, *ftmp = 0;
    struct stat st;
    int fd, c;

    if (!(fin = fopen(input_file_name, "r"))) return 0;
    if (stat(input_file_name, &st) < 0) return 0;
    rc_last_update = st.st_mtime;

    if (inserting)
    {
	strcpy(tmp_file_name, input_file_name);
	strcat(tmp_file_name, "-XXXXXX.temp");
	if ((fd = mkstemps(tmp_file_name, 5)) == -1)
	{
	    strcpy(tmp_file_name, "/tmp/bin2res-XXXXXX.temp");
	    if ((fd = mkstemps(tmp_file_name, 5)) == -1) return 0;
	}
	clean_file = tmp_file_name;
	if (!(ftmp = fdopen(fd, "w"))) return 0;
    }

    for (c = EOF; fgets(buffer, sizeof(buffer), fin); c = EOF)
    {
	if (inserting) fprintf(ftmp, "%s", buffer);
	if (!(res_file_name = parse_marker(buffer, &res_last_update))) continue;
        if ( (specific_file_name && strcmp(specific_file_name, res_file_name)) ||
	     (!force_processing && ((rc_last_update < res_last_update) == !inserting)) )
        {
	    if (verbose) printf("skipping '%s'\n", res_file_name);
            continue;
        }

        if (verbose) printf("processing '%s'\n", res_file_name);
	while ( (c = fgetc(fin)) != EOF && c != '{')
	    if (inserting) fputc(c, ftmp);
	if (c == EOF) break;

	if (inserting)
	{
	    if (!(fres = fopen(res_file_name, "rb"))) break;
	    if (!insert_hexdump(ftmp, fres)) break;
	    while ( (c = fgetc(fin)) != EOF && c != '}') /**/;
	    fclose(fres);
	}
	else
	{
	    clean_file = res_file_name;
	    if (!(fres = fopen(res_file_name, "wb"))) break;
	    if (!extract_hexdump(fres, fin)) break;
	    fclose(fres);
	    clean_file = NULL;
	}
    }

    fclose(fin);

    if (inserting)
    {
	fclose(ftmp);
	if (c == EOF)
        {
            if (rename(tmp_file_name, input_file_name) < 0)
            {
                /* try unlinking first, Windows rename is brain-damaged */
                if (unlink(input_file_name) < 0 || rename(tmp_file_name, input_file_name) < 0)
                    return 0;
            }
            clean_file = NULL;
        }
    }

    return c == EOF;
}