static krb5_error_code
get_new_tickets(krb5_context context,
		krb5_principal principal,
		krb5_ccache ccache,
		krb5_deltat ticket_life,
		int interactive)
{
    krb5_error_code ret;
    krb5_get_init_creds_opt *opt;
    krb5_creds cred;
    char passwd[256];
    krb5_deltat start_time = 0;
    krb5_deltat renew = 0;
    const char *renewstr = NULL;
    krb5_enctype *enctype = NULL;
    krb5_ccache tempccache;
    krb5_init_creds_context icc;
    krb5_keytab kt = NULL;
    int need_prompt;
    int will_use_keytab =  (use_keytab || keytab_str);

    passwd[0] = '\0';

    if (password_file) {
	FILE *f;

	if (strcasecmp("STDIN", password_file) == 0)
	    f = stdin;
	else
	    f = fopen(password_file, "r");
	if (f == NULL)
	    krb5_errx(context, 1, "Failed to open the password file %s",
		      password_file);

	if (fgets(passwd, sizeof(passwd), f) == NULL)
	    krb5_errx(context, 1,
		      N_("Failed to read password from file %s", ""),
		      password_file);
	if (f != stdin)
	    fclose(f);
	passwd[strcspn(passwd, "\n")] = '\0';
    }

#if defined(__APPLE__) && !defined(__APPLE_TARGET_EMBEDDED__)
    if (passwd[0] == '\0' && !will_use_keytab && home_directory_flag) {
	const char *realm;
	OSStatus osret;
	UInt32 length;
	void *buffer;
	char *name;

	realm = krb5_principal_get_realm(context, principal);

	ret = krb5_unparse_name_flags(context, principal,
				      KRB5_PRINCIPAL_UNPARSE_NO_REALM, &name);
	if (ret)
	    goto nopassword;

	osret = SecKeychainFindGenericPassword(NULL, (UInt32)strlen(realm), realm,
					       (UInt32)strlen(name), name,
					       &length, &buffer, &passwordItem);
	free(name);
	if (osret != noErr)
	    goto nopassword;

	if (length < sizeof(passwd) - 1) {
	    memcpy(passwd, buffer, length);
	    passwd[length] = '\0';
	}
	SecKeychainItemFreeContent(NULL, buffer);
    nopassword:
	do { } while(0);
    }
#endif

    memset(&cred, 0, sizeof(cred));

    ret = krb5_get_init_creds_opt_alloc (context, &opt);
    if (ret)
	krb5_err(context, 1, ret, "krb5_get_init_creds_opt_alloc");

    krb5_get_init_creds_opt_set_default_flags(context, "kinit",
	krb5_principal_get_realm(context, principal), opt);

    if(forwardable_flag != -1)
	krb5_get_init_creds_opt_set_forwardable (opt, forwardable_flag);

    if(proxiable_flag != -1)
	krb5_get_init_creds_opt_set_proxiable (opt, proxiable_flag);
    if(anonymous_flag)
	krb5_get_init_creds_opt_set_anonymous (opt, anonymous_flag);
    if (pac_flag != -1)
	krb5_get_init_creds_opt_set_pac_request(context, opt,
						pac_flag ? TRUE : FALSE);
    if (canonicalize_flag)
	krb5_get_init_creds_opt_set_canonicalize(context, opt, TRUE);
    if (pk_enterprise_flag || enterprise_flag || canonicalize_flag || windows_flag)
	krb5_get_init_creds_opt_set_win2k(context, opt, TRUE);
    if (pk_user_id || ent_user_id || anonymous_flag) {
	ret = krb5_get_init_creds_opt_set_pkinit(context, opt,
						 principal,
						 pk_user_id,
						 pk_x509_anchors,
						 NULL,
						 NULL,
						 pk_use_enckey ? 2 : 0 |
						 anonymous_flag ? 4 : 0,
						 krb5_prompter_posix,
						 NULL,
						 passwd);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_get_init_creds_opt_set_pkinit");
	if (ent_user_id)
	    krb5_get_init_creds_opt_set_pkinit_user_cert(context, opt, ent_user_id);
    }

    if (addrs_flag != -1)
	krb5_get_init_creds_opt_set_addressless(context, opt,
						addrs_flag ? FALSE : TRUE);

    if (renew_life == NULL && renewable_flag)
	renewstr = "1 month";
    if (renew_life)
	renewstr = renew_life;
    if (renewstr) {
	renew = parse_time (renewstr, "s");
	if (renew < 0)
	    errx (1, "unparsable time: %s", renewstr);

	krb5_get_init_creds_opt_set_renew_life (opt, renew);
    }

    if(ticket_life != 0)
	krb5_get_init_creds_opt_set_tkt_life (opt, ticket_life);

    if(start_str) {
	int tmp = parse_time (start_str, "s");
	if (tmp < 0)
	    errx (1, N_("unparsable time: %s", ""), start_str);

	start_time = tmp;
    }

    if(etype_str.num_strings) {
	int i;

	enctype = malloc(etype_str.num_strings * sizeof(*enctype));
	if(enctype == NULL)
	    errx(1, "out of memory");
	for(i = 0; i < etype_str.num_strings; i++) {
	    ret = krb5_string_to_enctype(context,
					 etype_str.strings[i],
					 &enctype[i]);
	    if(ret)
		krb5_err(context, 1, ret, "unrecognized enctype: %s",
			 etype_str.strings[i]);
	}
	krb5_get_init_creds_opt_set_etype_list(opt, enctype,
					       etype_str.num_strings);
    }

    ret = krb5_init_creds_init(context, principal,
			       krb5_prompter_posix, NULL,
			       start_time, opt, &icc);
    if (ret)
	krb5_err (context, 1, ret, "krb5_init_creds_init");

    if (server_str) {
	ret = krb5_init_creds_set_service(context, icc, server_str);
	if (ret)
	    krb5_err (context, 1, ret, "krb5_init_creds_set_service");
    }

    if (kdc_hostname)
	krb5_init_creds_set_kdc_hostname(context, icc, kdc_hostname);

    if (fast_armor_cache_string) {
	krb5_ccache fastid;
	
	ret = krb5_cc_resolve(context, fast_armor_cache_string, &fastid);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_cc_resolve(FAST cache)");
	
	ret = krb5_init_creds_set_fast_ccache(context, icc, fastid);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_init_creds_set_fast_ccache");
    }

    if(will_use_keytab) {
	if(keytab_str)
	    ret = krb5_kt_resolve(context, keytab_str, &kt);
	else
	    ret = krb5_kt_default(context, &kt);
	if (ret)
	    krb5_err (context, 1, ret, "resolving keytab");

	ret = krb5_init_creds_set_keytab(context, icc, kt);
	if (ret)
	    krb5_err (context, 1, ret, "krb5_init_creds_set_keytab");
    }

    need_prompt = !(pk_user_id || ent_user_id || anonymous_flag || use_keytab || keytab_str);

    if (interactive && passwd[0] == '\0' && need_prompt) {
	char *p, *prompt;

	krb5_unparse_name(context, principal, &p);
	asprintf (&prompt, N_("%s's Password: "******""), p);
	free(p);

	if (UI_UTIL_read_pw_string(passwd, sizeof(passwd)-1, prompt, 0)){
	    memset(passwd, 0, sizeof(passwd));
	    errx(1, "failed to read password");
	}
	free (prompt);
    }

    if (passwd[0]) {
	ret = krb5_init_creds_set_password(context, icc, passwd);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_init_creds_set_password");
    }

    ret = krb5_init_creds_get(context, icc);

#ifdef __APPLE__
    /*
     * Save password in Keychain
     */
    if (ret == 0 && keychain_flag && passwordItem == NULL) {
	krb5_error_code ret2;
	const char *realm;
	char *name;

	realm = krb5_principal_get_realm(context, principal);
	ret2 = krb5_unparse_name_flags(context, principal, KRB5_PRINCIPAL_UNPARSE_NO_REALM, &name);
	if (ret2 == 0) {
	    (void)SecKeychainAddGenericPassword(NULL,
						(UInt32)strlen(realm), realm,
						(UInt32)strlen(name), name,
						(UInt32)strlen(passwd), passwd,
						NULL);
	    free(name);
	}
    }
#endif

    memset(passwd, 0, sizeof(passwd));

    switch(ret){
    case 0:
	break;
    case KRB5_LIBOS_PWDINTR: /* don't print anything if it was just C-c:ed */
	exit(1);
    case KRB5KRB_AP_ERR_BAD_INTEGRITY:
    case KRB5KRB_AP_ERR_MODIFIED:
    case KRB5KDC_ERR_PREAUTH_FAILED:
    case KRB5_GET_IN_TKT_LOOP:
#ifdef __APPLE__
	if (passwordItem)
	    SecKeychainItemDelete(passwordItem);
#endif
	krb5_errx(context, 1, N_("Password incorrect", ""));
	break;
    case KRB5KRB_AP_ERR_V4_REPLY:
	krb5_errx(context, 1, N_("Looks like a Kerberos 4 reply", ""));
	break;
    case KRB5KDC_ERR_KEY_EXPIRED:
	krb5_errx(context, 1, N_("Password expired", ""));
	break;
    default:
	krb5_err(context, 1, ret, "krb5_get_init_creds");
    }

    ret = krb5_init_creds_get_creds(context, icc, &cred);
    if (ret)
	krb5_err(context, 1, ret, "krb5_init_creds_get_creds");

    krb5_process_last_request(context, opt, icc);

    ret = krb5_cc_new_unique(context, krb5_cc_get_type(context, ccache),
			     NULL, &tempccache);
    if (ret)
	krb5_err (context, 1, ret, "krb5_cc_new_unique");

    ret = krb5_init_creds_store(context, icc, tempccache);
    if (ret)
	krb5_err(context, 1, ret, "krb5_init_creds_store");

    ret = krb5_init_creds_store_config(context, icc, tempccache);
    if (ret)
	krb5_warn(context, ret, "krb5_init_creds_store_config");

    ret = krb5_init_creds_warn_user(context, icc);
    if (ret)
	krb5_warn(context, ret, "krb5_init_creds_warn_user");

    ret = krb5_cc_move(context, tempccache, ccache);
    if (ret) {
	(void)krb5_cc_destroy(context, tempccache);
	krb5_err (context, 1, ret, "krb5_cc_move");
    }

    if (switch_cache_flags)
	krb5_cc_switch(context, ccache);

    if (ok_as_delegate_flag || windows_flag || use_referrals_flag) {
	unsigned char d = 0;
	krb5_data data;

	if (ok_as_delegate_flag || windows_flag)
	    d |= 1;
	if (use_referrals_flag || windows_flag)
	    d |= 2;

	data.length = 1;
	data.data = &d;

	krb5_cc_set_config(context, ccache, NULL, "realm-config", &data);
    }

    if (enctype)
	free(enctype);

    krb5_init_creds_free(context, icc);
    krb5_get_init_creds_opt_free(context, opt);

    if (kt)
	krb5_kt_close(context, kt);

#ifdef __APPLE__
    if (passwordItem)
	CFRelease(passwordItem);
#endif

    return 0;
}