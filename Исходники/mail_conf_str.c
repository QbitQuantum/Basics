char   *get_mail_conf_str2(const char *name1, const char *name2,
			           const char *defval,
			           int min, int max)
{
    const char *strval;
    char   *name;

    name = concatenate(name1, name2, (char *) 0);
    if ((strval = mail_conf_lookup_eval(name)) == 0) {
	strval = mail_conf_eval(defval);
	mail_conf_update(name, strval);
    }
    check_mail_conf_str(name, strval, min, max);
    myfree(name);
    return (mystrdup(strval));
}