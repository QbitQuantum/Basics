// }}}
// {{{AuthLDAP
bool AuthLDAP::setup()
{
	LDAPURLDesc* urlDescription;
	LDAP* ldap;
	std::string url("dc=trapni,dc=de");

	int rv = ldap_url_parse(url.c_str(), &urlDescription);
	if (rv != LDAP_SUCCESS) {
		return false;
	}

	int ldapVersion = LDAP_VERSION3;
	ldap_set_option(nullptr, LDAP_OPT_PROTOCOL_VERSION, &ldapVersion);

	timeval timeout = { 10, 0 };
	ldap_set_option(nullptr, LDAP_OPT_NETWORK_TIMEOUT, &timeout);

	int reqcert = LDAP_OPT_X_TLS_ALLOW;
    ldap_set_option(NULL, LDAP_OPT_X_TLS_REQUIRE_CERT, &reqcert);

	rv = ldap_initialize(&ldap, url.c_str());
}