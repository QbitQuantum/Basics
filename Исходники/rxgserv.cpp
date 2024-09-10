//-----------------------------------------------------------------------------
void NetHandler::Accepted( Net::StreamPtr &stream ) {
	System::Log( "A client connected: address \"%s\"", 
		stream->GetHostname().c_str() );
}