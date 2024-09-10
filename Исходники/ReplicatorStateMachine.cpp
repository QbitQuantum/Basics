void
ReplicatorStateMachine::initializeClassAd()
{
    if( m_classAd != NULL) {
        delete m_classAd;
        m_classAd = NULL;
    }

    m_classAd = new ClassAd();

    SetMyTypeName(*m_classAd, "Replication");
    SetTargetTypeName(*m_classAd, "");

    m_name.formatstr( "replication@%s -p %d", get_local_fqdn().Value(),
				  daemonCore->InfoCommandPort( ) );
    m_classAd->Assign( ATTR_NAME, m_name.Value( ) );
    m_classAd->Assign( ATTR_MY_ADDRESS,
					   daemonCore->InfoCommandSinfulString( ) );

    // publish list of replication nodes
    char* buffer = param( "REPLICATION_LIST" );
	if ( NULL == buffer ) {
		EXCEPT( "ReplicatorStateMachine: No replication list!!" );
	}
    char* replAddress = NULL;
    StringList replList;
    MyString attrReplList;
    MyString comma;

    replList.initializeFromString( buffer );
    replList.rewind( );

    while( ( replAddress = replList.next() ) ) {
        attrReplList += comma;
        attrReplList += replAddress;
        comma = ",";
    }
    m_classAd->Assign( ATTR_REPLICATION_LIST, attrReplList.Value( ) );

    // publish DC attributes
    daemonCore->publish(m_classAd);
	free(buffer);
}