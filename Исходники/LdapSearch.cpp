void LdapSearch::timerEvent( QTimerEvent *e )
{
	LDAPMessage *result = 0;
	LDAP_TIMEVAL t = { 5, 0 };
	int err = ldap_result( d->ldap, d->msg_id, LDAP_MSG_ALL, &t, &result );
	switch( err )
	{
	case LDAP_SUCCESS: //Timeout
		return;
	case LDAP_RES_SEARCH_ENTRY:
	case LDAP_RES_SEARCH_RESULT:
		break;
	default:
		setLastError( tr("Failed to get result"), err );
		killTimer( e->timerId() );
		return;
	}
	killTimer( e->timerId() );

	QList<QSslCertificate> list;
	for( LDAPMessage *entry = ldap_first_entry( d->ldap, result );
		 entry; entry = ldap_next_entry( d->ldap, entry ) )
	{
		BerElement *pos = 0;
		for( char *attr = ldap_first_attribute( d->ldap, entry, &pos );
			 attr; attr = ldap_next_attribute( d->ldap, entry, pos ) )
		{
			if( qstrcmp( attr, "userCertificate;binary" ) == 0 )
			{
				berval **cert = ldap_get_values_len( d->ldap, entry, attr );
				for( ULONG i = 0; i < ldap_count_values_len( cert ); ++i )
					list << QSslCertificate( QByteArray( cert[i]->bv_val, cert[i]->bv_len ), QSsl::Der );
				ldap_value_free_len( cert );
			}
			ldap_memfree( attr );
		}
		ber_free( pos, 0 );
	}
	ldap_msgfree( result );

	Q_EMIT searchResult( list );
}