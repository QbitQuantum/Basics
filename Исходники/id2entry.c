int wt_id2entry_delete(
	Operation *op,
	WT_SESSION *session,
	Entry *e )
{
	int rc;
	WT_CURSOR *cursor = NULL;
	rc = session->open_cursor(session, WT_TABLE_ID2ENTRY, NULL,
							  NULL, &cursor);
	if ( rc ) {
		Debug( LDAP_DEBUG_ANY,
			   LDAP_XSTRING(wt_id2entry_delete)
			   ": open_cursor failed: %s (%d)\n",
			   wiredtiger_strerror(rc), rc, 0 );
		goto done;
	}
	cursor->set_key(cursor, e->e_id);
	rc = cursor->remove(cursor);
	if ( rc ) {
		Debug( LDAP_DEBUG_ANY,
			   LDAP_XSTRING(wt_id2entry_delete)
			   ": remove failed: %s (%d)\n",
			   wiredtiger_strerror(rc), rc, 0 );
		goto done;
	}

done:
	if(cursor){
		cursor->close(cursor);
	}
	return rc;
}