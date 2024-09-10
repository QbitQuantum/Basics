int NetUtils::FindNumberOfLocalNetworkInterfaces( void )
{
    PIP_ADAPTER_INFO pAdapterInfo = new IP_ADAPTER_INFO;
    unsigned long output_buffer_len = sizeof(IP_ADAPTER_INFO);

    // Make call to GetAdaptersInfo to get number of addapters
    DWORD ret = GetAdaptersInfo( pAdapterInfo, &output_buffer_len );
    delete pAdapterInfo;
    if( (ret == ERROR_BUFFER_OVERFLOW) || (ret == ERROR_SUCCESS) ) {
		int nif = output_buffer_len / sizeof(IP_ADAPTER_INFO);
		if( output_buffer_len > (nif * sizeof(IP_ADAPTER_INFO)) )
			nif++;
        return nif;
    }
    fprintf( stderr, "FindNumberOfLocalNetworkInterfaces() failed\n" );
    return -1;
}