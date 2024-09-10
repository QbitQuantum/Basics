int
main(int argc, char **argv)
{
    krb5_context context;
    krb5_principal princ;
    krb5_salt salt;
    int optidx;
    char buf[1024];
    krb5_enctype etype;
    krb5_error_code ret;

    optidx = krb5_program_setup(&context, argc, argv, args, num_args, NULL);

    if(help)
	usage(0);

    if(version){
	print_version (NULL);
	return 0;
    }

    argc -= optidx;
    argv += optidx;

    if (argc > 1)
	usage(1);

    if(!version5 && !version4 && !afs)
	version5 = 1;

    ret = krb5_string_to_enctype(context, keytype_str, &etype);
    if(ret)
	krb5_err(context, 1, ret, "krb5_string_to_enctype");

    if((etype != (krb5_enctype)ETYPE_DES_CBC_CRC &&
	etype != (krb5_enctype)ETYPE_DES_CBC_MD4 &&
	etype != (krb5_enctype)ETYPE_DES_CBC_MD5) &&
       (afs || version4)) {
	if(!version5) {
	    etype = ETYPE_DES_CBC_CRC;
	} else {
	    krb5_errx(context, 1,
		      "DES is the only valid keytype for AFS and Kerberos 4");
	}
    }

    if(version5 && principal == NULL){
	printf("Kerberos v5 principal: ");
	if(fgets(buf, sizeof(buf), stdin) == NULL)
	    return 1;
	buf[strcspn(buf, "\r\n")] = '\0';
	principal = estrdup(buf);
    }
    if(afs && cell == NULL){
	printf("AFS cell: ");
	if(fgets(buf, sizeof(buf), stdin) == NULL)
	    return 1;
	buf[strcspn(buf, "\r\n")] = '\0';
	cell = estrdup(buf);
    }
    if(argv[0])
	password = argv[0];
    if(password == NULL){
	if(UI_UTIL_read_pw_string(buf, sizeof(buf), "Password: "******"failed to unparse name: %s", principal);
	ret = krb5_get_pw_salt(context, princ, &salt);
	if (ret)
	    krb5_err(context, 1, ret, "failed to get salt for %s", principal);

	tokey(context, etype, password, salt, "Kerberos 5 (%s)");
	krb5_free_salt(context, salt);
    }
    if(version4){
	salt.salttype = KRB5_PW_SALT;
	salt.saltvalue.length = 0;
	salt.saltvalue.data = NULL;
	tokey(context, ETYPE_DES_CBC_MD5, password, salt, "Kerberos 4");
    }
    if(afs){
	salt.salttype = KRB5_AFS3_SALT;
	salt.saltvalue.length = strlen(cell);
	salt.saltvalue.data = cell;
	tokey(context, ETYPE_DES_CBC_MD5, password, salt, "AFS");
    }
    return 0;
}