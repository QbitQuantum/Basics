static bool finalize_join(void) {
	char *name = xstrdup(get_value(data, "Name"));
	if(!name) {
		fprintf(stderr, "No Name found in invitation!\n");
		return false;
	}

	if(!check_id(name)) {
		fprintf(stderr, "Invalid Name found in invitation: %s!\n", name);
		return false;
	}

	if(!netname)
		netname = grep(data, "NetName");

	bool ask_netname = false;
	char temp_netname[32];

make_names:
	if(!confbasegiven) {
		free(confbase);
		confbase = NULL;
	}

	make_names(false);

	free(tinc_conf);
	free(hosts_dir);

	xasprintf(&tinc_conf, "%s" SLASH "tinc.conf", confbase);
	xasprintf(&hosts_dir, "%s" SLASH "hosts", confbase);

	if(!access(tinc_conf, F_OK)) {
		fprintf(stderr, "Configuration file %s already exists!\n", tinc_conf);
		if(confbasegiven)
			return false;

		// Generate a random netname, ask for a better one later.
		ask_netname = true;
		snprintf(temp_netname, sizeof temp_netname, "join_%x", rand());
		netname = temp_netname;
		goto make_names;
	}	

	if(mkdir(confbase, 0777) && errno != EEXIST) {
		fprintf(stderr, "Could not create directory %s: %s\n", confbase, strerror(errno));
		return false;
	}

	if(mkdir(hosts_dir, 0777) && errno != EEXIST) {
		fprintf(stderr, "Could not create directory %s: %s\n", hosts_dir, strerror(errno));
		return false;
	}

	FILE *f = fopen(tinc_conf, "w");
	if(!f) {
		fprintf(stderr, "Could not create file %s: %s\n", tinc_conf, strerror(errno));
		return false;
	}

	fprintf(f, "Name = %s\n", name);

	char filename[PATH_MAX];
	snprintf(filename, sizeof filename, "%s" SLASH "%s", hosts_dir, name);
	FILE *fh = fopen(filename, "w");
	if(!fh) {
		fprintf(stderr, "Could not create file %s: %s\n", filename, strerror(errno));
		fclose(f);
		return false;
	}

	// Filter first chunk on approved keywords, split between tinc.conf and hosts/Name
	// Other chunks go unfiltered to their respective host config files
	const char *p = data;
	char *l, *value;

	while((l = get_line(&p))) {
		// Ignore comments
		if(*l == '#')
			continue;

		// Split line into variable and value
		int len = strcspn(l, "\t =");
		value = l + len;
		value += strspn(value, "\t ");
		if(*value == '=') {
			value++;
			value += strspn(value, "\t ");
		}
		l[len] = 0;

		// Is it a Name?
		if(!strcasecmp(l, "Name"))
			if(strcmp(value, name))
				break;
			else
				continue;
		else if(!strcasecmp(l, "NetName"))
			continue;

		// Check the list of known variables
		bool found = false;
		int i;
		for(i = 0; variables[i].name; i++) {
			if(strcasecmp(l, variables[i].name))
				continue;
			found = true;
			break;
		}

		// Ignore unknown and unsafe variables
		if(!found) {
			fprintf(stderr, "Ignoring unknown variable '%s' in invitation.\n", l);
			continue;
		} else if(!(variables[i].type & VAR_SAFE)) {
			fprintf(stderr, "Ignoring unsafe variable '%s' in invitation.\n", l);
			continue;
		}

		// Copy the safe variable to the right config file
		fprintf(variables[i].type & VAR_HOST ? fh : f, "%s = %s\n", l, value);
	}

	fclose(f);

	while(l && !strcasecmp(l, "Name")) {
		if(!check_id(value)) {
			fprintf(stderr, "Invalid Name found in invitation.\n");
			return false;
		}

		if(!strcmp(value, name)) {
			fprintf(stderr, "Secondary chunk would overwrite our own host config file.\n");
			return false;
		}

		snprintf(filename, sizeof filename, "%s" SLASH "%s", hosts_dir, value);
		f = fopen(filename, "w");

		if(!f) {
			fprintf(stderr, "Could not create file %s: %s\n", filename, strerror(errno));
			return false;
		}

		while((l = get_line(&p))) {
			if(!strcmp(l, "#---------------------------------------------------------------#"))
				continue;
			int len = strcspn(l, "\t =");
			if(len == 4 && !strncasecmp(l, "Name", 4)) {
				value = l + len;
				value += strspn(value, "\t ");
				if(*value == '=') {
					value++;
					value += strspn(value, "\t ");
				}
				l[len] = 0;
				break;
			}

			fputs(l, f);
			fputc('\n', f);
		}

		fclose(f);
	}

	// Generate our key and send a copy to the server
	ecdsa_t *key = ecdsa_generate();
	if(!key)
		return false;

	char *b64key = ecdsa_get_base64_public_key(key);
	if(!b64key)
		return false;

	snprintf(filename, sizeof filename, "%s" SLASH "ed25519_key.priv", confbase);
	f = fopenmask(filename, "w", 0600);
	if(!f)
		return false;

	if(!ecdsa_write_pem_private_key(key, f)) {
		fprintf(stderr, "Error writing private key!\n");
		ecdsa_free(key);
		fclose(f);
		return false;
	}

	fclose(f);

	fprintf(fh, "Ed25519PublicKey = %s\n", b64key);

	sptps_send_record(&sptps, 1, b64key, strlen(b64key));
	free(b64key);
	ecdsa_free(key);

	check_port(name);

ask_netname:
	if(ask_netname && tty) {
		fprintf(stderr, "Enter a new netname: ");
		if(!fgets(line, sizeof line, stdin)) {
			fprintf(stderr, "Error while reading stdin: %s\n", strerror(errno));
			return false;
		}
		if(!*line || *line == '\n')
			goto ask_netname;

		line[strlen(line) - 1] = 0;

		char newbase[PATH_MAX];
		snprintf(newbase, sizeof newbase, CONFDIR SLASH "tinc" SLASH "%s", line);
		if(rename(confbase, newbase)) {
			fprintf(stderr, "Error trying to rename %s to %s: %s\n", confbase, newbase, strerror(errno));
			goto ask_netname;
		}

		netname = line;
		make_names(false);
	}

	fprintf(stderr, "Configuration stored in: %s\n", confbase);

	return true;
}