static int mod_vhost_ldap_translate_name(request_rec *r)
{
	mod_vhost_ldap_request_t *reqc = NULL;
	mod_vhost_ldap_config_t *conf =
	(mod_vhost_ldap_config_t *)ap_get_module_config(r->server->module_config, &vhost_ldap_ng_module);
#if (AP_SERVER_MAJORVERSION_NUMBER == 2) && (AP_SERVER_MINORVERSION_NUMBER <= 2)
	core_server_config *core =
		(core_server_config *)ap_get_module_config(r->server->module_config, &core_module);
#endif	
	LDAP *ld = NULL;
	char *realfile = NULL;
	char *myfilter = NULL;
	alias_t *alias = NULL, *cursor = NULL;
	int i = 0, ret = 0;
	apr_table_t *e;
	LDAPMessage *ldapmsg = NULL, *vhostentry = NULL;
	
	if (conf->enabled != MVL_ENABLED || !conf->url || !r->hostname){
		ap_log_rerror(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, 0, r, 
				"[mod_vhost_ldap_ng.c] Module disabled");
		return DECLINED;
	}

	//Search in cache
	reqc = (mod_vhost_ldap_request_t *)get_from_requestscache(r);
	if(!reqc){
		ap_log_rerror(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, 0, r, 
				"[mod_vhost_ldap_ng.c] Cannot resolve data from cache");
		reqc = apr_pcalloc(vhost_ldap_pool, sizeof(mod_vhost_ldap_request_t));
	}
	if (reqc->expires < apr_time_now()){
		//Search ldap
		//TODO: Create a function
		while((ret = ldapconnect(&ld, conf)) != 0 && i<2){
			i++;
			ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, r, 
				"[mod_vhost_ldap_ng.c] ldapconnect: %s", ldap_err2string(ret));
		}
		if(i == 2){
			conf->enabled = MVL_DISABLED;
			return HTTP_GATEWAY_TIME_OUT;
		}

		myfilter = apr_psprintf(r->pool,"(&(%s)(|(apacheServerName=%s)(apacheServerAlias=%s)))",
									conf->filter, r->hostname, r->hostname);

		ret = ldap_search_s (ld, conf->basedn, conf->scope, myfilter, (char **)attributes, 0, &ldapmsg);
		if(ret != LDAP_SUCCESS){//SIGPIPE?
			return DECLINED;
		}
		if(ldap_count_entries(ld, ldapmsg)!=1){
			if(!conf->fallback_name || !conf->fallback_docroot){
				reqc->name = apr_pstrdup(vhost_ldap_pool, r->hostname);
				reqc->decline = 1;
				reqc->admin = apr_pstrdup(vhost_ldap_pool, r->server->server_admin);
				add_to_requestscache(reqc, r);
				if(ldapmsg)
					ldap_msgfree(ldapmsg);
				ldapdestroy(&ld);
				return DECLINED;
			}else{
				reqc->name = conf->fallback_name;
				reqc->docroot = conf->fallback_docroot;
			}
		}else{
			reqc->aliases = (apr_array_header_t *)apr_array_make(vhost_ldap_pool, 2, sizeof(alias_t));
			reqc->redirects = (apr_array_header_t *)apr_array_make(vhost_ldap_pool, 2, sizeof(alias_t));
			reqc->env = apr_table_make(vhost_ldap_pool, 2);
			vhostentry = ldap_first_entry(ld, ldapmsg);
			reqc->dn = ldap_get_dn(ld, vhostentry);
			i=0;
			while(attributes[i]){
				int k = 0, j;
				char **eValues = ldap_get_values(ld, vhostentry, attributes[i]), *str[3];
				if (eValues){
					k = ldap_count_values (eValues);
					if (strcasecmp(attributes[i], "apacheServerName") == 0){
						reqc->name = apr_pstrdup(vhost_ldap_pool, eValues[0]);
					}else if(strcasecmp(attributes[i], "apacheServerAdmin") == 0){
						reqc->admin = apr_pstrdup(vhost_ldap_pool, eValues[0]);
					}else if(strcasecmp(attributes[i], "apacheDocumentRoot") == 0){
						reqc->docroot = apr_pstrdup(vhost_ldap_pool, eValues[0]);
						/* Make it absolute, relative to ServerRoot */
						if(conf->rootdir && (strncmp(reqc->docroot, "/", 1) != 0))
							reqc->docroot = apr_pstrcat(vhost_ldap_pool, conf->rootdir, reqc->docroot, NULL);
						reqc->docroot = ap_server_root_relative(vhost_ldap_pool, reqc->docroot);
					}else if(strcasecmp(attributes[i], "apacheAlias") == 0){
						while(k){
							k--;
							for(j = 0; j < 2; j++)
                                str[j] = ap_getword_conf(r->pool, (const char **)&eValues[k]);
							if(str[--j] == '\0')
								ap_log_rerror(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, r,
                                "[mod_vhost_ldap_ng.c]: Wrong apacheAlias parameter: %s",
                                eValues[k]);
							else{
								alias = apr_array_push(reqc->aliases);
								alias->src = apr_pstrdup(vhost_ldap_pool, str[0]);
								alias->dst = apr_pstrdup(vhost_ldap_pool, str[1]);
							}
						}
					}else if(strcasecmp(attributes[i], "apacheScriptAlias") == 0){
						while(k){
							k--; 
							for(j = 0; j < 2; j++)
								str[j] = ap_getword_conf(r->pool, (const char **)&eValues[k]);
							if(str[--j] == '\0')
								ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
									"[mod_vhost_ldap_ng.c]: Wrong apacheScriptAlias parameter: %s", eValues[k]);
							else{
								alias = apr_array_push(reqc->aliases);
								alias->src = apr_pstrdup(vhost_ldap_pool, str[0]);
								alias->dst = apr_pstrdup(vhost_ldap_pool, str[1]);
							}
						}
					}else if(strcasecmp (attributes[i], "apacheRedirect") == 0){
						while(k){
							k--; 
							for(j = 0; j < 3; j++)
								str[j] = ap_getword_conf(r->pool, (const char **)&eValues[k]);
							if(str[1] == '\0')
								ap_log_rerror(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, r,
								"[mod_vhost_ldap_ng.c]: Missing apacheRedirect parameter: %s",
								eValues[k]);
							else{
								alias = apr_array_push(reqc->redirects);
								alias->src = apr_pstrdup(vhost_ldap_pool, str[0]);
								if(str[2] != '\0'){
									if(strcasecmp(str[1], "gone") == 0)
										alias->flags |= REDIR_GONE;
									else if (strcasecmp(str[1], "permanent") == 0)
										alias->flags |= REDIR_PERMANENT;
									else if (strcasecmp(str[1], "temp") == 0)
										alias->flags |= REDIR_TEMP;
									else if (strcasecmp(str[1], "seeother") == 0)
										alias->flags |= REDIR_SEEOTHER;
									else{
										alias->flags |= REDIR_PERMANENT;
										ap_log_rerror(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, r,
										"[mod_vhost_ldap_ng.c]: Wrong apacheRedirect type: %s", str[2]);
									}
									alias->dst = apr_pstrdup(vhost_ldap_pool, str[2]);
								}else
									alias->dst = apr_pstrdup(vhost_ldap_pool, str[1]);
							}
						}
					}else if(strcasecmp(attributes[i], "apacheSuexecUid") == 0){
						reqc->uid = apr_pstrdup(vhost_ldap_pool, eValues[0]);
					}else if(strcasecmp(attributes[i], "apacheSuexecGid") == 0){
						reqc->gid = apr_pstrdup(vhost_ldap_pool, eValues[0]);
					}else if(strcasecmp (attributes[i], "apacheErrorLog") == 0){
						if(conf->rootdir && (strncmp(eValues[0], "/", 1) != 0))
							r->server->error_fname = apr_pstrcat(vhost_ldap_pool, conf->rootdir, eValues[0], NULL);
						else
							r->server->error_fname = apr_pstrdup(vhost_ldap_pool, eValues[0]);;
						apr_file_open(&r->server->error_log, r->server->error_fname,
								APR_APPEND | APR_WRITE | APR_CREATE | APR_LARGEFILE,
								APR_OS_DEFAULT, r->pool);
					}
#ifdef HAVEPHP
					else if(strcasecmp(attributes[i], "phpIncludePath") == 0){
						if(conf->php_includepath)
							reqc->php_includepath = apr_pstrcat(vhost_ldap_pool, conf->php_includepath, ":", eValues[0], NULL);
						else
							reqc->php_includepath = apr_pstrdup(vhost_ldap_pool, eValues[0]);
					}else if(strcasecmp(attributes[i], "phpOpenBasedir") == 0){
						if(conf->rootdir && (strncmp(eValues[0], "/", 1) != 0))
							reqc->php_openbasedir = apr_pstrcat(vhost_ldap_pool, conf->rootdir, eValues[0], NULL);
						else
							reqc->php_openbasedir = apr_pstrdup(vhost_ldap_pool, eValues[0]);
					}
					else if(strcasecmp(attributes[i], "php_admin_value") == 0){
					}
#endif
					else if(strcasecmp(attributes[i], "SetEnv") == 0){
						for(j = 0; j < 2; j++)
							str[j] = ap_getword_conf(r->pool, (const char **)&eValues[0]);
						if(str[--j] == '\0')
							ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
							"[mod_vhost_ldap_ng.c]: Wrong apacheScriptAlias parameter: %s", eValues[0]);
						else{
							apr_table_set(reqc->env, str[0], str[1]);
						}
					}else if(strcasecmp(attributes[i], "PassEnv") == 0){
					}
				}
				i++;
			}
		}
		if(ldapmsg)
			ldap_msgfree(ldapmsg);
		ldapdestroy(&ld);
		add_to_requestscache(reqc, r);
	}
	if(reqc->decline)
		return DECLINED;
	
	ap_set_module_config(r->request_config, &vhost_ldap_ng_module, reqc);
	e = r->subprocess_env;
	if(apr_table_elts(reqc->env)->nelts)
		r->subprocess_env = apr_table_overlay(r->pool, e, reqc->env);
