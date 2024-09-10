/*
  dump a record from LDAP on stdout
  used for debugging
*/
void ads_dump(ADS_STRUCT *ads, LDAPMessage *res)
{
	char *field;
	LDAPMessage *msg;
	BerElement *b;
	char *this_dn;
    
	for (msg = ldap_first_entry(ads->ld, res); 
	     msg; msg = ldap_next_entry(ads->ld, msg)) {
		this_dn = ldap_get_dn(ads->ld, res);
		if (this_dn) {
			printf("Dumping: %s\n", this_dn);
		}
		ldap_memfree(this_dn);

		for (field = ldap_first_attribute(ads->ld, msg, &b); 
		     field;
		     field = ldap_next_attribute(ads->ld, msg, b)) {
			char **values, **p;
			values = ldap_get_values(ads->ld, msg, field);
			for (p = values; *p; p++) {
				printf("%s: %s\n", field, *p);
			}
			ldap_value_free(values);
			ldap_memfree(field);
		}

		ber_free(b, 1);
		printf("\n");
	}
}