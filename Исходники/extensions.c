int ldap_parse_page_control(LDAP *ld, LDAPControl **controls, unsigned int *totalcount, struct berval **cookie)
{
	int i, rc;
	BerElement *theBer;
	LDAPControl *listCtrlp;
	
	for (i = 0; controls[i] != NULL; i++){
		if (strcmp(controls[i]->ldctl_oid, "1.2.840.113556.1.4.319") == 0) {
			listCtrlp = controls[i];
			if ((theBer = ber_init(&listCtrlp->ldctl_value)) == NULLBER){
				return (LDAP_NO_MEMORY);
			}
			if ((rc = ber_scanf(theBer, "{iO}", totalcount, cookie)) == LBER_ERROR){
				ber_free(theBer, 1);
				return (LDAP_DECODING_ERROR);
			}
			ber_free(theBer, 1);
			return (LDAP_SUCCESS);
		}
	}
	return (LDAP_CONTROL_NOT_FOUND);
}