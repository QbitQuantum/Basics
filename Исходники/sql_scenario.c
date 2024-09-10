str
SQLinitClient(Client c)
{
	mvc *m;
	str schema;
	str msg = MAL_SUCCEED;
	backend *be;
	bstream *bfd = NULL;
	stream *fd = NULL;
	static int maybeupgrade = 1;

#ifdef _SQL_SCENARIO_DEBUG
	mnstr_printf(GDKout, "#SQLinitClient\n");
#endif
	if (SQLinitialized == 0 && (msg = SQLprelude(NULL)) != MAL_SUCCEED)
		return msg;
	MT_lock_set(&sql_contextLock);
	/*
	 * Based on the initialization return value we can prepare a SQLinit
	 * string with all information needed to initialize the catalog
	 * based on the mandatory scripts to be executed.
	 */
	if (sqlinit) {		/* add sqlinit to the fdin stack */
		buffer *b = (buffer *) GDKmalloc(sizeof(buffer));
		size_t len = strlen(sqlinit);
		bstream *fdin;

		buffer_init(b, _STRDUP(sqlinit), len);
		fdin = bstream_create(buffer_rastream(b, "si"), b->len);
		bstream_next(fdin);
		MCpushClientInput(c, fdin, 0, "");
	}
	if (c->sqlcontext == 0) {
		m = mvc_create(c->idx, 0, SQLdebug, c->fdin, c->fdout);
		global_variables(m, "monetdb", "sys");
		if (isAdministrator(c) || strcmp(c->scenario, "msql") == 0)	/* console should return everything */
			m->reply_size = -1;
		be = (void *) backend_create(m, c);
	} else {
		be = c->sqlcontext;
		m = be->mvc;
		mvc_reset(m, c->fdin, c->fdout, SQLdebug, NR_GLOBAL_VARS);
		backend_reset(be);
	}
	if (m->session->tr)
		reset_functions(m->session->tr);
	/* pass through credentials of the user if not console */
	schema = monet5_user_set_def_schema(m, c->user);
	if (!schema) {
		_DELETE(schema);
		throw(PERMD, "SQLinitClient", "08004!schema authorization error");
	}
	_DELETE(schema);

	/*expect SQL text first */
	be->language = 'S';
	/* Set state, this indicates an initialized client scenario */
	c->state[MAL_SCENARIO_READER] = c;
	c->state[MAL_SCENARIO_PARSER] = c;
	c->state[MAL_SCENARIO_OPTIMIZE] = c;
	c->sqlcontext = be;

	initSQLreferences();
	/* initialize the database with predefined SQL functions */
	if (SQLnewcatalog == 0) {
		/* check whether table sys.systemfunctions exists: if
		 * it doesn't, this is probably a restart of the
		 * server after an incomplete initialization */
		sql_schema *s = mvc_bind_schema(m, "sys");
		sql_table *t = s ? mvc_bind_table(m, s, "systemfunctions") : NULL;
		if (t == NULL)
			SQLnewcatalog = 1;
	}
	if (SQLnewcatalog > 0) {
		char path[PATHLENGTH];
		str fullname;

		SQLnewcatalog = 0;
		maybeupgrade = 0;
		snprintf(path, PATHLENGTH, "createdb");
		slash_2_dir_sep(path);
		fullname = MSP_locate_sqlscript(path, 1);
		if (fullname) {
			str filename = fullname;
			str p, n;
			fprintf(stdout, "# SQL catalog created, loading sql scripts once\n");
			do {
				p = strchr(filename, PATH_SEP);
				if (p)
					*p = '\0';
				if ((n = strrchr(filename, DIR_SEP)) == NULL) {
					n = filename;
				} else {
					n++;
				}
				fprintf(stdout, "# loading sql script: %s\n", n);
				fd = open_rastream(filename);
				if (p)
					filename = p + 1;

				if (fd) {
					size_t sz;
					sz = getFileSize(fd);
					if (sz > (size_t) 1 << 29) {
						mnstr_destroy(fd);
						msg = createException(MAL, "createdb", "file %s too large to process", filename);
					} else {
						bfd = bstream_create(fd, sz == 0 ? (size_t) (128 * BLOCK) : sz);
						if (bfd && bstream_next(bfd) >= 0)
							msg = SQLstatementIntern(c, &bfd->buf, "sql.init", TRUE, FALSE, NULL);
						bstream_destroy(bfd);
					}
					if (m->sa)
						sa_destroy(m->sa);
					m->sa = NULL;
					if (msg)
						p = NULL;
				}
			} while (p);
			GDKfree(fullname);
		} else
			fprintf(stderr, "!could not read createdb.sql\n");
	} else {		/* handle upgrades */
		if (!m->sa)
			m->sa = sa_create();
		if (maybeupgrade)
			SQLupgrades(c,m);
		maybeupgrade = 0;
	}
	MT_lock_unset(&sql_contextLock);
	fflush(stdout);
	fflush(stderr);

	/* send error from create scripts back to the first client */
	if (msg) {
		error(c->fdout, msg);
		handle_error(m, c->fdout, 0);
		sqlcleanup(m, mvc_status(m));
	}
	return msg;
}