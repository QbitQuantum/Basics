CLSID ServerConnection::getCLSID()
{
	FRL_EXCEPT_GUARD();
	CLSID server_clsid = GUID_NULL;
	#if( FRL_CHARACTER == FRL_CHARACTER_UNICODE )
		if( FAILED(CLSIDFromProgID( server_id.c_str(), &server_clsid)) )
		{
			if( UuidFromString( (unsigned short*)server_id.c_str(), &server_clsid) != RPC_S_OK )
				FRL_THROW_S_CLASS( NotResolveProgID );
		}
	#else
		if( FAILED(CLSIDFromProgID( string2wstring( server_id ).c_str(), &server_clsid)) )
		{
			if( UuidFromString( (unsigned char*)server_id.c_str(), &server_clsid) != RPC_S_OK )
				FRL_THROW_S_CLASS( NotResolveProgID );
		}	
	#endif // FRL_CHARACTER_UNICODE
	return server_clsid;
}