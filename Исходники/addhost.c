static void ldap_dump(LDAP *ld,LDAPMessage *res)
{
	LDAPMessage *e;
    
	for (e = ldap_first_entry(ld, res); e; e = ldap_next_entry(ld, e)) {
		BerElement *b;
		char *attr;
		char *dn = ldap_get_dn(ld, res);
		if (dn)
			printf("dn: %s\n", dn);
		ldap_memfree(dn);

		for (attr = ldap_first_attribute(ld, e, &b); 
		     attr;
		     attr = ldap_next_attribute(ld, e, b)) {
			char **values, **p;
			values = ldap_get_values(ld, e, attr);
			for (p = values; *p; p++) {
				printf("%s: %s\n", attr, *p);
			}
			ldap_value_free(values);
			ldap_memfree(attr);
		}

		ber_free(b, 1);
		printf("\n");
	}
}