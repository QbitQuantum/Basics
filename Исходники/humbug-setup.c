int readHumbugConfig( void ){
	FILE *file;
	char conf_buf[512];

	file = fopen(HBG_CONF_FILE, "r");

	if (NULL == file) {
		fprintf( stdout, "Can`t open config file: %s\n", strerror(errno));
		return -1;
	}

	while (NULL != fgets(conf_buf, 512, file)) {

		if (('#' == *conf_buf) || ('=' == *conf_buf) || ('\n' == *conf_buf)
				|| (';' == *conf_buf) || ('\r' == *conf_buf)) {
			continue;
		}

		if ('\n' == conf_buf[strlen(conf_buf) - 1]) {
			conf_buf[strlen(conf_buf) - 1] = '\0';
		}

		if (strlen(conf_buf) <=2  || '=' == conf_buf[strlen(conf_buf) - 1] || NULL == strchr(conf_buf, '=')) {
			continue;
		}

		char *variable, value[256], *tmp_value, *p;

		variable = strtok(conf_buf, "=");
		tmp_value = strtok(NULL, "=");

		p = value;
		while (*tmp_value) {
			if (*tmp_value == ' ' || *tmp_value == '\t') {
				tmp_value++;
			} else {
				*p++ = *tmp_value++;
			}
		}
		*p = 0;

		if (0 == strncmp("port", variable, 4)) {
			strcpy(params->astPortVal, value);
		} else if (0 == strncmp("address", variable, 7)) {
			strcpy(params->astIpVal, value);
		} else if (0 == strncmp("user", variable, 4)) {
			strcpy(params->astUserVal, value);
		} else if (0 == strncmp("secret", variable, 6)) {
			strcpy(params->astPassVal, value);
		}else if (0 == strncmp("h_port", variable, 6)) {
			strcpy(params->humbugPort, value);
		} else if (0 == strncmp("h_host", variable, 6)) {
			strcpy(params->humbugHost, value);
		}else if (0 == strncmp("h_apikey", variable, 8)) {
			strcpy(params->humbugApikey, value);
		}else if (0 == strncmp("h_read", variable, 6)) {
			char *pEvent;
			params->eventsSize = 0;
			if ( NULL != (pEvent = strtok(value, ",")) ) {
				strcpy( params->events[params->eventsSize++], pEvent );
				while ( NULL != ( pEvent = strtok(NULL, ",")) ) {
					strcpy( params->events[params->eventsSize++], pEvent );
				}
			}
		}else if (0 == strncmp("encrypted", variable, 9)) {
			if (0 == strncasecmp("yes", value, 3)) {
				params->encrypted = 1;
			} else {
				params->encrypted = 0;
			}
		} else if (0 == strncmp("h_key", variable, 5)) {
			strcpy(params->humbugKey, value);
		}else if ( 0 == strncmp("log_file", variable, 8) ) {
			strcpy(params->log_file, value);
		}else if (0 == strncmp("debug_level", variable, 11)) {
			params->debug_level = atoi(value);
		}

	}

	fclose(file);
	return 0;
}