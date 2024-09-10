static int
sc_card_sm_load(struct sc_card *card, const char *module_path, const char *in_module)
{
	struct sc_context *ctx = NULL;
	int rv = SC_ERROR_INTERNAL;
	char *module = NULL;
#ifdef _WIN32
	char temp_path[PATH_MAX];
	int temp_len;
	long rc;
	HKEY hKey;
	const char path_delim = '\\';
#else
	const char path_delim = '/';
#endif

	assert(card != NULL);
	ctx = card->ctx;
	SC_FUNC_CALLED(ctx, SC_LOG_DEBUG_NORMAL);
	if (!in_module)
		return sc_card_sm_unload(card);

#ifdef _WIN32
	if (!module_path) {
		rc = RegOpenKeyExA( HKEY_CURRENT_USER, "Software\\OpenSC Project\\OpenSC", 0, KEY_QUERY_VALUE, &hKey );
		if( rc == ERROR_SUCCESS ) {
			temp_len = PATH_MAX;
			rc = RegQueryValueExA( hKey, "SmDir", NULL, NULL, (LPBYTE) temp_path, &temp_len);
			if( (rc == ERROR_SUCCESS) && (temp_len < PATH_MAX) )
				module_path = temp_path;
			RegCloseKey( hKey );
		}
	}
	if (!module_path) {
		rc = RegOpenKeyExA( HKEY_LOCAL_MACHINE, "Software\\OpenSC Project\\OpenSC", 0, KEY_QUERY_VALUE, &hKey );
		if( rc == ERROR_SUCCESS ) {
			temp_len = PATH_MAX;
			rc = RegQueryValueExA( hKey, "SmDir", NULL, NULL, (LPBYTE) temp_path, &temp_len);
			if(rc == ERROR_SUCCESS && temp_len < PATH_MAX)
				module_path = temp_path;
			RegCloseKey( hKey );
		}
	}
#endif
	sc_debug(ctx, SC_LOG_DEBUG_NORMAL, "SM module '%s' located in '%s'", in_module, module_path);
	if (module_path)   {
		int sz = strlen(in_module) + strlen(module_path) + 3;
		module = malloc(sz);
		if (module)
			snprintf(module, sz, "%s%c%s", module_path, path_delim, in_module);
	}
	else   {
		module = strdup(in_module);
	}

	if (!module)
		return SC_ERROR_OUT_OF_MEMORY;

	sc_log(ctx, "try to load SM module '%s'", module);
	do  {
		struct sm_module_operations *mod_ops = &card->sm_ctx.module.ops;
		void *mod_handle;

		card->sm_ctx.module.handle = sc_dlopen(module);
		if (!card->sm_ctx.module.handle)   {
			sc_log(ctx, "cannot open dynamic library '%s': %s", module, sc_dlerror());
			break;
		}
		mod_handle = card->sm_ctx.module.handle;

		mod_ops->initialize = sc_dlsym(mod_handle, "initialize");
		if (!mod_ops->initialize)   {
			sc_log(ctx, "SM handler 'initialize' not exported: %s", sc_dlerror());
			break;
		}

		mod_ops->get_apdus  = sc_dlsym(mod_handle, "get_apdus");
		if (!mod_ops->get_apdus)   {
			sc_log(ctx, "SM handler 'get_apdus' not exported: %s", sc_dlerror());
			break;
		}

		mod_ops->finalize  = sc_dlsym(mod_handle, "finalize");
		if (!mod_ops->finalize)
			sc_log(ctx, "SM handler 'finalize' not exported -- ignored");

		mod_ops->module_init  = sc_dlsym(mod_handle, "module_init");
		if (!mod_ops->module_init)
			sc_log(ctx, "SM handler 'module_init' not exported -- ignored");

		mod_ops->module_cleanup  = sc_dlsym(mod_handle, "module_cleanup");
		if (!mod_ops->module_cleanup)
			sc_log(ctx, "SM handler 'module_cleanup' not exported -- ignored");

		mod_ops->test  = sc_dlsym(mod_handle, "test");
		if (mod_ops->test)
			sc_log(ctx, "SM handler 'test' not exported -- ignored");

		rv = 0;
		break;
	} while(0);

	if (rv)
		sc_card_sm_unload(card);

	card->sm_ctx.sm_mode = SM_MODE_ACL;
	if (module)
		free(module);

	SC_FUNC_RETURN(ctx, SC_LOG_DEBUG_VERBOSE, rv);
}