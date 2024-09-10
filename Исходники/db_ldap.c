int ldapLogin(char *thisUid, char *thisPwd, struct threadInfo * ti) {
	extern struct threadInfo *pMainThreadInfo;

	int (*dbConnect)(struct threadStorageInfo *);
	void (*dbDisconnect)(struct threadStorageInfo *);
	int (*dbCookie)(char *, int, struct threadStorageInfo *);
	int (*dbInsert)(char *, int, struct threadStorageInfo *);

	dbConnect = pMainThreadInfo->dbInfo.connect;
	dbDisconnect = pMainThreadInfo->dbInfo.disconnect;
	dbCookie = pMainThreadInfo->dbInfo.cookie;
	dbInsert = pMainThreadInfo->dbInfo.insert;

	if(thisUid == NULL) {
		return(-1);
	}

	if((ti->directoryInfo.ldapUri = configFetch("ldap_uri", &ti->directoryInfo.i)) == NULL) {
		ti->directoryInfo.ldapUri = LDAP_MYURI;
	}

	if((ti->directoryInfo.ldapUsername = configFetch("ldap_username", &ti->directoryInfo.i)) == NULL) {
		ti->directoryInfo.ldapUsername = LDAP_MYUSERNAME;
	}

	if((ti->directoryInfo.ldapPassword = configFetch("ldap_password", &ti->directoryInfo.i)) == NULL) {
		ti->directoryInfo.ldapPassword = LDAP_MYPASSWORD;
	}

	if((ti->directoryInfo.ldapAttr = configFetch("ldap_searchattr", &ti->directoryInfo.i)) == NULL) {
		ti->directoryInfo.ldapAttr = LDAP_MYATTR;
	}

	if((ti->directoryInfo.ldapBase = configFetch("ldap_searchbase", &ti->directoryInfo.i)) == NULL) {
		ti->directoryInfo.ldapBase = LDAP_MYBASE;
	}

	if((ti->directoryInfo.ldapFilter = configFetch("ldap_searchfilter", &ti->directoryInfo.i)) == NULL) {
		ti->directoryInfo.ldapFilter = LDAP_MYFILTER;
	}

	if(ldap_initialize(&ti->directoryInfo.l, ti->directoryInfo.ldapUri) != LDAP_SUCCESS) {
		ldapMessage(ti, ERROR_SLIGHT, "Error occurred while trying to initialize LDAP connection", NULL);

		return(-1);
	}

	ti->directoryInfo.v = LDAP_MYVERSION;

	if(ldap_set_option(ti->directoryInfo.l, LDAP_OPT_PROTOCOL_VERSION, (int *) &ti->directoryInfo.v) != LDAP_OPT_SUCCESS) {
		ldapMessage(ti, ERROR_SLIGHT, "Error occurred while trying to initialize LDAP connection", NULL);

		ldap_unbind(ti->directoryInfo.l);

		return(-1);
	}

	if(ti->directoryInfo.ldapUsername != NULL && ti->directoryInfo.ldapUsername[0] != 0) {
		if(ldap_bind_s(ti->directoryInfo.l, ti->directoryInfo.ldapUsername, ti->directoryInfo.ldapPassword, LDAP_AUTH_SIMPLE) != LDAP_SUCCESS) {
			ldapMessage(ti, ERROR_SLIGHT, "Error occurred while trying to establish LDAP connection", ti->directoryInfo.ldapUsername);

			ldap_unbind(ti->directoryInfo.l);

			return(-1);
		}
	}

	ti->directoryInfo.timeVal.tv_sec = LDAP_MYTIMEOUT;
	ti->directoryInfo.timeVal.tv_usec = 0;

	if(ldap_search_st(ti->directoryInfo.l, ti->directoryInfo.ldapBase, LDAP_SCOPE_SUBTREE, ti->directoryInfo.ldapFilter, NULL, 0, &ti->directoryInfo.timeVal, &ti->directoryInfo.m) != LDAP_SUCCESS) {
		ldapMessage(ti, ERROR_SLIGHT, "Error occurred while trying to search from LDAP database", ti->directoryInfo.ldapFilter);

		ldap_unbind(ti->directoryInfo.l);

		return(-1);
	}

	if(ldap_count_entries(ti->directoryInfo.l, ti->directoryInfo.m) <= 0) {
		ldapMessage(ti, ERROR_SLIGHT, "Search from LDAP database returned no entries", ti->directoryInfo.ldapFilter);

		ldap_msgfree(ti->directoryInfo.m);
		ldap_unbind(ti->directoryInfo.l);

		return(-1);
	}

	if((ti->directoryInfo.e = ldap_first_entry(ti->directoryInfo.l, ti->directoryInfo.m)) == NULL) {
		ldapMessage(ti, ERROR_SLIGHT, "Search from LDAP database returned no entries", ti->directoryInfo.ldapFilter);

		ldap_msgfree(ti->directoryInfo.m);
		ldap_unbind(ti->directoryInfo.l);

		return(-1);
	}

	if((ti->directoryInfo.d = ldap_get_dn(ti->directoryInfo.l, ti->directoryInfo.e)) == NULL) {
		ldapMessage(ti, ERROR_SLIGHT, "Search from LDAP database returned no entries", ti->directoryInfo.ldapFilter);

		ldap_msgfree(ti->directoryInfo.m);
		ldap_unbind(ti->directoryInfo.l);

		return(-1);
	}

	snprintf(ti->directoryInfo.dnSpace, sizeof(ti->directoryInfo.dnSpace), "%s=%s,%s%c", ti->directoryInfo.ldapAttr, thisUid, ti->directoryInfo.d, 0);

	ldap_memfree(ti->directoryInfo.d);
	ldap_msgfree(ti->directoryInfo.m);

	if(ldap_bind_s(ti->directoryInfo.l, ti->directoryInfo.dnSpace, thisPwd, LDAP_AUTH_SIMPLE) != LDAP_SUCCESS) {
		ldapMessage(ti, ERROR_SLIGHT, "Authentication against LDAP failed", ti->directoryInfo.dnSpace);

		ldap_unbind(ti->directoryInfo.l);

		return(-1);
	}

	ldap_unbind(ti->directoryInfo.l);

	ti->directoryInfo.l = NULL;

	if(dbConnect(&ti->storageInfo) == 0) {
		if(dbCookie(thisUid, strlen(thisUid), &ti->storageInfo) != 0) {
			ldapMessage(ti, ERROR_SLIGHT, "Authentication against LDAP failed", "Error occurred while trying to create session");

			dbDisconnect(&ti->storageInfo);

			return(-1);
		}

		if(dbInsert(thisUid, strlen(thisUid), &ti->storageInfo) != 0) {
			ldapMessage(ti, ERROR_SLIGHT, "Authentication against LDAP failed", "Error occurred while trying to create session");

			dbDisconnect(&ti->storageInfo);

			return(-1);
		}

		dbDisconnect(&ti->storageInfo);

		return(0);
	}
	else {
		ldapMessage(ti, ERROR_SLIGHT, "Authentication against LDAP failed", "Error occurred while trying to create session");

		return(-1);
	}
}