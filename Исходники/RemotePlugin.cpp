bool RemotePlugin::processMessage( const message & _m )
{
	lock();
	message replyMessage( _m.id );
	bool reply = false;
	switch( _m.id )
	{
		case IdUndefined:
			return false;

		case IdInitDone:
			reply = true;
			break;

		case IdSampleRateInformation:
			reply = true;
			replyMessage.addInt( engine::getMixer()->processingSampleRate() );
			break;

		case IdBufferSizeInformation:
			reply = true;
			replyMessage.addInt( engine::getMixer()->framesPerPeriod() );
			break;

		case IdChangeInputCount:
			m_inputCount = _m.getInt( 0 );
			resizeSharedProcessingMemory();
			break;

		case IdChangeOutputCount:
			m_outputCount = _m.getInt( 0 );
			resizeSharedProcessingMemory();
			break;

		case IdDebugMessage:
			fprintf( stderr, "RemotePlugin::DebugMessage: %s",
						_m.getString( 0 ).c_str() );
			break;

		case IdProcessingDone:
		case IdQuit:
		default:
			break;
	}
	if( reply )
	{
		sendMessage( replyMessage );
	}
	unlock();

	return true;
}