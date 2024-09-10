void SimpleReceiverApp::setup()
{
	mReceiver.setListener( "/mousemove/1",
	[&]( const osc::Message &msg ){
		mCurrentCirclePos.x = msg[0].int32();
		mCurrentCirclePos.y = msg[1].int32();
	});
	mReceiver.setListener( "/mouseclick/1",
	[&]( const osc::Message &msg ){
		mCurrentSquarePos = vec2( msg[0].flt(), msg[1].flt() ) * vec2( getWindowSize() );
	});
	mReceiver.bind();
	mReceiver.listen();
}