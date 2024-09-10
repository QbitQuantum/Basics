int vglInit(FILE * out)
{
    vgl_map_table_t * tab = __vgl_map_table;
    int missing = 0;

    while (tab->fname) {
	__extfuncptr * fptr = (__extfuncptr *)tab->fptr;

	*fptr = (__extfuncptr)getProcAddress(tab->fname);

	if (*fptr == 0) {
	    *fptr = (__extfuncptr)__vgl_missing_func;

	    if (out) {
		if (!missing) {
		    fprintf(out, "vglInit: Missing extension functions:\n", tab->fname);
		}
		fprintf(out, "  %s\n", tab->fname);
	    }

	    missing++;
	}

	tab++;
    }

    if (out && missing) {
	fprintf(out, "%d functions are missing\n", missing);
    }

    return -missing;
}