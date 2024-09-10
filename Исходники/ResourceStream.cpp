//-----------------------------------------------------------------------------------------------
void ResourceStream::WriteAABB2( const AABB2& data, const char* optionalLabel )
{
	if( m_internalFormat == RESOURCE_STREAM_FORMAT_BINARY )
	{
		// DEBUGGING - { int q = 5; } //ConsolePrintf( "WriteAABB2: value=(%g,%g),(g,%g), at offset %d (\"%s\")\n", data.mins.x, data.mins.y, data.maxs.x, data.maxs.y, m_dataBytesAvailable, optionalLabel ? optionalLabel : "" );
		WriteBinaryType( data );
		return;
	}

	std::string asText;
	Sprintf( asText, "AABB2[(%g,%g),(%g,%g)] ", data.mins.x, data.mins.y, data.maxs.x, data.maxs.y );
	WriteStringIndentedIfNeeded( asText );
	WriteLineEndIfVerbose( optionalLabel );
}