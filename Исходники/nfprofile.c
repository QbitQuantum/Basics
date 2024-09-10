static profile_param_info_t *ParseParams (char *profile_datadir) {
struct stat stat_buf;
char line[512], path[MAXPATHLEN], *p, *q, *s;
profile_param_info_t *profile_list;
profile_param_info_t **list = &profile_list;

	profile_list = NULL;
	while ( ( fgets(line, 512, stdin) != NULL )) {
		LogInfo("Process line '%s'\n", line);
		line[511] = '\0';

		if ( *list == NULL ) 
			*list = (profile_param_info_t *)malloc(sizeof(profile_param_info_t));
		// else we come from a continue statement with illegal data - overwrite

		if ( !*list) {
			LogError("malloc() error in %s line %d: %s\n", __FILE__, __LINE__, strerror(errno) );
			return NULL;
		}

		(*list)->next 		  = NULL;
		(*list)->profilegroup = NULL;
		(*list)->profilename  = NULL;
		(*list)->channelname  = NULL;
		(*list)->channel_sourcelist = NULL;
		(*list)->profiletype  = 0;

		// delete '\n' at the end of line
		// format of stdin config line:
		// <profilegroup>#<profilename>#<profiletype>#<channelname>#<channel_sourcelist>
		p = strchr(line, '\n');
		if ( p ) *p = '\0';

		q = line;
		p = strchr(q, '#');
		if ( p ) 
			*p = '\0';

		s = line;

		// savety check: if no separator found loop to next line
		if ( !p ) {
			LogError("Incomplete line - channel skipped.\n");
			continue;
		}

		q = p;
		q++;

		p = strchr(q, '#');
		if ( p ) 
			*p = '\0';

		snprintf(path, MAXPATHLEN-1, "%s/%s/%s", profile_datadir, s, q);
		path[MAXPATHLEN-1] = '\0';
		if ( stat(path, &stat_buf) || !S_ISDIR(stat_buf.st_mode) ) {
			LogError("profile '%s' not found in group %s. Skipped.\n", q, s);
			continue;
		}

		(*list)->profilegroup = strdup(s);
		(*list)->profilename  = strdup(q);

		// savety check: if no separator found loop to next line
		if ( !p ) {
			LogError("Incomplete line - channel skipped.\n");
			continue;
		}

		q = p;
		q++;

		p = strchr(q, '#');
		if ( p ) 
			*p = '\0';

		s = q;
		while ( *s ) {
			if ( *s < '0' || *s > '9' ) {
				LogError("Not a valid number: %s\n", q);
				s = NULL;
				break;
			}
			s++;
		}
		if ( s == NULL )
			continue;

		(*list)->profiletype = (int)strtol(q, (char **)NULL, 10);

		// savety check: if no separator found loop to next line
		if ( !p ) {
			LogError("Incomplete line - channel skipped.\n");
			continue;
		}

		q = p;
		q++;

		p = strchr(q, '#');
		if ( p ) 
			*p = '\0';

		snprintf(path, MAXPATHLEN-1, "%s/%s/%s/%s", profile_datadir, (*list)->profilegroup, (*list)->profilename, q);
		path[MAXPATHLEN-1] = '\0';
		if ( stat(path, &stat_buf) || !S_ISDIR(stat_buf.st_mode) ) {
			LogError("channel '%s' in profile '%s' not found. Skipped.\n", q, (*list)->profilename);
			continue;
		}

		(*list)->channelname = strdup(q);

		if ( !p ) {
			LogError("Incomplete line - Skipped.\n");
			continue;
		}

		q = p;
		q++;

		p = strchr(q, '#');
		if ( p ) 
			*p = '\0';

		// Skip leading '| chars
		while ( *q && *q == '|' ) {
			q++;
		}
		s = q;

		// if q is already empty ( '\0' ) loop is not processed
		while ( *s ) {
			// as s[0] is not '\0' s[1] may be '\0' but still valid and in range
			if ( s[0] == '|' && s[1] == '|' ) {
				char *t = s;
				t++;
				while ( *t ) {	// delete this empty channel name
					t[0] = t[1];
					t++;
				}
			} else
				s++;
		}
		// we have no doublicate '|' here any more
		// check if last char is an extra '|' 
		if ( *q && (q[strlen(q)-1] == '|') )
			q[strlen(q)-1] = '\0';

		if ( *q && (strcmp(q, "*") != 0) ) 
			(*list)->channel_sourcelist = strdup(q);

		list = &((*list)->next);
	}

	if ( *list != NULL ) {
		free(*list);
		*list = NULL;
	}

	if ( ferror(stdin) ) {
		LogError("fgets() error: %s", strerror(errno));
		return NULL;
	}

	return profile_list;

} // End of ParseParams