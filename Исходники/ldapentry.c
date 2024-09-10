/* Preform a LDAP add or modify operation depend on the `mod` parameter. */
PyObject *
add_or_modify(LDAPEntry *self, int mod) {
	int rc = -1;
	char *dnstr = NULL;
	LDAPMod **mods = NULL;
	PyObject *tmp;

	/* Get DN string. */
	tmp = PyObject_Str(self->dn);
	dnstr = PyObject2char(tmp);
	Py_DECREF(tmp);
	if (dnstr == NULL || strlen(dnstr) == 0) {
		PyErr_SetString(PyExc_AttributeError, "Missing distinguished name.");
		return NULL;
	}
	mods = LDAPEntry_CreateLDAPMods(self);
	if (mods == NULL) {
		PyErr_SetString(PyExc_MemoryError, "Create LDAPMods is failed.");
		return NULL;
	}

	if (mod == 0) {
		rc = ldap_add_ext_s(self->client->ld, dnstr, mods, NULL, NULL);
	} else {
		rc = ldap_modify_ext_s(self->client->ld, dnstr, mods, NULL, NULL);
	}
	if (rc != LDAP_SUCCESS) {
		//TODO Proper errors
		PyObject *ldaperror = get_error("LDAPError");
		PyErr_SetString(ldaperror, ldap_err2string(rc));
		Py_DECREF(ldaperror);
		LDAPEntry_DismissLDAPMods(self, mods);
		free(dnstr);
		return NULL;
	}
	free(dnstr);
	LDAPEntry_DismissLDAPMods(self, mods);
	return Py_None;
}