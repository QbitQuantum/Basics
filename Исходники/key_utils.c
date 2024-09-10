int
read_key_pem(FILE *fp, PyObject **py_private_key_ndn,
             PyObject **py_public_key_ndn, PyObject **py_public_key_digest,
             int *public_key_digest_len,
             char *password)
{
        struct ndn_pkey *private_key = NULL;
	PyObject *py_private_key = NULL, *py_public_key = NULL;
	unsigned long err, reason;
	fpos_t fpos;
	int r;
	int public_only;

	r = fgetpos(fp, &fpos);
	JUMP_IF_NEG(r, errno_error);

        private_key = (struct ndn_pkey *)PEM_read_PrivateKey(fp, NULL, NULL, password);
	if (private_key) {
		public_only = 0;
		goto success;
	}

	err = ERR_get_error();
	reason = ERR_GET_REASON(err);

	/* 108 was meaning that start line isn't recognized */
	if (reason == 108) {
		r = fsetpos(fp, &fpos);
		JUMP_IF_NEG(r, errno_error);

		private_key = (struct ndn_pkey *)PEM_read_PUBKEY (fp, NULL, NULL, NULL);
		if (private_key) {
			public_only = 1;
			goto success;
		}

		err = ERR_get_error();
		reason = ERR_GET_REASON(err);
	}

	{
		char buf[256];

		ERR_error_string_n(err, buf, sizeof(buf));
		PyErr_Format(g_PyExc_NDNKeyError, "Unable to read Private Key: %s",
				buf);
		goto error;
	}

success:

	r = ndn_keypair(public_only, private_key, py_private_key_ndn,
			py_public_key_ndn);
	JUMP_IF_NEG(r, error);

	r = create_public_key_digest(private_key, py_public_key_digest,
			public_key_digest_len);
	JUMP_IF_NEG(r, error);

	return 0;

errno_error:
	PyErr_SetFromErrno(PyExc_IOError);
error:
	Py_XDECREF(py_private_key);
	Py_XDECREF(py_public_key);
	if (private_key)
		EVP_PKEY_free((EVP_PKEY *)private_key);
	return -1;
}