static krb5_error_code
parse_key_set(krb5_context context, const char *key,
	      krb5_enctype **ret_enctypes, size_t *ret_num_enctypes,
	      krb5_salt *salt, krb5_principal principal)
{
    const char *p;
    char buf[3][256];
    int num_buf = 0;
    int i, num_enctypes = 0;
    krb5_enctype e;
    const krb5_enctype *enctypes = NULL;
    krb5_error_code ret;

    p = key;

    *ret_enctypes = NULL;
    *ret_num_enctypes = 0;

    /* split p in a list of :-separated strings */
    for(num_buf = 0; num_buf < 3; num_buf++)
	if(strsep_copy(&p, ":", buf[num_buf], sizeof(buf[num_buf])) == -1)
	    break;

    salt->saltvalue.data = NULL;
    salt->saltvalue.length = 0;

    for(i = 0; i < num_buf; i++) {
	if(enctypes == NULL && num_buf > 1) {
	    /* this might be a etype specifier */
	    /* XXX there should be a string_to_etypes handling
	       special cases like `des' and `all' */
	    if(strcmp(buf[i], "des") == 0) {
		enctypes = des_etypes;
		num_enctypes = sizeof(des_etypes)/sizeof(des_etypes[0]);
	    } else if(strcmp(buf[i], "des3") == 0) {
		e = ETYPE_DES3_CBC_SHA1;
		enctypes = &e;
		num_enctypes = 1;
	    } else {
		ret = krb5_string_to_enctype(context, buf[i], &e);
		if (ret == 0) {
		    enctypes = &e;
		    num_enctypes = 1;
		} else
		    return ret;
	    }
	    continue;
	}
	if(salt->salttype == 0) {
	    /* interpret string as a salt specifier, if no etype
	       is set, this sets default values */
	    /* XXX should perhaps use string_to_salttype, but that
	       interface sucks */
	    if(strcmp(buf[i], "pw-salt") == 0) {
		if(enctypes == NULL) {
		    enctypes = all_etypes;
		    num_enctypes = sizeof(all_etypes)/sizeof(all_etypes[0]);
		}
		salt->salttype = KRB5_PW_SALT;
	    } else if(strcmp(buf[i], "afs3-salt") == 0) {
		if(enctypes == NULL) {
		    enctypes = des_etypes;
		    num_enctypes = sizeof(des_etypes)/sizeof(des_etypes[0]);
		}
		salt->salttype = KRB5_AFS3_SALT;
	    }
	    continue;
	}

	{
	    /* if there is a final string, use it as the string to
	       salt with, this is mostly useful with null salt for
	       v4 compat, and a cell name for afs compat */
	    salt->saltvalue.data = strdup(buf[i]);
	    if (salt->saltvalue.data == NULL) {
		krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
		return ENOMEM;
	    }
	    salt->saltvalue.length = strlen(buf[i]);
	}
    }

    if(enctypes == NULL || salt->salttype == 0) {
	krb5_set_error_message(context, EINVAL, "bad value for default_keys `%s'", key);
	return EINVAL;
    }

    /* if no salt was specified make up default salt */
    if(salt->saltvalue.data == NULL) {
	if(salt->salttype == KRB5_PW_SALT)
	    ret = krb5_get_pw_salt(context, principal, salt);
	else if(salt->salttype == KRB5_AFS3_SALT) {
	    krb5_const_realm realm = krb5_principal_get_realm(context, principal);
	    salt->saltvalue.data = strdup(realm);
	    if(salt->saltvalue.data == NULL) {
		krb5_set_error_message(context, ENOMEM,
				       "out of memory while "
				       "parsing salt specifiers");
		return ENOMEM;
	    }
	    strlwr(salt->saltvalue.data);
	    salt->saltvalue.length = strlen(realm);
	}
    }

    *ret_enctypes = malloc(sizeof(enctypes[0]) * num_enctypes);
    if (*ret_enctypes == NULL) {
	krb5_free_salt(context, *salt);
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }
    memcpy(*ret_enctypes, enctypes, sizeof(enctypes[0]) * num_enctypes);
    *ret_num_enctypes = num_enctypes;

    return 0;
}