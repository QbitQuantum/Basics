static const char *
at_pr_port(struct sockaddr_at *sat)
{
static	char mybuf[50];
	struct servent *serv;

	switch(sat->sat_port) {
	case ATADDR_ANYPORT:
		return("*");
	case 0xff:
		return "????";
	default:
		if (numeric_port) {
			(void)snprintf(mybuf, sizeof(mybuf), "%d",
			    (unsigned int)sat->sat_port);
		} else {
			serv = getservbyport(sat->sat_port, "ddp");
			if (serv == NULL)
				(void)snprintf(mybuf, sizeof(mybuf), "%d",
				    (unsigned int) sat->sat_port);
			else
				(void) snprintf(mybuf, sizeof(mybuf), "%s",
				    serv->s_name);
		}
	}
	return mybuf;
}