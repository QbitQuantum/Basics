/*
 * Get from "/proc/net/dev" all interfaces listed there; if they're
 * already in the list of interfaces we have, that won't add another
 * instance, but if they're not, that'll add them.
 *
 * We don't bother getting any addresses for them; it appears you can't
 * use SIOCGIFADDR on Linux to get IPv6 addresses for interfaces, and,
 * although some other types of addresses can be fetched with SIOCGIFADDR,
 * we don't bother with them for now.
 *
 * We also don't fail if we couldn't open "/proc/net/dev"; we just leave
 * the list of interfaces as is.
 */
static int
scan_proc_net_dev(pcap_if_t **devlistp, int fd, char *errbuf)
{
	FILE *proc_net_f;
	char linebuf[512];
	int linenum;
	unsigned char *p;
	char name[512];	/* XXX - pick a size */
	char *q, *saveq;
	struct ifreq ifrflags;
	int ret = 0;

	proc_net_f = fopen("/proc/net/dev", "r");
	if (proc_net_f == NULL)
		return (0);

	for (linenum = 1;
	    fgets(linebuf, sizeof linebuf, proc_net_f) != NULL; linenum++) {
		/*
		 * Skip the first two lines - they're headers.
		 */
		if (linenum <= 2)
			continue;

		p = &linebuf[0];

		/*
		 * Skip leading white space.
		 */
		while (*p != '\0' && isspace(*p))
			p++;
		if (*p == '\0' || *p == '\n')
			continue;	/* blank line */

		/*
		 * Get the interface name.
		 */
		q = &name[0];
		while (*p != '\0' && !isspace(*p)) {
			if (*p == ':') {
				/*
				 * This could be the separator between a
				 * name and an alias number, or it could be
				 * the separator between a name with no
				 * alias number and the next field.
				 *
				 * If there's a colon after digits, it
				 * separates the name and the alias number,
				 * otherwise it separates the name and the
				 * next field.
				 */
				saveq = q;
				while (isdigit(*p))
					*q++ = *p++;
				if (*p != ':') {
					/*
					 * That was the next field,
					 * not the alias number.
					 */
					q = saveq;
				}
				break;
			} else
				*q++ = *p++;
		}
		*q = '\0';

		/*
		 * Get the flags for this interface, and skip it if
		 * it's not up.
		 */
		strncpy(ifrflags.ifr_name, name, sizeof(ifrflags.ifr_name));
		if (ioctl(fd, SIOCGIFFLAGS, (char *)&ifrflags) < 0) {
			if (errno == ENXIO)
				continue;
			(void)snprintf(errbuf, PCAP_ERRBUF_SIZE,
			    "SIOCGIFFLAGS: %.*s: %s",
			    (int)sizeof(ifrflags.ifr_name),
			    ifrflags.ifr_name,
			    pcap_strerror(errno));
			ret = -1;
			break;
		}
		if (!(ifrflags.ifr_flags & IFF_UP))
			continue;

		/*
		 * Add an entry for this interface, with no addresses.
		 */
		if (pcap_add_if(devlistp, name, ifrflags.ifr_flags, NULL,
		    errbuf) == -1) {
			/*
			 * Failure.
			 */
			ret = -1;
			break;
		}
	}
	if (ret != -1) {
		/*
		 * Well, we didn't fail for any other reason; did we
		 * fail due to an error reading the file?
		 */
		if (ferror(proc_net_f)) {
			(void)snprintf(errbuf, PCAP_ERRBUF_SIZE,
			    "Error reading /proc/net/dev: %s",
			    pcap_strerror(errno));
			ret = -1;
		}
	}

	(void)fclose(proc_net_f);
	return (ret);
}