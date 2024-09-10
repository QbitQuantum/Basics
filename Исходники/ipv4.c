int ipv4_del_nameservers_from_resolv_conf(struct tunnel *tunnel)
{
	int ret = -1;
	FILE *file;
	struct stat stat;
	char ns1[27], ns2[27]; // 11 + 15 + 1
	char *buffer, *line;

	// If nameservers were already there before setting up tunnel,
	// don't delete them from /etc/resolv.conf
	if (!tunnel->ipv4.ns_are_new)
		return 0;

	if (tunnel->ipv4.ns1_addr.s_addr == 0)
		return 1;

	file = fopen("/etc/resolv.conf", "r+");
	if (file == NULL) {
		log_warn("Could not open /etc/resolv.conf (%s).\n",
		         strerror(errno));
		return 1;
	}

	if (fstat(fileno(file), &stat) == -1) {
		log_warn("Could not stat /etc/resolv.conf (%s).\n",
		         strerror(errno));
		goto err_close;
	}

	buffer = malloc(stat.st_size);
	if (buffer == NULL) {
		log_warn("Could not read /etc/resolv.conf (%s).\n",
		         "Not enough memory");
		goto err_close;
	}

	// Copy all file contents at once
	if (fread(buffer, stat.st_size, 1, file) != 1) {
		log_warn("Could not read /etc/resolv.conf.\n");
		goto err_free;
	}

	strcpy(ns1, "nameserver ");
	strncat(ns1, inet_ntoa(tunnel->ipv4.ns1_addr), 15);
	strcpy(ns2, "nameserver ");
	strncat(ns2, inet_ntoa(tunnel->ipv4.ns2_addr), 15);

	file = freopen("/etc/resolv.conf", "w", file);
	if (file == NULL) {
		log_warn("Could not reopen /etc/resolv.conf (%s).\n",
		         strerror(errno));
		goto err_free;
	}

	for (line = strtok(buffer, "\n"); line != NULL; line = strtok(NULL, "\n")) {
		if (strcmp(line, ns1) == 0) {
			log_debug("Deleting \"%s\" from /etc/resolv.conf.\n", ns1);
		} else if (strcmp(line, ns2) == 0) {
			log_debug("Deleting \"%s\" from /etc/resolv.conf.\n", ns1);
		} else {
			fputs(line, file);
			fputs("\n", file);
		}
	}

	ret = 0;

err_free:
	free(buffer);
err_close:
	fclose(file);

	return ret;
}