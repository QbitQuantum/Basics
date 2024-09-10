bool testHashDataLong(bool bVerbose){

	HCRYPTHASH hHash;
	BYTE bDataToHash[50];
	BYTE bHashValue[32];
	BYTE bBenchmarkHashValue[32];
	//strtobyte( "73657479622032333D6874676E656C202C6567617373656D2073692073696854", bDataToHash );
	memcpy( bDataToHash, "Suppose the original message has length = 50 bytes", 50 );
	strtobyte( "0852F5623B89DD57AEB4781FE54DF14EEAFBC1350613763A0D770AA657BA1A47", bBenchmarkHashValue );

	if (!(CryptCreateHash(hProv,
					  CALG_GOST_HASH,
					  0,
					  0,
					  &hHash)))
	{   
		if ( bVerbose )
			printf("CryptCreateHash Failed\n");
		return false;
	}

	DWORD dwHashLen = 32;
	if ( !CryptHashData( hHash, bDataToHash, 50, 0 ) ){
		if ( bVerbose )
			printf("CryptHashData Failed\n");
		return false;
	}

	if ( !CryptGetHashParam( hHash, HP_HASHVAL, bHashValue, &dwHashLen, 0 ) ){
		if ( bVerbose )
			printf("CryptGetHashParam Failed\n");
		return false;
	}

	if ( memcmp( bHashValue, bBenchmarkHashValue, dwHashLen ) != 0 ){
		if ( bVerbose )
			std::cout << bHashValue << std::endl;
		return false;
	}

	if ( !CryptDestroyHash( hHash ) ){
		if ( bVerbose )
			std::cout << "CryptDestroyHash failed" << std::endl;
		return false;
	}

	return true;

}