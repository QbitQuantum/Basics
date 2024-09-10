static int
hostent_read_snapshot_func(struct hostent *ht, char *line)
{
	StringList *sl1, *sl2;
	char *s, *ps, *ts;
	int i, rv;

#ifdef DEBUG
	printf("1 line read from snapshot:\n%s\n", line);
#endif

	rv = 0;
	i = 0;
	sl1 = sl2 = NULL;
	ps = line;
	memset(ht, 0, sizeof(struct hostent));
	while ((s = strsep(&ps, " ")) != NULL) {
		switch (i) {
		case 0:
			ht->h_name = strdup(s);
			ATF_REQUIRE(ht->h_name != NULL);
			break;

		case 1:
			ht->h_addrtype = (int)strtol(s, &ts, 10);
			if (*ts != '\0')
				goto fin;
			break;

		case 2:
			ht->h_length = (int)strtol(s, &ts, 10);
			if (*ts != '\0')
				goto fin;
			break;

		case 3:
			if (sl1 == NULL) {
				if (strcmp(s, "(null)") == 0)
					return (0);

				sl1 = sl_init();
				ATF_REQUIRE(sl1 != NULL);

				if (strcmp(s, "noaliases") != 0) {
					ts = strdup(s);
					ATF_REQUIRE(ts != NULL);
					sl_add(sl1, ts);
				}
			} else {
				if (strcmp(s, ":") == 0)
					++i;
				else {
					ts = strdup(s);
					ATF_REQUIRE(ts != NULL);
					sl_add(sl1, ts);
				}
			}
			break;

		case 4:
			if (sl2 == NULL) {
				if (strcmp(s, "(null)") == 0)
					return (0);

				sl2 = sl_init();
				ATF_REQUIRE(sl2 != NULL);

				if (strcmp(s, "noaddrs") != 0) {
					ts = calloc(1, ht->h_length);
					ATF_REQUIRE(ts != NULL);
					rv = hostent_read_snapshot_addr(s,
					    (unsigned char *)ts,
					    ht->h_length);
					sl_add(sl2, ts);
					if (rv != 0)
						goto fin;
				}
			} else {
				ts = calloc(1, ht->h_length);
				ATF_REQUIRE(ts != NULL);
				rv = hostent_read_snapshot_addr(s,
				    (unsigned char *)ts, ht->h_length);
				sl_add(sl2, ts);
				if (rv != 0)
					goto fin;
			}
			break;
		default:
			break;
		}

		if (i != 3 && i != 4)
			++i;
	}

fin:
	if (sl1 != NULL) {
		sl_add(sl1, NULL);
		ht->h_aliases = sl1->sl_str;
	}
	if (sl2 != NULL) {
		sl_add(sl2, NULL);
		ht->h_addr_list = sl2->sl_str;
	}

	if ((i != 4) || (rv != 0)) {
		free_hostent(ht);
		memset(ht, 0, sizeof(struct hostent));
		return (-1);
	}

	/* NOTE: is it a dirty hack or not? */
	free(sl1);
	free(sl2);
	return (0);
}