void
DaemonList::init( daemon_t type, const char* host_list, const char* pool_list )
{
	Daemon* tmp;
	char* host;
	char const *pool = NULL;
	StringList foo;
	StringList pools;
	if( host_list ) {
		foo.initializeFromString( host_list );
		foo.rewind();
	}
	if( pool_list ) {
		pools.initializeFromString( pool_list );
		pools.rewind();
	}
	while( true ) {
		host = foo.next();
		pool = pools.next();
		if( !host && !pool ) {
			break;
		}
		tmp = buildDaemon( type, host, pool );
		append( tmp );
	}
}