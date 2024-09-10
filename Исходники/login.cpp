int login::proof()
{
	
	/* setup LDAP connection */
	if((ld=ldap_init(LDAP_HOST, LDAP_PORT)) == NULL) {
		perror("ldap_init failed");
		return EXIT_FAILURE;
	}
	printf("\nconnected to LDAP server %s on port %d\n",LDAP_HOST,LDAP_PORT);
	
	/* non-anonymous bind from home */
	rc = ldap_simple_bind_s(ld,BIND_USER,BIND_PW);
	
	if(rc != LDAP_SUCCESS) {
		fprintf(stderr,"\nLDAP error: %s\n",ldap_err2string(rc));
		return EXIT_FAILURE;
	} else {
		printf("\npretended anonymous bind successful\n");
	}
	
	/* perform LDAP search */
	rc = ldap_search_s(ld, SEARCHBASE, SCOPE, filter_c, attribs, 0, &result);
	
	if(rc != LDAP_SUCCESS) {
		fprintf(stderr,"\nLDAP search error: %s\n",ldap_err2string(rc));
		return EXIT_FAILURE;
	}else{
		printf("\nTotal results: %d\n", ldap_count_entries(ld, result));
		if(ldap_count_entries(ld,result) < 1) {
			fprintf(stderr,"\nUser nicht gefunden!\n");
			return EXIT_FAILURE;
		}
	}
	
	e = ldap_first_entry(ld, result);
	found = ldap_get_dn(ld,e);
	printf("\nDN: %s\n",found);
	
	/* User anmelden */
	rc = ldap_simple_bind_s(ld,found,passwd_c);
	
	if(rc != LDAP_SUCCESS) {
		fprintf(stderr,"\nLDAP error: %s\n",ldap_err2string(rc));
		return EXIT_FAILURE;
	} else {
		printf("\nbind successful\n");
	}
	
	
	/* free memory used for result */
	ldap_msgfree(result);
	free(attribs[0]);
	free(attribs[1]);
	printf("\nLDAP login succeeded\n");
	
	ldap_unbind(ld);
	return EXIT_SUCCESS;
}