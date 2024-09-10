static char*
check_ldap_auth(LD_session *session, char *login, unsigned char *password, char *fullname) {
	int rc = 0, count = 0;
	char logbuf[MAXLOGBUF];
	LDAPMessage *res, *entry;
	char *attr, *dn;
	BerElement * ber;
	struct berval **list_of_values;
	struct berval value;
	char *validgroups;
	char filter[MAXFILTERSTR];
	struct berval cred_user;

	/* Check authorization */
	memset(filter, 0, 100);
	snprintf(filter, MAXLOGBUF, "(&(objectClass=posixGroup)(memberUid=%s))", login);


	cred_user.bv_val = (const char *)password;
	cred_user.bv_len = strlen(cred_user.bv_val);

#if LDAP_API_VERSION > 3000	
	if((rc = ldap_sasl_bind_s(session->sess, fullname, ldap_authorization_type, &cred_user, NULL, NULL, NULL))!=LDAP_SUCCESS) {
		snprintf(logbuf, MAXLOGBUF, "Ldap server %s authentificate with method %s failed: %s", ldap_authorization_host, ldap_authorization_type, ldap_err2string(rc));  
		ldap_log(LOG_DEBUG, logbuf);
		return RETURN_TRUE;
	};
#else	
	if((rc = ldap_bind_s(session->sess, fullname, password, LDAP_AUTH_SIMPLE))!=LDAP_SUCCESS) {
		snprintf(logbuf, MAXLOGBUF, "Ldap server %s authentificate failed: %s", ldap_authorization_host, ldap_err2string(rc));  
		ldap_log(LOG_DEBUG, logbuf);
		return RETURN_TRUE;
	}
#endif

	if ((rc = ldap_search_ext_s(session->sess, ldap_authorization_basedn, LDAP_SCOPE_SUBTREE, filter, NULL, 0, NULL, NULL, NULL, LDAP_NO_LIMIT, &res)) != LDAP_SUCCESS) {
#if LDAP_API_VERSION > 3000
		ldap_unbind_ext(session->sess, NULL, NULL);
#else   
		ldap_unbind(session->sess);
#endif
		return RETURN_TRUE;
	}

	for (entry = ldap_first_entry(session->sess,res); entry!=NULL && count<=ldap_count_messages(session->sess, res); entry=ldap_next_entry(session->sess, res)) {
		count++;
		for(attr = ldap_first_attribute(session->sess,entry,&ber); attr != NULL ; attr=ldap_next_attribute(session->sess,entry,ber)) {
			snprintf(logbuf, MAXLOGBUF, "Found attribute %s", attr);        
			ldap_log(LOG_DEBUG, logbuf); 
			if (strcmp(attr, "cn"))
				continue;
			if ((list_of_values = ldap_get_values_len(session->sess, entry, attr)) != NULL ) {
				value = *list_of_values[0];
				char temp[MAXGROUPLIST];
				memset(temp, 0, MAXGROUPLIST);
				if (ldap_authorization_validgroups) {
					strcpy(temp, ldap_authorization_validgroups);
					validgroups = strtok(temp, ",");
					while (validgroups != NULL)
					{
						snprintf(logbuf, MAXLOGBUF, "Attribute value validgroups ? value.bv_val >> %s ? %s", validgroups, value.bv_val);        
						ldap_log(LOG_DEBUG, logbuf); 
						if (!strcmp(validgroups, value.bv_val))
						{
							ldap_msgfree(res);
#if LDAP_API_VERSION > 3000
							ldap_unbind_ext(session->sess, NULL, NULL);
#else   
							ldap_unbind(session->sess);
#endif
							dn = malloc((int)strlen(value.bv_val)*sizeof(char));
							memset(dn, 0, (int)strlen(value.bv_val)*sizeof(char));
							strcpy(dn, value.bv_val);
							return dn;
						}
						validgroups = strtok (NULL, ",");
					}
//					printf("VAL: %s\n", value.bv_val);
					ldap_value_free_len( list_of_values );
				}
			}
		}
		res = ldap_next_message(session->sess, res);
	};
	ldap_msgfree(res);
#if LDAP_API_VERSION > 3000
	ldap_unbind_ext(session->sess, NULL, NULL);
#else   
	ldap_unbind(session->sess);
#endif
	return RETURN_TRUE;
}