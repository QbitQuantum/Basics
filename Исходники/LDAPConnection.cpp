/**
 * The public method auth authenticats the user with username and password
 * Parameters:
 * 		std::string *username: a reverence to the username
 * 		std::string *pw: a reverence to the password
 * Return:
 * 		bool: true if auth successfull
 */
bool LDAPConnection::auth(std::string *username, std::string *pw){
	int rc = 0;
	LDAPMessage *result, *entry;
	std::string filter = "(uid=";
	filter.append(*username);
	filter.append(")");

	//searches for user
	rc = ldap_search_s(this->ld, SEARCHBASE, SCOPE, filter.c_str(), this->attribs, 0, &result);
	if(rc != LDAP_SUCCESS){
		std::cout << ldap_err2string(rc) << std::endl;
		ldap_msgfree(result);
		return false;
	}

	//counts results
	if(ldap_count_entries(this->ld, result) != 1){
		ldap_msgfree(result);
		return false;
	}

	//gets user dn
	entry = ldap_first_entry(this->ld, result);
	std::string dn = ldap_get_dn(this->ld,entry);
	ldap_msgfree(result);

	//initializes a new ldap connection
	LDAP *ldp;
	ldap_initialize(&ldp, LDAP_HOST);
	if(ldp == NULL){
		return false;
	}

	//tries to bind the user
	rc = ldap_simple_bind_s(ldp, dn.c_str(), pw->c_str());

	if(rc != LDAP_SUCCESS){
		ldap_unbind(ldp);
		return false;
	}

	//closes the new ldap connection
	ldap_unbind(ldp);
	return true;
}