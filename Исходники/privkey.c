/* Read a sets of private DSA keys from a FILE* into the given
 * OtrlUserState.  The FILE* must be open for reading. */
gcry_error_t otrl_privkey_read_FILEp(OtrlUserState us, FILE *privf)
{
    int privfd;
    struct stat st;
    char *buf;
    const char *token;
    size_t tokenlen;
    gcry_error_t err;
    gcry_sexp_t allkeys;
    size_t i;

    if (!privf) return gcry_error(GPG_ERR_NO_ERROR);

    /* Release any old ideas we had about our keys */
    otrl_privkey_forget_all(us);

    /* Load the data into a buffer */
    privfd = fileno(privf);
    if (fstat(privfd, &st)) {
	err = gcry_error_from_errno(errno);
	return err;
    }
    buf = malloc(st.st_size);
    if (!buf && st.st_size > 0) {
	return gcry_error(GPG_ERR_ENOMEM);
    }
    if (fread(buf, st.st_size, 1, privf) != 1) {
	err = gcry_error_from_errno(errno);
	free(buf);
	return err;
    }

    err = gcry_sexp_new(&allkeys, buf, st.st_size, 0);
    free(buf);
    if (err) {
	return err;
    }

    token = gcry_sexp_nth_data(allkeys, 0, &tokenlen);
    if (tokenlen != 8 || strncmp(token, "privkeys", 8)) {
	gcry_sexp_release(allkeys);
	return gcry_error(GPG_ERR_UNUSABLE_SECKEY);
    }

    /* Get each account */
    for(i=1; i<gcry_sexp_length(allkeys); ++i) {
	gcry_sexp_t names, protos, privs;
	char *name, *proto;
	gcry_sexp_t accounts;
	OtrlPrivKey *p;
	
	/* Get the ith "account" S-exp */
	accounts = gcry_sexp_nth(allkeys, i);
	
	/* It's really an "account" S-exp? */
	token = gcry_sexp_nth_data(accounts, 0, &tokenlen);
	if (tokenlen != 7 || strncmp(token, "account", 7)) {
	    gcry_sexp_release(accounts);
	    gcry_sexp_release(allkeys);
	    return gcry_error(GPG_ERR_UNUSABLE_SECKEY);
	}
	/* Extract the name, protocol, and privkey S-exps */
	names = gcry_sexp_find_token(accounts, "name", 0);
	protos = gcry_sexp_find_token(accounts, "protocol", 0);
	privs = gcry_sexp_find_token(accounts, "private-key", 0);
	gcry_sexp_release(accounts);
	if (!names || !protos || !privs) {
	    gcry_sexp_release(names);
	    gcry_sexp_release(protos);
	    gcry_sexp_release(privs);
	    gcry_sexp_release(allkeys);
	    return gcry_error(GPG_ERR_UNUSABLE_SECKEY);
	}
	/* Extract the actual name and protocol */
	token = gcry_sexp_nth_data(names, 1, &tokenlen);
	if (!token) {
	    gcry_sexp_release(names);
	    gcry_sexp_release(protos);
	    gcry_sexp_release(privs);
	    gcry_sexp_release(allkeys);
	    return gcry_error(GPG_ERR_UNUSABLE_SECKEY);
	}
	name = malloc(tokenlen + 1);
	if (!name) {
	    gcry_sexp_release(names);
	    gcry_sexp_release(protos);
	    gcry_sexp_release(privs);
	    gcry_sexp_release(allkeys);
	    return gcry_error(GPG_ERR_ENOMEM);
	}
	memmove(name, token, tokenlen);
	name[tokenlen] = '\0';
	gcry_sexp_release(names);

	token = gcry_sexp_nth_data(protos, 1, &tokenlen);
	if (!token) {
	    free(name);
	    gcry_sexp_release(protos);
	    gcry_sexp_release(privs);
	    gcry_sexp_release(allkeys);
	    return gcry_error(GPG_ERR_UNUSABLE_SECKEY);
	}
	proto = malloc(tokenlen + 1);
	if (!proto) {
	    free(name);
	    gcry_sexp_release(protos);
	    gcry_sexp_release(privs);
	    gcry_sexp_release(allkeys);
	    return gcry_error(GPG_ERR_ENOMEM);
	}
	memmove(proto, token, tokenlen);
	proto[tokenlen] = '\0';
	gcry_sexp_release(protos);

	/* Make a new OtrlPrivKey entry */
	p = malloc(sizeof(*p));
	if (!p) {
	    free(name);
	    free(proto);
	    gcry_sexp_release(privs);
	    gcry_sexp_release(allkeys);
	    return gcry_error(GPG_ERR_ENOMEM);
	}

	/* Fill it in and link it up */
	p->accountname = name;
	p->protocol = proto;
	p->pubkey_type = OTRL_PUBKEY_TYPE_DSA;
	p->privkey = privs;
	p->next = us->privkey_root;
	if (p->next) {
	    p->next->tous = &(p->next);
	}
	p->tous = &(us->privkey_root);
	us->privkey_root = p;
	err = make_pubkey(&(p->pubkey_data), &(p->pubkey_datalen), p->privkey);
	if (err) {
	    gcry_sexp_release(allkeys);
	    otrl_privkey_forget(p);
	    return gcry_error(GPG_ERR_UNUSABLE_SECKEY);
	}
    }
    gcry_sexp_release(allkeys);

    return gcry_error(GPG_ERR_NO_ERROR);
}