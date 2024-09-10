int     get_mail_conf_int2(const char *name1, const char *name2, int defval,
			        int min, int max)
{
    int     intval;
    char   *name;

    name = concatenate(name1, name2, (char *) 0);
    if (convert_mail_conf_int(name, &intval) == 0)
	set_mail_conf_int(name, intval = defval);
    check_mail_conf_int(name, intval, min, max);
    myfree(name);
    return (intval);
}