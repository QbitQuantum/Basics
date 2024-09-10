	void send_sysmessage_cl_affix( Client *client, unsigned int cliloc_num, const char* affix,
								   bool prepend, const u16 *arguments, unsigned short font,
								   unsigned short color )
	{
	  PktHelper::PacketOut<PktOut_CC> msg;
	  msg->offset += 2;
	  unsigned textlen = 0, affix_len = 0;

	  if ( arguments != NULL )
	  {
		while ( arguments[textlen] != L'\0' )
		  ++textlen;
	  }
	  affix_len = static_cast<unsigned>( strlen( affix ) + 1 );
	  if ( affix_len > SPEECH_MAX_LEN + 1 )
		affix_len = SPEECH_MAX_LEN + 1;

	  if ( textlen > ( SPEECH_MAX_LEN ) )
		textlen = SPEECH_MAX_LEN;

	  msg->Write<u32>( 0xFFFFFFFFu ); // serial
	  msg->Write<u16>( 0xFFFFu );     // body
	  msg->Write<u8>( 6u );           // type 6 lower left, 7 on player
	  msg->WriteFlipped<u16>( color );
	  msg->WriteFlipped<u16>( font );
	  msg->WriteFlipped<u32>( cliloc_num );
	  msg->Write<u8>( ( prepend ) ? 1u : 0u );
	  msg->Write( "System", 30, false );
	  msg->Write( affix, static_cast<u16>( affix_len ) );
	  if ( arguments != NULL )
		msg->WriteFlipped( arguments, static_cast<u16>( textlen ), true );
	  else
		msg->offset += 2;
	  u16 len = msg->offset;
	  msg->offset = 1;
	  msg->WriteFlipped<u16>( len );
	  msg.Send( client, len );
	}