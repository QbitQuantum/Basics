void set_global_values(const char *configuration_file)
{
	if (!configuration_file)
		return;
	pmesg(LOG_INFO, __FILE__, __LINE__, "Loading configuration from '%s'\n", configuration_file);

	oph_server_params = hashtbl_create(HASHTBL_KEY_NUMBER, NULL);
	if (!oph_server_params)
		return;

	char tmp[OPH_MAX_STRING_SIZE];
	char *value;
	FILE *file = fopen(configuration_file, "r");
	if (file) {
		char key[OPH_MAX_STRING_SIZE], value2[OPH_MAX_STRING_SIZE];
		while (fgets(tmp, OPH_MAX_STRING_SIZE, file)) {
			if (strlen(tmp)) {
				tmp[strlen(tmp) - 1] = '\0';
				if (tmp[0] == OPH_COMMENT_MARK)
					continue;	// Skip possible commented lines
				value = strchr(tmp, OPH_SEPARATOR_KV[0]);
				if (value) {
					value++;
					snprintf(key, value - tmp, "%s", tmp);
					if (value[0]) {
						if (value[0] == OPH_SUBSTITUTION_MARK && !strncasecmp(value + 1, OPH_SERVER_LOCATION_STR, strlen(OPH_SERVER_LOCATION_STR))) {
							snprintf(value2, OPH_MAX_STRING_SIZE, "%s%s", oph_server_location, value + strlen(OPH_SERVER_LOCATION_STR) + 1);
							value = value2;
						}
						hashtbl_insert(oph_server_params, key, value);
					} else
						hashtbl_insert(oph_server_params, key, "");
					pmesg(LOG_DEBUG, __FILE__, __LINE__, "Read %s=%s\n", key, value);
				}
			}
		}
		fclose(file);
	}
	// Pre-process
	if ((value = hashtbl_get(oph_server_params, OPH_SERVER_CONF_TIMEOUT)))
		oph_server_timeout = strtol(value, NULL, 10);
	if ((value = hashtbl_get(oph_server_params, OPH_SERVER_CONF_INACTIVITY_TIMEOUT)))
		oph_server_inactivity_timeout = strtol(value, NULL, 10);
	if ((value = hashtbl_get(oph_server_params, OPH_SERVER_CONF_WORKFLOW_TIMEOUT)))
		oph_server_workflow_timeout = strtol(value, NULL, 10);
	if ((value = hashtbl_get(oph_server_params, OPH_SERVER_CONF_SERVER_FARM_SIZE)))
		oph_server_farm_size = (unsigned int) strtol(value, NULL, 10);
	if ((value = hashtbl_get(oph_server_params, OPH_SERVER_CONF_QUEUE_SIZE)))
		oph_server_queue_size = (unsigned int) strtol(value, NULL, 10);
	if ((value = hashtbl_get(oph_server_params, OPH_SERVER_CONF_AUTO_RETRY)))
		oph_auto_retry = (unsigned int) strtol(value, NULL, 10);
	if ((value = hashtbl_get(oph_server_params, OPH_SERVER_CONF_POLL_TIME)))
		oph_server_poll_time = (unsigned int) strtol(value, NULL, 10);
	if ((value = hashtbl_get(oph_server_params, OPH_SERVER_CONF_BASE_BACKOFF)))
		oph_base_backoff = (unsigned int) strtol(value, NULL, 10);
	if (!logfile && (value = hashtbl_get(oph_server_params, OPH_SERVER_CONF_LOGFILE))) {
		pmesg(LOG_INFO, __FILE__, __LINE__, "Selected log file '%s'\n", value);
		logfile = fopen(value, "a");
		if (logfile)
			set_log_file(logfile);
		// Redirect stdout and stderr to logfile
		if (!freopen(value, "a", stdout))
			pmesg(LOG_ERROR, __FILE__, __LINE__, "Error in redirect stdout to logfile\n");
		if (!freopen(value, "a", stderr))
			pmesg(LOG_ERROR, __FILE__, __LINE__, "Error in redirect stderr to logfile\n");
	}
	// Default values
	if (!oph_server_protocol && !(oph_server_protocol = hashtbl_get(oph_server_params, OPH_SERVER_CONF_PROTOCOL))) {
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_PROTOCOL, OPH_DEFAULT_PROTOCOL);
		oph_server_protocol = hashtbl_get(oph_server_params, OPH_SERVER_CONF_PROTOCOL);
	}
	if (!oph_server_host && !(oph_server_host = hashtbl_get(oph_server_params, OPH_SERVER_CONF_HOST))) {
		if (!gethostname(tmp, OPH_MAX_STRING_SIZE))
			hashtbl_insert(oph_server_params, OPH_SERVER_CONF_HOST, tmp);
		else
			hashtbl_insert(oph_server_params, OPH_SERVER_CONF_HOST, OPH_DEFAULT_HOST);
		oph_server_host = hashtbl_get(oph_server_params, OPH_SERVER_CONF_HOST);
	}
	if (!oph_server_port && !(oph_server_port = hashtbl_get(oph_server_params, OPH_SERVER_CONF_PORT))) {
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_PORT, OPH_DEFAULT_PORT);
		oph_server_port = hashtbl_get(oph_server_params, OPH_SERVER_CONF_PORT);
	}
	if (!(oph_server_cert = hashtbl_get(oph_server_params, OPH_SERVER_CONF_CERT))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_SERVER_CERT, oph_server_location);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_CERT, tmp);
		oph_server_cert = hashtbl_get(oph_server_params, OPH_SERVER_CONF_CERT);
	}
	if (!(oph_server_ca = hashtbl_get(oph_server_params, OPH_SERVER_CONF_CA))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_SERVER_CA, oph_server_location);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_CA, tmp);
		oph_server_ca = hashtbl_get(oph_server_params, OPH_SERVER_CONF_CA);
	}
	if (!(oph_server_password = hashtbl_get(oph_server_params, OPH_SERVER_CONF_CERT_PASSWORD))) {
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_CERT_PASSWORD, OPH_SERVER_PASSWORD);
		oph_server_password = hashtbl_get(oph_server_params, OPH_SERVER_CONF_CERT_PASSWORD);
	}
	if (!(oph_rmanager_conf_file = hashtbl_get(oph_server_params, OPH_SERVER_CONF_RMANAGER_CONF_FILE))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_RMANAGER_CONF_FILE, oph_server_location);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_RMANAGER_CONF_FILE, tmp);
		oph_rmanager_conf_file = hashtbl_get(oph_server_params, OPH_SERVER_CONF_RMANAGER_CONF_FILE);
	}
	if (!(oph_auth_location = hashtbl_get(oph_server_params, OPH_SERVER_CONF_AUTHZ_DIR))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_SERVER_AUTHZ, oph_server_location);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_AUTHZ_DIR, tmp);
		oph_auth_location = hashtbl_get(oph_server_params, OPH_SERVER_CONF_AUTHZ_DIR);
	}
	if (!(oph_txt_location = hashtbl_get(oph_server_params, OPH_SERVER_CONF_TXT_DIR))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_TXT_LOCATION, oph_server_location);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_TXT_DIR, tmp);
		oph_txt_location = hashtbl_get(oph_server_params, OPH_SERVER_CONF_TXT_DIR);
	}
	if (!(oph_web_server = hashtbl_get(oph_server_params, OPH_SERVER_CONF_WEB_SERVER))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_WEB_SERVER);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_WEB_SERVER, tmp);
		oph_web_server = hashtbl_get(oph_server_params, OPH_SERVER_CONF_WEB_SERVER);
	}
	if (!(oph_web_server_location = hashtbl_get(oph_server_params, OPH_SERVER_CONF_WEB_SERVER_LOCATION))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_WEB_SERVER_LOCATION);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_WEB_SERVER_LOCATION, tmp);
		oph_web_server_location = hashtbl_get(oph_server_params, OPH_SERVER_CONF_WEB_SERVER_LOCATION);
	}
	if (!(oph_operator_client = hashtbl_get(oph_server_params, OPH_SERVER_CONF_OPERATOR_CLIENT))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_OPERATOR_CLIENT);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_OPERATOR_CLIENT, tmp);
		oph_operator_client = hashtbl_get(oph_server_params, OPH_SERVER_CONF_OPERATOR_CLIENT);
	}
	if (!(oph_ip_target_host = hashtbl_get(oph_server_params, OPH_SERVER_CONF_IP_TARGET_HOST))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_IP_TARGET_HOST);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_IP_TARGET_HOST, tmp);
		oph_ip_target_host = hashtbl_get(oph_server_params, OPH_SERVER_CONF_IP_TARGET_HOST);
	}
	if (!(oph_subm_user = hashtbl_get(oph_server_params, OPH_SERVER_CONF_SUBM_USER))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_SUBM_USER);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_SUBM_USER, tmp);
		oph_subm_user = hashtbl_get(oph_server_params, OPH_SERVER_CONF_SUBM_USER);
	}
	if (!(oph_subm_user_publk = hashtbl_get(oph_server_params, OPH_SERVER_CONF_SUBM_USER_PUBLK))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_SUBM_USER_PUBLK);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_SUBM_USER_PUBLK, tmp);
		oph_subm_user_publk = hashtbl_get(oph_server_params, OPH_SERVER_CONF_SUBM_USER_PUBLK);
	}
	if (!(oph_subm_user_privk = hashtbl_get(oph_server_params, OPH_SERVER_CONF_SUBM_USER_PRIVK))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_SUBM_USER_PRIVK);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_SUBM_USER_PRIVK, tmp);
		oph_subm_user_privk = hashtbl_get(oph_server_params, OPH_SERVER_CONF_SUBM_USER_PRIVK);
	}
	if (!(oph_xml_operators = hashtbl_get(oph_server_params, OPH_SERVER_CONF_XML_URL))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_CLIENT_XML_URL);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_XML_URL, tmp);
		oph_xml_operators = hashtbl_get(oph_server_params, OPH_SERVER_CONF_XML_URL);
	}
	if (!(oph_xml_operator_dir = hashtbl_get(oph_server_params, OPH_SERVER_CONF_XML_DIR))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_SERVER_XML_EXT_PATH);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_XML_DIR, tmp);
		oph_xml_operator_dir = hashtbl_get(oph_server_params, OPH_SERVER_CONF_XML_DIR);
	}
	if (!(oph_user_notifier = hashtbl_get(oph_server_params, OPH_SERVER_CONF_NOTIFIER))) {
		snprintf(tmp, OPH_MAX_STRING_SIZE, OPH_USER_NOTIFIER);
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_NOTIFIER, tmp);
		oph_user_notifier = hashtbl_get(oph_server_params, OPH_SERVER_CONF_NOTIFIER);
	}
	if (!(oph_base_src_path = hashtbl_get(oph_server_params, OPH_SERVER_CONF_BASE_SRC_PATH))) {
		hashtbl_insert(oph_server_params, OPH_SERVER_CONF_BASE_SRC_PATH, OPH_BASE_SRC_PATH);
		oph_base_src_path = hashtbl_get(oph_server_params, OPH_SERVER_CONF_BASE_SRC_PATH);
	}


	oph_json_location = oph_web_server_location;	// Position of JSON Response will be the same of web server
}