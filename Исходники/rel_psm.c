static sql_rel *
rel_create_func(mvc *sql, dlist *qname, dlist *params, symbol *res, dlist *ext_name, dlist *body, int type, int lang, int replace)
{
	const char *fname = qname_table(qname);
	const char *sname = qname_schema(qname);
	sql_schema *s = NULL;
	sql_func *f = NULL;
	sql_subfunc *sf;
	dnode *n;
	list *type_list = NULL, *restype = NULL;
	int instantiate = (sql->emode == m_instantiate);
	int deps = (sql->emode == m_deps);
	int create = (!instantiate && !deps);
	bit vararg = FALSE;

	char is_table = (res && res->token == SQL_TABLE);
	char is_aggr = (type == F_AGGR);
	char is_func = (type != F_PROC);
	char is_loader = (type == F_LOADER);

	char *F = is_loader?"LOADER":(is_aggr?"AGGREGATE":(is_func?"FUNCTION":"PROCEDURE"));
	char *fn = is_loader?"loader":(is_aggr ? "aggregate" : (is_func ? "function" : "procedure"));
	char *KF = type==F_FILT?"FILTER ": type==F_UNION?"UNION ": "";
	char *kf = type == F_FILT ? "filter " : type == F_UNION ? "union " : "";

	assert(res || type == F_PROC || type == F_FILT || type == F_LOADER);

	if (is_table)
		type = F_UNION;

	if (STORE_READONLY && create) 
		return sql_error(sql, 06, SQLSTATE(42000) "Schema statements cannot be executed on a readonly database.");
			
	if (sname && !(s = mvc_bind_schema(sql, sname)))
		return sql_error(sql, 02, SQLSTATE(3F000) "CREATE %s%s: no such schema '%s'", KF, F, sname);
	if (s == NULL)
		s = cur_schema(sql);

	type_list = create_type_list(sql, params, 1);
	if ((sf = sql_bind_func_(sql->sa, s, fname, type_list, type)) != NULL && create) {
		if (replace) {
			sql_func *func = sf->func;
			int action = 0;
			if (!mvc_schema_privs(sql, s)) {
				return sql_error(sql, 02, SQLSTATE(42000) "CREATE OR REPLACE %s%s: access denied for %s to schema ;'%s'", KF, F, stack_get_string(sql, "current_user"), s->base.name);
			}
			if (mvc_check_dependency(sql, func->base.id, !IS_PROC(func) ? FUNC_DEPENDENCY : PROC_DEPENDENCY, NULL))
				return sql_error(sql, 02, SQLSTATE(42000) "CREATE OR REPLACE %s%s: there are database objects dependent on %s%s %s;", KF, F, kf, fn, func->base.name);
			if (!func->s) {
				return sql_error(sql, 02, SQLSTATE(42000) "CREATE OR REPLACE %s%s: not allowed to replace system %s%s %s;", KF, F, kf, fn, func->base.name);
			}

			if(mvc_drop_func(sql, s, func, action))
				return sql_error(sql, 02, SQLSTATE(HY001) MAL_MALLOC_FAIL);
			sf = NULL;
		} else {
			if (params) {
				char *arg_list = NULL;
				node *n;
				
				for (n = type_list->h; n; n = n->next) {
					char *tpe =  subtype2string((sql_subtype *) n->data);
					
					if (arg_list) {
						char *t = arg_list;
						arg_list = sql_message("%s, %s", arg_list, tpe);
						_DELETE(t);
						_DELETE(tpe);
					} else {
						arg_list = tpe;
					}
				}
				(void)sql_error(sql, 02, SQLSTATE(42000) "CREATE %s%s: name '%s' (%s) already in use", KF, F, fname, arg_list);
				_DELETE(arg_list);
				list_destroy(type_list);
				return NULL;
			} else {
				list_destroy(type_list);
				return sql_error(sql, 02, SQLSTATE(42000) "CREATE %s%s: name '%s' already in use", KF, F, fname);
			}
		}
	}
	list_destroy(type_list);
	if (create && !mvc_schema_privs(sql, s)) {
		return sql_error(sql, 02, SQLSTATE(42000) "CREATE %s%s: insufficient privileges "
				"for user '%s' in schema '%s'", KF, F,
				stack_get_string(sql, "current_user"), s->base.name);
	} else {
		char *q = QUERY(sql->scanner);
		list *l = NULL;

	 	if (params) {
			for (n = params->h; n; n = n->next) {
				dnode *an = n->data.lval->h;
				sql_add_param(sql, an->data.sval, &an->next->data.typeval);
			}
			l = sql->params;
			if (l && list_length(l) == 1) {
				sql_arg *a = l->h->data;

				if (strcmp(a->name, "*") == 0) {
					l = NULL;
					vararg = TRUE;
				}
			}
		}
		if (!l)
			l = sa_list(sql->sa);
		if (res) {
			restype = result_type(sql, res);
			if (!restype)
				return sql_error(sql, 01, SQLSTATE(42000) "CREATE %s%s: failed to get restype", KF, F);
		}
		if (body && lang > FUNC_LANG_SQL) {
			char *lang_body = body->h->data.sval;
			char *mod = 	
					(lang == FUNC_LANG_R)?"rapi":
					(lang == FUNC_LANG_C || lang == FUNC_LANG_CPP)?"capi":
					(lang == FUNC_LANG_J)?"japi":
					(lang == FUNC_LANG_PY)?"pyapi":
 					(lang == FUNC_LANG_MAP_PY)?"pyapimap":"unknown";
			sql->params = NULL;
			if (create) {
				f = mvc_create_func(sql, sql->sa, s, fname, l, restype, type, lang,  mod, fname, lang_body, (type == F_LOADER)?TRUE:FALSE, vararg, FALSE);
			} else if (!sf) {
				return sql_error(sql, 01, SQLSTATE(42000) "CREATE %s%s: R function %s.%s not bound", KF, F, s->base.name, fname );
			} /*else {
				sql_func *f = sf->func;
				f->mod = _STRDUP("rapi");
				f->imp = _STRDUP("eval");
				if (res && restype)
					f->res = restype;
				f->sql = 0;
				f->lang = FUNC_LANG_INT;
			}*/
		} else if (body) {
			sql_arg *ra = (restype && !is_table)?restype->h->data:NULL;
			list *b = NULL;
			sql_schema *old_schema = cur_schema(sql);

			if (create) { /* needed for recursive functions */
				q = query_cleaned(q);
				sql->forward = f = mvc_create_func(sql, sql->sa, s, fname, l, restype, type, lang, "user", q, q, FALSE, vararg, FALSE);
				GDKfree(q);
			}
			sql->session->schema = s;
			b = sequential_block(sql, (ra)?&ra->type:NULL, ra?NULL:restype, body, NULL, is_func);
			sql->forward = NULL;
			sql->session->schema = old_schema;
			sql->params = NULL;
			if (!b) 
				return NULL;
		
			/* check if we have a return statement */
			if (is_func && restype && !has_return(b)) {
				return sql_error(sql, 01, SQLSTATE(42000) "CREATE %s%s: missing return statement", KF, F);
			}
			if (!is_func && !restype && has_return(b)) {
				return sql_error(sql, 01, SQLSTATE(42000) "CREATE %s%s: procedures "
						"cannot have return statements", KF, F);
			}

			/* in execute mode we instantiate the function */
			if (instantiate || deps) {
				return rel_psm_block(sql->sa, b);
			}
		} else {
			char *fmod = qname_module(ext_name);
			char *fnme = qname_fname(ext_name);

			if (!fmod || !fnme)
				return NULL;
			sql->params = NULL;
			if (create) {
				q = query_cleaned(q);
				f = mvc_create_func(sql, sql->sa, s, fname, l, restype, type, lang, fmod, fnme, q, FALSE, vararg, FALSE);
				GDKfree(q);
			} else if (!sf) {
				return sql_error(sql, 01, SQLSTATE(42000) "CREATE %s%s: external name %s.%s not bound (%s.%s)", KF, F, fmod, fnme, s->base.name, fname );
			} else {
				sql_func *f = sf->func;
				if (!f->mod || strcmp(f->mod, fmod))
					f->mod = _STRDUP(fmod);
				if (!f->imp || strcmp(f->imp, fnme)) 
					f->imp = (f->sa)?sa_strdup(f->sa, fnme):_STRDUP(fnme);
				if(!f->mod || !f->imp) {
					_DELETE(f->mod);
					_DELETE(f->imp);
					return sql_error(sql, 02, SQLSTATE(HY001) "CREATE %s%s: could not allocate space", KF, F);
				}
				f->sql = 0; /* native */
				f->lang = FUNC_LANG_INT;
			}
		}
	}
	return rel_create_function(sql->sa, s->base.name, f);
}