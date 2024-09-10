static void process_config_file(sc_context_t *ctx, struct _sc_ctx_options *opts)
{
	int i, r, count = 0;
	scconf_block **blocks;
	const char *conf_path = NULL;
	const char *debug = NULL;
#ifdef _WIN32
	char temp_path[PATH_MAX];
	DWORD temp_len;
	long rc;
	HKEY hKey;
#endif

	/* Takes effect even when no config around */
	debug = getenv("OPENSC_DEBUG");
	if (debug)
		ctx->debug = atoi(debug);

	memset(ctx->conf_blocks, 0, sizeof(ctx->conf_blocks));
#ifdef _WIN32
	conf_path = getenv("OPENSC_CONF");
	if (!conf_path) {
		rc = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\OpenSC Project\\OpenSC", 0, KEY_QUERY_VALUE, &hKey);
		if (rc == ERROR_SUCCESS) {
			temp_len = PATH_MAX;
			rc = RegQueryValueEx( hKey, "ConfigFile", NULL, NULL, (LPBYTE) temp_path, &temp_len);
			if ((rc == ERROR_SUCCESS) && (temp_len < PATH_MAX))
				conf_path = temp_path;
			RegCloseKey(hKey);
		}
	}

	if (!conf_path) {
		rc = RegOpenKeyExA( HKEY_LOCAL_MACHINE, "Software\\OpenSC Project\\OpenSC", 0, KEY_QUERY_VALUE, &hKey );
		if (rc == ERROR_SUCCESS) {
			temp_len = PATH_MAX;
			rc = RegQueryValueEx( hKey, "ConfigFile", NULL, NULL, (LPBYTE) temp_path, &temp_len);
			if ((rc == ERROR_SUCCESS) && (temp_len < PATH_MAX))
				conf_path = temp_path;
			RegCloseKey(hKey);
		}
	}

	if (!conf_path) {
		sc_log(ctx, "process_config_file doesn't find opensc config file. Please set the registry key.");
		return;
	}

#else
	conf_path = getenv("OPENSC_CONF");
	if (!conf_path)
		conf_path = OPENSC_CONF_PATH;
#endif
	ctx->conf = scconf_new(conf_path);
	if (ctx->conf == NULL)
		return;
	r = scconf_parse(ctx->conf);
#ifdef OPENSC_CONFIG_STRING
	/* Parse the string if config file didn't exist */
	if (r < 0)
		r = scconf_parse_string(ctx->conf, OPENSC_CONFIG_STRING);
#endif
	if (r < 1) {
		/* A negative return value means the config file isn't
		 * there, which is not an error. Nevertheless log this
		 * fact. */
		if (r < 0)
			sc_log(ctx, "scconf_parse failed: %s", ctx->conf->errmsg);
		else
			sc_log(ctx, "scconf_parse failed: %s", ctx->conf->errmsg);
		scconf_free(ctx->conf);
		ctx->conf = NULL;
		return;
	}
	blocks = scconf_find_blocks(ctx->conf, NULL, "app", ctx->app_name);
	if (blocks[0])
		ctx->conf_blocks[count++] = blocks[0];
	free(blocks);
	if (strcmp(ctx->app_name, "default") != 0) {
		blocks = scconf_find_blocks(ctx->conf, NULL, "app", "default");
		if (blocks[0])
			ctx->conf_blocks[count] = blocks[0];
		free(blocks);
	}
	/* Above we add 2 blocks at most, but conf_blocks has 3 elements,
	 * so at least one is NULL */
	for (i = 0; ctx->conf_blocks[i]; i++)
		load_parameters(ctx, ctx->conf_blocks[i], opts);
}