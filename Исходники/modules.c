/*
 *	Find a module on disk or in memory, and link to it.
 */
static module_list_t *linkto_module(const char *module_name,
		const char *cffilename, int cflineno)
{
	module_list_t *node;
	lt_dlhandle handle;
	char module_struct[256];
	char *p;

	/*
	 *	Look through the global module library list for the
	 *	named module.
	 */
	for (node = module_list; node != NULL; node = node->next) {
		/*
		 *	Found the named module.  Return it.
		 */
		if (strcmp(node->name, module_name) == 0)
			return node;

	}

	/*
	 *	Keep the handle around so we can dlclose() it.
	 */
	handle = lt_dlopenext(module_name);
	if (handle == NULL) {
		radlog(L_ERR|L_CONS, "%s[%d] Failed to link to module '%s':"
				" %s\n", cffilename, cflineno, module_name, lt_dlerror());
		return NULL;
	}

	/* make room for the module type */
	node = (module_list_t *) rad_malloc(sizeof(module_list_t));

	/* fill in the module structure */
	node->next = NULL;
	node->handle = handle;
	strNcpy(node->name, module_name, sizeof(node->name));
	
	/*
	 *	Link to the module's rlm_FOO{} module structure.
	 */
	/* module_name has the version embedded; strip it. */
	strcpy(module_struct, module_name);
	p = strrchr(module_struct, '-');
	if (p)
		*p = '\0';
	node->module = (module_t *) lt_dlsym(node->handle, module_struct);
	if (!node->module) {
		radlog(L_ERR|L_CONS, "%s[%d] Failed linking to "
				"%s structure in %s: %s\n",
				cffilename, cflineno,
				module_name, cffilename, lt_dlerror());
		lt_dlclose(node->handle);	/* ignore any errors */
		free(node);
		return NULL;
	}
	
	/* call the modules initialization */
	if (node->module->init && (node->module->init)() < 0) {
		radlog(L_ERR|L_CONS, "%s[%d] Module initialization failed.\n",
				cffilename, cflineno);
		lt_dlclose(node->handle);	/* ignore any errors */
		free(node);
		return NULL;
	}

	DEBUG("Module: Loaded %s ", node->module->name);

	node->next = module_list;
	module_list = node;

	return node;
}