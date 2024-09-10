static bcspec_t *
bcspec_new(plugin_t * plt, octet_t * spec)
{
	octet_t         oct;
	bcspec_t       *bcs = 0;
	plugin_t       *p;
	int             n;

	/*
	 * two parts name ":" typespec 
	 */
	if ((n = octchr(spec, ':')) < 0) {
		oct_print( LOG_ERR,
		    "Error in boundary condition specification", spec);
		return 0;
	}

	oct.len = spec->len - n - 1;
	oct.val = spec->val + n + 1;
	spec->len = n;

	if ((p = plugin_match(plt, spec)) == 0) {
		traceLog(LOG_ERR,"Doesn't match any known plugin",spec);
		return 0;
	}

	bcs = (bcspec_t *) Calloc(1,sizeof(bcspec_t));

	bcs->plugin = p;
	bcs->name = oct2strdup(spec, 0);
	bcs->spec = octdup(&oct);

	return bcs;
}