void katuyou(FILE *fp_out)
{
    FILE	*fp;
    char	cur_path[FILENAME_MAX];
    char	juman_path[FILENAME_MAX];
    char	katuyoufile_path[FILENAME_MAX];

    getpath(cur_path, juman_path);

    while (1) {
	if ((fp = pathfopen(KATUYOUFILE, "r", "", katuyoufile_path))
	    != NULL) break;
	if ((fp = pathfopen(KATUYOUFILE, "r", cur_path, katuyoufile_path))
	    != NULL) break;
	if ((fp = pathfopen(KATUYOUFILE, "r", juman_path, katuyoufile_path))
	    != NULL) break;
	if ((fp = pathfopen(KATUYOUFILE, "r", "../dic/", katuyoufile_path)) /* for compilation */
	    != NULL) break;
	error(OpenError, "can't open", katuyoufile_path, ".", EOA);
    }

    if (fp_out != NULL) {
	 print_current_time(fp_out);
	 fprintf(fp_out, "%s parsing... ", katuyoufile_path);
    }

    initialize_type_form(); read_type_form(fp);

    if (fp_out != NULL)
	 fputs("done.\n\n", fp_out);

    fclose(fp);
}