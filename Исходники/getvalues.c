int
ldap_count_values_len( struct berval **vals )
{
	return( ldap_count_values( (char **) vals ) );
}