#ifdef HAVEPHP
	char *openbasedir, *include;
	if(!reqc->php_includepath)
		include = apr_pstrcat(r->pool, conf->php_includepath, ":", reqc->docroot, NULL);
	else
		include = apr_pstrcat(r->pool, reqc->php_includepath, ":", conf->php_includepath, ":", reqc->docroot, NULL);
	zend_alter_ini_entry("include_path", strlen("include_path") + 1, (void *)include, strlen(include), PHP_INI_SYSTEM, PHP_INI_STAGE_RUNTIME);
	if(reqc->php_openbasedir){
		openbasedir = apr_pstrcat(r->pool, reqc->php_openbasedir, ":", include, NULL);
		zend_alter_ini_entry("open_basedir", strlen("open_basedir") + 1, (void *)openbasedir, strlen(openbasedir), PHP_INI_SYSTEM, PHP_INI_STAGE_RUNTIME);
	}
#endif
	if ((reqc->name == NULL)||(reqc->docroot == NULL)) {
		ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, r, 
			"[mod_vhost_ldap_ng.c] translate: "
			"translate failed; ServerName %s or DocumentRoot %s not defined", reqc->name, reqc->docroot);
		return HTTP_INTERNAL_SERVER_ERROR;
	}
	
	cursor = NULL;
	//From mod_alias: checking for redirects
	if(reqc->redirects){
		cursor = (alias_t *)reqc->redirects->elts;
		if (r->uri[0] != '/' && r->uri[0] != '\0') 
			return DECLINED;
		for(i = 0; i < reqc->redirects->nelts; i++){
			alias = (alias_t *) &cursor[i];
			if(alias_matches(r->uri, alias->src)){
				apr_table_setn(r->headers_out, "Location", alias->dst);
				/* OLD STUFF
				if(alias->redir_status){
					if (strcasecmp(alias->redir_status, "gone") == 0)
						return  HTTP_GONE;
					else if (strcasecmp(alias->redir_status, "permanent") == 0)
						return HTTP_MOVED_PERMANENTLY;
					else if (strcasecmp(alias->redir_status, "temp") == 0)
						return HTTP_MOVED_TEMPORARILY;
					else if (strcasecmp(alias->redir_status, "seeother") == 0)
						return HTTP_SEE_OTHER;
				}
				*/
				if(alias->flags & REDIR_GONE) return HTTP_GONE;
				else if(alias->flags & REDIR_TEMP) return HTTP_MOVED_TEMPORARILY;
				else if(alias->flags & REDIR_SEEOTHER) return HTTP_SEE_OTHER;
				else return HTTP_MOVED_PERMANENTLY;
			}
		}
	}
	
	/* Checking for aliases */
	if(reqc->aliases){
		cursor = (alias_t *)reqc->aliases->elts;
		for(i = 0; reqc->aliases && i < reqc->aliases->nelts; i++){
			alias = (alias_t *) &cursor[i];
			if (alias_matches(r->uri, alias->src)) {
				/* Set exact filename for CGI script */
				realfile = apr_pstrcat(r->pool, alias->dst, r->uri + strlen(alias->src), NULL);
				/* Add apacheRootDir config param IF realfile is a realative path*/
				if(conf->rootdir && (strncmp(realfile, "/", 1) != 0))
					realfile = apr_pstrcat(r->pool, conf->rootdir, "/", realfile, NULL);
				/* Let apache normalize the path */
				if((realfile = ap_server_root_relative(r->pool, realfile))) {
					ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
						"[mod_vhost_ldap_ng.c]: ap_document_root is: %s",
						ap_document_root(r));
					r->filename = realfile;
					if(alias->flags & ISCGI){
						//r->handler = "cgi-script";
						r->handler = "Script";
						apr_table_setn(r->notes, "alias-forced-type", r->handler);
					}
					return OK;
				}
				return OK;
			} else if (r->uri[0] == '/') {
				/* we don't set r->filename here, and let other modules do it
				* this allows other modules (mod_rewrite.c) to work as usual
				*/
				/* r->filename = apr_pstrcat (r->pool, reqc->docroot, r->uri, NULL); */
			} else {
				/* We don't handle non-file requests here */
				return DECLINED;
			}
		}
	}
	
	if ((r->server = apr_pmemdup(r->pool, r->server, sizeof(*r->server))) == NULL) {
		ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, r, 
			"[mod_vhost_ldap_ng.c] translate: "
			"translate failed; Unable to copy r->server structure");
		return HTTP_INTERNAL_SERVER_ERROR;
	}
	
	r->server->server_hostname = apr_pstrdup(r->pool,reqc->name);

	if (reqc->admin)
		r->server->server_admin = apr_pstrdup(r->pool, reqc->admin);

#if (AP_SERVER_MAJORVERSION_NUMBER == 2) && (AP_SERVER_MINORVERSION_NUMBER <= 2)
	core->ap_document_root = apr_pstrdup(r->pool, reqc->docroot);
	if (!ap_is_directory(r->pool, reqc->docroot))
		ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
			"[mod_vhost_ldap_ng.c] set_document_root: Warning: DocumentRoot [%s] does not exist", core->ap_document_root);
#else
	ap_set_document_root(r, reqc->docroot);
#endif
	//ap_set_module_config(r->server->module_config, &core_module, core);

	/* Hack to allow post-processing by other modules (mod_rewrite, mod_alias) */
	return DECLINED;
}