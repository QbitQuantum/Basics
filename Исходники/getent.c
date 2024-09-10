static int
services(int argc, char *argv[])
{
	struct servent	*se;
	int		i, rv = RV_OK;

	setservent(1);
	if (argc == 2) {
		while ((se = getservent()) != NULL)
			SERVICESPRINT;
	} else {
		for (i = 2; i < argc; i++) {
			const char	*err;
			long long	id;
			char *proto = strchr(argv[i], '/');

			if (proto != NULL)
				*proto++ = '\0';
			id = strtonum(argv[i], 0, UINT_MAX, &err);
			if (!err)
				se = getservbyport(htons((u_short)id), proto);
			else
				se = getservbyname(argv[i], proto);
			if (se != NULL)
				SERVICESPRINT;
			else {
				rv = RV_NOTFOUND;
				break;
			}
		}
	}
	endservent();
	return rv;
}