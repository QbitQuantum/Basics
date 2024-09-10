bool BindTheDemon(const char * username, const char * passwd)
{
	static LDAP * ld = NULL;
	

	static int auth_method = LDAP_AUTH_SIMPLE;
	static int version = LDAP_VERSION3;
	static char uri[] = "ldaps://ldap.pheme.uwa.edu.au";
	char dn[BUFSIZ]; // The "dn" is essentially the username plus a bunch of cruft that for some (presumably good) reason LDAP requires

	if (ld == NULL)
	{
		ldap_initialize(&ld, uri); // This is deprecated.
		if (ld == NULL)
		{
			fprintf(stderr, "ldap_init failed - %s\n", strerror(errno));
			return false;
		}

		printf("ldap_init succeeded\n");
		if (ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version) != LDAP_OPT_SUCCESS) // This is also deprecated.
		{
			fprintf(stderr, "ldap_set_option failed - %s\n", strerror(errno));
			return false;
		}

		printf("ldap_set_option succeeded\n");
	}

	char * user_type = "Students";
	if (username[0] == '0')
		user_type = "Staff";

	if (sprintf(dn, "cn=%s,ou=%s,ou=Users,ou=UWA,dc=uwads,dc=uwa,dc=edu,dc=au", username, user_type) >= BUFSIZ)
	{
		fprintf(stderr, "LDAP DN string too long!\n");
		return false;
	}

	printf("ldap_bind_s ...\n");

	//printf("dn = %s\npasswd = %s\n", dn, passwd);

	struct berval creds;
	creds.bv_val = (char*)passwd;
	if (ldap_simple_bind_s(ld, dn, passwd) != LDAP_SUCCESS) // Yep. Deprecated.
	//if (ldap_sasl_bind_s(ld, dn, LDAP_SASL_SIMPLE , &creds, NULL, NULL, NULL) != LDAP_SUCCESS) // Doesn't work
	{
		fprintf(stderr,"ldap_bind_s failed - %s", strerror(errno));
		return false;
	}
	return true;

}