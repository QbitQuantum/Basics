/*	Opens a connection to the LDAP server. Initializes LDAP structure.
	If TLS is true, starts TLS session.
*/
static int
connecting(LDAPConnection *self) {
	int rc = -1;
	int tls_option = -1;
	char *binddn = NULL;
	char *pswstr = NULL;
	char *mech = NULL;
	char *authzid = "";
	char *realm = NULL;
	char *authcid = NULL;
	PyObject *url = NULL;
	PyObject *tls = NULL;
	PyObject *tmp = NULL;
	PyObject *creds = NULL;

	url = PyObject_GetAttrString(self->client, "_LDAPClient__url");
	if (url == NULL) return -1;

	tmp = PyObject_GetAttrString(self->client, "_LDAPClient__cert_policy");
	tls_option = (int)PyLong_AsLong(tmp);
	Py_DECREF(tmp);

	rc = _LDAP_initialization(&(self->ld), url, tls_option);
	Py_DECREF(url);

	if (rc != LDAP_SUCCESS) {
		PyObject *ldaperror = get_error_by_code(rc);
		PyErr_SetString(ldaperror, ldap_err2string(rc));
		Py_DECREF(ldaperror);
		return -1;
	}

	tls = PyObject_GetAttrString(self->client, "_LDAPClient__tls");
	if (tls == NULL) return -1;

	/* Start TLS, if it necessary. */
	if (PyObject_IsTrue(tls)) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
		rc = ldap_start_tls_sA(self->ld, NULL, NULL, NULL, NULL);
#else
		rc = ldap_start_tls_s(self->ld, NULL, NULL);
#endif
		if (rc != LDAP_SUCCESS) {
			//TODO Proper errors
			PyObject *ldaperror = get_error_by_code(rc);
			PyErr_SetString(ldaperror, ldap_err2string(rc));
			Py_DECREF(ldaperror);
			Py_DECREF(tls);
			return -1;
		}
	}
	Py_DECREF(tls);

	creds = PyObject_GetAttrString(self->client, "_LDAPClient__credentials");
	if (creds == NULL) return -1;

	tmp = PyObject_GetAttrString(self->client, "_LDAPClient__mechanism");
	if (tmp == NULL) return -1;
	mech = PyObject2char(tmp);
	Py_XDECREF(tmp);

	/* Get credential information, if it's given. */
	if (PyTuple_Check(creds) && PyTuple_Size(creds) > 1) {
		if (strcmp(mech, "SIMPLE") == 0) {
			tmp = PyTuple_GetItem(creds, 0);
			binddn = PyObject2char(tmp);
		} else {
			tmp = PyTuple_GetItem(creds, 0);
			authcid = PyObject2char(tmp);
			tmp = PyDict_GetItemString(creds, "realm");
			realm = PyObject2char(tmp);
		}
		tmp = PyTuple_GetItem(creds, 1);
		pswstr = PyObject2char(tmp);
	}

	if (authzid == NULL) authzid = "";

	rc = _LDAP_bind_s(self->ld, mech, binddn, pswstr, authcid, realm, authzid);

	free(mech);
	free(binddn);
	free(pswstr);
	free(authcid);
	free(realm);
	if (strcmp(authzid, "") != 0) free(authzid);

	if (rc != LDAP_SUCCESS) {
		PyObject *ldaperror = get_error_by_code(rc);
		PyErr_SetString(ldaperror, ldap_err2string(rc));
		Py_DECREF(ldaperror);
		Py_DECREF(creds);
		return -1;
	}
	Py_DECREF(creds);

	return 0;
}