// passing over REPLICATION_LIST configuration parameter, turning all the 
// addresses into canonical <ip:port> form and inserting them all, except for
// the address of local replication daemon, into 'm_replicationDaemonsList'.
void
AbstractReplicatorStateMachine::initializeReplicationList( char* buffer )
{
    StringList replicationAddressList;
    char*      replicationAddress    = NULL;
    bool       isMyAddressPresent    = false;
	Sinful     my_addr( daemonCore->InfoCommandSinfulString( ) );

    replicationAddressList.initializeFromString( buffer );
    // initializing a list unrolls it, that's why the rewind is needed to bring
    // it to the beginning
    replicationAddressList.rewind( );
    /* Passing through the REPLICATION_LIST configuration parameter, stripping
     * the optional <> brackets off, and extracting the host name out of
     * either ip:port or hostName:port entries
     */
    while( (replicationAddress = replicationAddressList.next( )) ) {
        char* sinfulAddress = utilToSinful( replicationAddress );

        if( sinfulAddress == NULL ) {
            char bufArray[BUFSIZ];

			sprintf( bufArray, 
					"AbstractReplicatorStateMachine::initializeReplicationList"
                    " invalid address %s\n", replicationAddress );
            utilCrucialError( bufArray );

            continue;
        }
        if( my_addr.addressPointsToMe( Sinful(sinfulAddress) ) ) {
            isMyAddressPresent = true;
        }
        else {
            m_replicationDaemonsList.insert( sinfulAddress );
        }
        // pay attention to release memory allocated by malloc with free and by
        // new with delete here utilToSinful returns memory allocated by malloc
        free( sinfulAddress );
    }

    if( !isMyAddressPresent ) {
        utilCrucialError( "ReplicatorStateMachine::initializeReplicationList "
                          "my address is not present in REPLICATION_LIST" );
    }
}