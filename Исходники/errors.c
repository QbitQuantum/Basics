/* Convert an LDAP error into an informative python exception */
PyObject*
LDAPerror( LDAP*l, char*msg ) 
{
	if (l == NULL) {
		PyErr_SetFromErrno( LDAPexception_class );
		return NULL;
	}
	else {
		int errnum;
		PyObject *errobj;
		PyObject *info;
		PyObject *str;

		char *matched, *error;
		if (ldap_get_option(l, LDAP_OPT_ERROR_NUMBER, &errnum) < 0)
			errobj = LDAPexception_class;	/* unknown error XXX */
		else
			errobj = errobjects[errnum+LDAP_ERROR_OFFSET];
		
		if (errnum == LDAP_NO_MEMORY)
			return PyErr_NoMemory();

		info = PyDict_New();
		if (info == NULL)
			return NULL;

		str = PyBytes_FromString(ldap_err2string(errnum));
		if (str)
			PyDict_SetItemString( info, "desc", str );
		Py_XDECREF(str);

		if (ldap_get_option(l, LDAP_OPT_MATCHED_DN, &matched) >= 0
			&& matched != NULL) {
		    if (*matched != '\0') {
			str = PyBytes_FromString(matched);
			if (str)
			    PyDict_SetItemString( info, "matched", str );
			Py_XDECREF(str);
		    }
		    ldap_memfree(matched);
		}
		
		if (errnum == LDAP_REFERRAL) {
		    str = PyBytes_FromString(msg);
		    if (str)
			PyDict_SetItemString( info, "info", str );
		    Py_XDECREF(str);
		} else if (ldap_get_option(l, LDAP_OPT_ERROR_STRING, &error) >= 0
			&& error != NULL) {
		    if (error != '\0') {
			str = PyBytes_FromString(error);
			if (str)
			    PyDict_SetItemString( info, "info", str );
			Py_XDECREF(str);
		    }
		    ldap_memfree(error);
		}
		PyErr_SetObject( errobj, info );
		Py_DECREF(info);
		return NULL;
	}
}