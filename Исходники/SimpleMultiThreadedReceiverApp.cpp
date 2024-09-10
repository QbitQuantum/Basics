void SimpleMultiThreadedReceiverApp::setup()
{
	mReceiver.setListener( "/mousemove/1",
	[&]( const osc::Message &msg ){
		std::lock_guard<std::mutex> lock( mCirclePosMutex );
		mCurrentCirclePos.x = msg[0].int32();
		mCurrentCirclePos.y = msg[1].int32();
	});
	mReceiver.setListener( "/mouseclick/1",
	[&]( const osc::Message &msg ){
		std::lock_guard<std::mutex> lock( mSquarePosMutex );
		mCurrentSquarePos = vec2( msg[0].flt(), msg[1].flt() ) * vec2( getWindowSize() );
	});
	
	mReceiver.bind();
	mReceiver.listen();
	
	mThread = std::thread( std::bind(
	[]( std::shared_ptr<asio::io_service> &service ){
		service->run();
	}, mIoService ));
}