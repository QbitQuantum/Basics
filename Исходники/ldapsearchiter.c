static PyObject *
LDAPSearchIter_AcquireNextPage(LDAPSearchIter *self) {
	int msgid = -1;

	/* If paged LDAP search is in progress. */
	if ((self->cookie != NULL) && (self->cookie->bv_val != NULL) &&
			(strlen(self->cookie->bv_val) > 0)) {
		msgid = LDAPConnection_Searching(self->conn, (PyObject *)self);
		if (msgid < 0) return NULL;

		return PyLong_FromLong((long int)msgid);
	} else {
		ber_bvfree(self->cookie);
		self->cookie = NULL;

		Py_RETURN_NONE;
	}
}