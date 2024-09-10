std::string getmac_one( int lana_num )
{ 
	NCB ncb; 
	UCHAR uRetCode; 

	memset( &ncb, 0, sizeof( ncb ) ); 
	ncb.ncb_command = NCBRESET; 
	ncb.ncb_lana_num = lana_num; 

	uRetCode = Netbios( &ncb ); 
	//printf( "The NCBRESET return code is:0x%x \n", uRetCode ); 

	memset( &ncb, 0, sizeof( ncb ) ); 
	ncb.ncb_command = NCBASTAT; 
	ncb.ncb_lana_num = lana_num; 

	strcpy( (char *)ncb.ncb_callname, "* " ); 
	ncb.ncb_buffer = ( unsigned char * ) &Adapter; 

	ncb.ncb_length = sizeof( Adapter ); 
	uRetCode = Netbios( &ncb ); 
	// printf( "The NCBASTAT return code is: 0x%x \n", uRetCode );
	std::string s;
	if ( uRetCode == 0 ) 
	{
		int bAddressInt [ MACSESION ];
		char CommarSeperatedAddress[ MACSESION * 3 ]={0};
		for( int i = 0; i < MACSESION; ++i )
		{
			bAddressInt[ i ] = Adapter.adapt.adapter_address[ i ];
			bAddressInt[ i ] &= 0x000000ff; // avoid "ff" leading bytes when "char" is lager then 0x7f
		}
		sprintf( CommarSeperatedAddress, "%02x:%02x:%02x:%02x:%02x:%02x",
			bAddressInt[ 0 ],
			bAddressInt[ 1 ],
			bAddressInt[ 2 ],
			bAddressInt[ 3 ],
			bAddressInt[ 4 ],
			bAddressInt[ 5 ]); // Should use scl::FormatString inside 
		s = CommarSeperatedAddress;
	}
	return s;
}