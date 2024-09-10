com_table *
get_comtab_ent(char *pattern, int pat_len)
{
    com_table *ctp;
    int len;

    for (ctp = ComTab; ctp->com_name; ++ctp) {
	len = FMAX(pat_len, (int)strlen(ctp->com_name));
	if ((bu_strncmp (pattern, ctp->com_name, len)) == 0)
	    break;
    }
    return (ctp->com_name) ? ctp : CT_NULL;
}