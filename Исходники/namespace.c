bool arcan_verify_namespaces(bool report)
{
	bool working = true;

	if (report)
		arcan_warning("--- Verifying Namespaces: ---\n");

/* 1. check namespace mapping for holes */
	for (int i = 0; i < sizeof(
		namespaces.paths) / sizeof(namespaces.paths[0]); i++){
			if (namespaces.paths[i] == NULL){
				if (i != (int)log2(RESOURCE_SYS_LIBS)){
					working = false;
					if (report)
						arcan_warning("%s -- broken\n", lbls[i]);
					continue;
				}
			}

		if (report)
			arcan_warning("%s -- OK (%s)\n", lbls[i], namespaces.paths[i]);
	}

	if (report)
		arcan_warning("--- Namespace Verification Completed ---\n");

/* 2. missing; check permissions for each mounted space, i.e. we should be able
 * to write to state, we should be able to write to appl temporary etc.  also
 * check disk space for possible warning conditions (these should likely also
 * be emitted as system events)
 */

	if (working){
		char* toktmp = strdup(FRAMESERVER_MODESTRING);

/* modestring is static, atypestr can only be reduced in bytes used */
		if (!atypestr)
			atypestr = strdup(FRAMESERVER_MODESTRING);

		char* tokctx, (* tok) = strtok_r(toktmp, " ", &tokctx);
		if (tok && atypestr){
			char* base = arcan_expand_resource("", RESOURCE_SYS_BINS);
			size_t baselen = strlen(base);

/* fix for specialized "do we have default arcan_frameserver? then compact to
 * afsrv_ for archetype prefix" mode */
			size_t sfxlen = sizeof("arcan_frameserver") - 1;
			if (baselen >= sfxlen){
				if (strcmp(&base[baselen - sfxlen], "arcan_frameserver") == 0){
					const char* sfx = "afsrv";
					memcpy(&base[baselen - sfxlen], sfx, sizeof("afsrv"));
				}
			}

/* could / should do a more rigorous test of the corresponding afsrv, e.g.
 * executable, permission and linked shmif version */
			atypestr[0] = '\0';
			bool first = true;
			do{
				char* fn;
				char exp[2 + baselen + strlen(tok)];
				snprintf(exp, sizeof(exp), "%s_%s", base, tok);
				if (arcan_isfile(exp)){
					if (!first){
						strcat(atypestr, " ");
					}
					strcat(atypestr, tok);
					first = false;
				}
			} while ((tok = strtok_r(NULL, " ", &tokctx)));

			free(base);
		}
		free(toktmp);
	}

	return working;
}