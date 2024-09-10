 /* Poll the answer of the async function calls of the binding process.
 Returns NULL in case of error, Py_None for timeout, and the LDAPConnection
 object if successfully finished the binding. */
static PyObject *
binding(LDAPConnectIter *self) {
	int rc = -1;
	int err = 0;
	struct timeval polltime;
	LDAPControl **returned_ctrls = NULL;
	LDAPMessage *res;

	polltime.tv_sec = 0L;
	polltime.tv_usec = 10L;

	if (self->bind_inprogress == 0) {
		/* First call of bind. */
		rc = LDAP_bind(self->conn->ld, self->info, NULL, &(self->message_id));
		if (rc != LDAP_SUCCESS && rc != LDAP_SASL_BIND_IN_PROGRESS) {
			set_exception(self->conn->ld, rc);
			return NULL;
		}
		self->bind_inprogress = 1;
		Py_RETURN_NONE;
	} else {
		if (self->async) {
			/* Binding is already in progress, poll result from the server. */
			rc = ldap_result(self->conn->ld, self->message_id, LDAP_MSG_ALL, &polltime, &res);
		} else {
			/* Block until the server response. */
			rc = ldap_result(self->conn->ld, self->message_id, LDAP_MSG_ALL, NULL, &res);
		}
		switch (rc) {
		case -1:
			/* Error occurred during the operation. */
			set_exception(self->conn->ld, 0);
			return NULL;
		case 0:
			/* Timeout exceeded.*/
			Py_RETURN_NONE;
		case LDAP_RES_BIND:
			/* Response is arrived from the server. */
			rc = ldap_parse_result(self->conn->ld, res, &err, NULL, NULL, NULL, &returned_ctrls, 0);

			if ((rc != LDAP_SUCCESS) ||
				(err != LDAP_SASL_BIND_IN_PROGRESS && err != LDAP_SUCCESS)) {
				/* Connection is failed. */
				set_exception(self->conn->ld, err);
				return NULL;
			}

			if (strcmp(self->info->mech, "SIMPLE") != 0) {
				/* Continue SASL binding procedure. */
				rc = LDAP_bind(self->conn->ld, self->info, res, &(self->message_id));

				if (rc != LDAP_SUCCESS && rc != LDAP_SASL_BIND_IN_PROGRESS) {
					set_exception(self->conn->ld, rc);
					return NULL;
				}

				if (rc == LDAP_SASL_BIND_IN_PROGRESS) {
					Py_RETURN_NONE;
				}
			}

			if (rc == LDAP_SUCCESS) {
				/* The binding is successfully finished. */
				self->bind_inprogress = 0;
				self->conn->closed = 0;
				Py_INCREF((PyObject *)self->conn);
				return (PyObject *)self->conn;
			}
			Py_RETURN_NONE;
		default:
			/* Invalid return value, it never should happen. */
			PyErr_BadInternalCall();
			return NULL;
		}
	}
}