int     get_mail_conf_time2(const char *name1, const char *name2,
			            int defval, int def_unit, int min, int max)
{
    int     intval;
    char   *name;

    name = concatenate(name1, name2, (char *) 0);
    if (convert_mail_conf_time(name, &intval, def_unit) == 0)
	set_mail_conf_time_int(name, defval);
    if (convert_mail_conf_time(name, &intval, def_unit) == 0)
	msg_panic("get_mail_conf_time2: parameter not found: %s", name);
    check_mail_conf_time(name, intval, min, max);
    myfree(name);
    return (intval);
}