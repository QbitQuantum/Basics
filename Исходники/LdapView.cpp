// Fetch all attributes of an entry, and display them in a dialog
void LdapView::showProperties( LDAP *ld, char *dn )
{
	PropDlg dlg;
	if ( ldap_search( ld, dn, LDAP_SCOPE_BASE, "objectclass=*",
				NULL, FALSE ) == -1 )
	{
		AfxMessageBox( "Failed to start asynchronous search" );
		return;
	}

	LDAPMessage *res;
	int rc;
	// Process results as they come in
	while ( (rc = ldap_result( ld, LDAP_RES_ANY, 0, NULL, &res ))
		== LDAP_RES_SEARCH_ENTRY )
	{
		LDAPMessage *e = ldap_first_entry( ld, res );
		BerElement		*ber;
		// Loop over attributes in this entry
		for ( char *a = ldap_first_attribute( ld, e, &ber ); a != NULL;
				a = ldap_next_attribute( ld, e, ber ) )
		{
			struct berval **bvals;
			if ( (bvals = ldap_get_values_len( ld, e, a )) != NULL )
			{
				dlg.AddLine( a );
				// Loop over values for this attribute
				for ( int i = 0; bvals[i] != NULL; i++ )
				{
					CString val;
					val.Format( "    %s", bvals[ i ]->bv_val );
					dlg.AddLine( val );
				}
				ber_bvecfree( bvals );
			}
		}
		if ( ber != NULL )
			ber_free( ber, 0 );
		ldap_msgfree( res );
	}
	if ( rc == -1 )
	{
		AfxMessageBox( "Error on ldap_result" );
		return;
	}
	else if (( rc = ldap_result2error( ld, res, 0 )) != LDAP_SUCCESS )
	{
		char *errString = ldap_err2string( rc );
		AfxMessageBox( errString );
	}
	ldap_msgfree( res );
	// Set the title of the dialog to the distinguished name, and display it
	dlg.SetTitle( dn );
	dlg.DoModal();
}