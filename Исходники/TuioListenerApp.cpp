void TuioClientApp::setup()
{
	// Create your osc receiver with whatever configuration needed. In this case we'll open it up
	// with the Default Tuio Port - 3333.
	mOscReceiver = std::make_shared<osc::ReceiverUdp>( tuio::Receiver::DEFAULT_TUIO_PORT );

	// Create the Tuio Receiver passing the Osc Receiver's pointer. 
	mTuio = std::make_shared<tuio::Receiver>( mOscReceiver.get() );
	// Add your tuio callbacks.
	mTuio->setAddedFn<tuio::Cursor2d>( std::bind( &TuioClientApp::added, this, std::placeholders::_1 ) );
	mTuio->setUpdatedFn<tuio::Cursor2d>( std::bind( &TuioClientApp::updated, this, std::placeholders::_1 ) );
	mTuio->setRemovedFn<tuio::Cursor2d>( std::bind( &TuioClientApp::removed, this, std::placeholders::_1 ) );
	// Bind the Osc Receiver...
	try {
		mOscReceiver->bind();
	}
	catch( const ci::Exception &ex ) {
		CI_LOG_EXCEPTION( "OscReceiver bind", ex );
		quit();
	}
	// And listen for messages.
	mOscReceiver->listen( 
	[]( asio::error_code ec, asio::ip::udp::endpoint ep ) -> bool {
		if( ec ) {
			CI_LOG_E( "Error on listener: " << ec.message() << " Error Value: " << ec.value() );
			return false;
		}
		else
			return true;
	} );
}