unsigned int
GetUserLevel(LDAP *ld,char *user)
{

	LDAPMessage        *res, *e;
	char               *a;
	BerElement         *ptr;
	char               **vals;
	unsigned int ret;
	
	char *filter = GetClientFilter(user);
	
	if (ldap_search_s(ld, CLIENT_PATH, LDAP_SCOPE_SUBTREE,filter, NULL, 0, &res)!= LDAP_SUCCESS) {
		printf("%s\n",filter);
		ldap_perror(ld, "ldap_search_s");
		exit(1);
	}
	
	if( (e=ldap_first_entry(ld, res)) == NULL )
	   fprintf(stderr, "LDAP error: user not found");

	a = ldap_first_attribute(ld, e, &ptr);
	while( strcmp(a,"internationaliSDNNumber") != 0 )
		a = ldap_next_attribute(ld, e, ptr);
	   
	vals = ldap_get_values(ld, e, a);	
	ret = atoi(vals[0]);		
	/* free the search results */
	ldap_msgfree(res);
	return ret;
}