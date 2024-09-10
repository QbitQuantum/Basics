//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string LDAP_UNX::getDistinguishedName( const std::string userID,
	std::string *dname )
{
	*dname = "";
	LDAP *ldap = NULL;	// INITIALISE AND CONNECT TO LDAP SERVER
	std::string	e = initialize( &ldap );
	if ( ! e.empty() )
		{return( e );
		}
	std::string	base = ou + "," + dc;
	std::string	bparam = std::string("CN=LDAPbind,") + base;
	const	int 	ibind = ldap_simple_bind_s( ldap, bparam.c_str(),
		ldap_pw.c_str() );
	if ( ibind != LDAP_SUCCESS )
		{sprintf( ebuf, "ldap_simple_bind_s=%d", ibind );
		return( std::string(ebuf) );
		}
/* SEARCH FOR ENTRY WITH sAMAccountName AS GIVEN BY USER AND GET
 distinguishedName IF IT EXISTS (IF FOUND, THEN USERNAME EXISTS) */
	LDAPMessage *res = ( LDAPMessage * )NULL;
	std::string filter = "(sAMAccountName=" + userID + ")";
	const	int	isearch = ldap_search_s( ldap, base.c_str(),
		LDAP_SCOPE_ONELEVEL, filter.c_str(), ( char ** )NULL, 0, &res );
	if ( isearch != LDAP_SUCCESS )
		{sprintf( ebuf, "ldap_search_s=%d", isearch );
		return( std::string(ebuf) );
		}
	const	int	nentries = ldap_count_entries( ldap, res );
	if ( nentries <= 0 )
		{    // FAILED TO FIND distinguishedName from sAMAccountName
		ldap_msgfree( res );
		ldap_unbind_s( ldap );
		return( "Username not found in LDAP-OU" );
		}
					    // EXTRACT distinguishedNAme
	char 	*dn = ldap_get_dn( ldap, ldap_first_entry( ldap, res ) );
	*dname = std::string( dn );
	ldap_memfree( dn );			    		// TIDY UP
	ldap_msgfree( res );
	ldap_unbind_s( ldap );   			// DROP ASSOCIATION
	return( "" );
 }