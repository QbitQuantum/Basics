long    get_mail_conf_long2(const char *name1, const char *name2, long defval,
			            long min, long max)
{
    long    longval;
    char   *name;

    name = concatenate(name1, name2, (char *) 0);
    if (convert_mail_conf_long(name, &longval) == 0)
	set_mail_conf_long(name, longval = defval);
    check_mail_conf_long(name, longval, min, max);
    myfree(name);
    return (longval);
}