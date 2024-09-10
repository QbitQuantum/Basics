	// When you create a ChatterSession it waits to accept a
	// connection.  This is done by it's own
	ChatterSession(
	TCPSocket      & server,
	SocketService	* svc,
	ts_list_head	* head
	) :
	SocketPort( NULL, server ),
	ts_list_item( head ) {
	cerr << "ChatterSession Created\n";

	tpport_t port;
	InetHostAddress ia = getPeer( & port );

	cerr << "connecting from " << ia.getHostname() <<
	":" << port << endl;

	// Set up non-blocking reads
	setCompletion( false );

	// Set yerself to time out in 10 seconds
	setTimer( 100000 );
	attach(svc);
	}