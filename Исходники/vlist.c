static void
rt_uplot_get_args(FILE *fp, const struct uplot *up, char *carg, fastf_t *arg)
{
    size_t ret;
    int i, j;
    int cc = 0;
    char inbuf[SIZEOF_NETWORK_DOUBLE] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

    for (i = 0; i < up->narg; i++) {
	switch (up->targ) {
	    case TSHORT:
		arg[i] = getshort(fp);
		break;
	    case TIEEE:
	    {
		double scan;
		ret = fread(inbuf, SIZEOF_NETWORK_DOUBLE, 1, fp);
		if (ret != 1)
		    bu_log("WARNING: uplot read failure\n");
		ntohd((unsigned char *)&scan, (unsigned char *)inbuf, 1);
		arg[i] = scan; /* convert double to fastf_t */
		break;
	    }
	    case TSTRING:
		j = 0;
		while (!feof(fp) &&
		       (cc = getc(fp)) != '\n')
		    carg[j++] = cc;
		carg[j] = '\0';
		break;
	    case TCHAR:
		cc = getc(fp);
		if (cc == EOF)
		    return;

		carg[i] = cc;
		arg[i] = 0;
		break;
	    case TNONE:
	    default:
		arg[i] = 0;	/* ? */
		break;
	}
    }
}