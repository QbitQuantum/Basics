void LDAPSession::stringSearch ( string dn,const list<string> &attributes,
                                 string searchParam,
                                 list<LDAPStringEntry>& result )
{
	char** attr;
	attr= ( char** ) malloc ( sizeof ( char* ) *attributes.size() +1 );
	int i=0;
	list<string>::const_iterator it=attributes.begin();
	list<string>::const_iterator end=attributes.end();
	for ( ;it!=end;++it )
	{
		attr[i]= ( char* ) malloc ( sizeof ( char ) *
		                            ( *it ).length() +1 );
		strcpy ( attr[i], ( *it ).c_str() );
		++i;
	}
	attr[i]=0l;
	LDAPMessage* res;
	int errc=ldap_search_s ( ld,dn.c_str(),LDAP_SCOPE_SUBTREE,
	                         searchParam.c_str(),attr,0,&res );
	if ( errc != LDAP_SUCCESS )
	{
		i=0;
		it=attributes.begin();
		for ( ;it!=end;++it )
		{
			free ( attr[i] );
			++i;
		}
		free ( attr );
		throw LDAPExeption ( "ldap_search_s",ldap_err2string ( errc ) );
	}
	LDAPMessage *entry=ldap_first_entry ( ld,res );
	while ( entry )
	{
		LDAPStringEntry stringEntry;
		it=attributes.begin();
		for ( ;it!=end;++it )
		{
			LDAPStringValue val;
			val.attr= ( *it );
			char **atr=ldap_get_values ( ld,entry,
			                             ( *it ).c_str() );
			int count=ldap_count_values ( atr );
			for ( i=0;i<count;i++ )
			{
				val.value.push_back ( atr[i] );
			}
			ldap_value_free ( atr );
			stringEntry.push_back ( val );
		}
		entry=ldap_next_entry ( ld,entry );
		result.push_back ( stringEntry );
	}
	free ( res );
	i=0;
	it=attributes.begin();
	for ( ;it!=end;++it )
	{
		free ( attr[i] );
		++i;
	}
	free ( attr );
}