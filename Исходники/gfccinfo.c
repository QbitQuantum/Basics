gfarm_error_t
add_line(char *line, int lineno)
{
	gfarm_error_t e;
	long port, ncpu, flags;
	int len, nhostaliases;
	char *s, *hostname, *architecture;
	char *hostaliases[MAX_HOSTALIASES + 1];

	/* parse architecture */
	line += strspn(line, space); /* skip space */
	len = strcspn(line, space);
	if (len == 0 || line[len] == '\0')
		return (invalid_input(lineno));
	line[len] = '\0';
	architecture = line;
	line += len + 1;
	s = validate_architecture(architecture);
	if (s != NULL) {
		fprintf(stderr,
		    "line %d: invalid character '%c' in architecture \"%s\"\n",
		    lineno, *s, architecture);
		return (GFARM_ERR_INVALID_ARGUMENT);
	}

	e = parse_string_long(&line, lineno, "ncpu", &ncpu);
	if (e != GFARM_ERR_NO_ERROR)
		return (e);

	/* parse hostname */
	line += strspn(line, space); /* skip space */
	len = strcspn(line, space);
	if (len == 0)
		return (invalid_input(lineno));
	hostname = line;
	if (line[len] == '\0') {
		line += len;
	} else {
		line[len] = '\0';
		line += len + 1;
	}
	s = validate_hostname(hostname);
	if (s != NULL) {
		fprintf(stderr,
		    "line %d: invalid character '%c' in hostname \"%s\"\n",
		    lineno, *s, hostname);
		return (GFARM_ERR_INVALID_ARGUMENT);
	}

	e = parse_string_long(&line, lineno, "port", &port);
	if (e != GFARM_ERR_NO_ERROR)
		return (e);

	e = parse_string_long(&line, lineno, "flags", &flags);
	if (e != GFARM_ERR_NO_ERROR)
		return (e);

	/* parse hostaliases */
	for (nhostaliases = 0;; nhostaliases++) {
		line += strspn(line, space); /* skip space */
		if (*line == '\0')
			break;
		len = strcspn(line, space);
		/* assert(len > 0); */
		if (nhostaliases >= MAX_HOSTALIASES) {
			fprintf(stderr, "line %d: "
			    "number of hostaliases exceeds %d\n",
			    lineno, nhostaliases);
			return (GFARM_ERR_INVALID_ARGUMENT);
		}
		hostaliases[nhostaliases] = line;
		if (line[len] == '\0') {
			line += len;
		} else {
			line[len] = '\0';
			line += len + 1;
		}
		s = validate_hostname(hostaliases[nhostaliases]);
		if (s != NULL) {
			fprintf(stderr, "line %d: "
			    "invalid character '%c' in hostalias \"%s\"\n",
			    lineno, *s, hostaliases[nhostaliases]);
			return (GFARM_ERR_INVALID_ARGUMENT);
		}
	}
	hostaliases[nhostaliases] = NULL;

	e = add_host(hostname, port, hostaliases, architecture, ncpu, flags);
	if (e != GFARM_ERR_NO_ERROR)
		fprintf(stderr, "line %d: %s\n",
		    lineno, gfarm_error_string(e));
	return (e);
}