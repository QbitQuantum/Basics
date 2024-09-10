static int config_connection_request(struct config_connection *conn,
				     const char *const *args)
{
	struct config_export_context *ctx;
	struct master_service_settings_output output;
	struct config_filter filter;
	const char *path, *error, *module, *const *wanted_modules;
	ARRAY(const char *) modules;
	bool is_master = FALSE;

	/* [<args>] */
	t_array_init(&modules, 4);
	memset(&filter, 0, sizeof(filter));
	for (; *args != NULL; args++) {
		if (strncmp(*args, "service=", 8) == 0)
			filter.service = *args + 8;
		else if (strncmp(*args, "module=", 7) == 0) {
			module = *args + 7;
			if (strcmp(module, "master") == 0)
				is_master = TRUE;
			array_append(&modules, &module, 1);
		} else if (strncmp(*args, "lname=", 6) == 0)
			filter.local_name = *args + 6;
		else if (strncmp(*args, "lip=", 4) == 0) {
			if (net_addr2ip(*args + 4, &filter.local_net) == 0) {
				filter.local_bits =
					IPADDR_IS_V4(&filter.local_net) ?
					32 : 128;
			}
		} else if (strncmp(*args, "rip=", 4) == 0) {
			if (net_addr2ip(*args + 4, &filter.remote_net) == 0) {
				filter.remote_bits =
					IPADDR_IS_V4(&filter.remote_net) ?
					32 : 128;
			}
		}
	}
	array_append_zero(&modules);
	wanted_modules = array_count(&modules) == 1 ? NULL :
		array_idx(&modules, 0);

	if (is_master) {
		/* master reads configuration only when reloading settings */
		path = master_service_get_config_path(master_service);
		if (config_parse_file(path, TRUE, NULL, &error) <= 0) {
			o_stream_nsend_str(conn->output,
				t_strconcat("\nERROR ", error, "\n", NULL));
			config_connection_destroy(conn);
			return -1;
		}
	}

	o_stream_cork(conn->output);

	ctx = config_export_init(wanted_modules, CONFIG_DUMP_SCOPE_SET, 0,
				 config_request_output, conn->output);
	config_export_by_filter(ctx, &filter);
	config_export_get_output(ctx, &output);

	if (output.specific_services != NULL) {
		const char *const *s;

		for (s = output.specific_services; *s != NULL; s++) {
			o_stream_nsend_str(conn->output,
				t_strdup_printf("service=%s\t", *s));
		}
	}
	if (output.service_uses_local)
		o_stream_nsend_str(conn->output, "service-uses-local\t");
	if (output.service_uses_remote)
		o_stream_nsend_str(conn->output, "service-uses-remote\t");
	if (output.used_local)
		o_stream_nsend_str(conn->output, "used-local\t");
	if (output.used_remote)
		o_stream_nsend_str(conn->output, "used-remote\t");
	o_stream_nsend_str(conn->output, "\n");

	if (config_export_finish(&ctx) < 0) {
		config_connection_destroy(conn);
		return -1;
	}
	o_stream_nsend_str(conn->output, "\n");
	o_stream_uncork(conn->output);
	return 0;
}