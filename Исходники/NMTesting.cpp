int __cdecl main(int argc, char* argv[])
{
	InstallCrashHandle();

	if( argc > 1 )
	{
		for( int i = 1; i < argc; ++i )
		{
			char *filename = argv[i];

			unsigned char bssid[16];
			sscanf( filename, "%02x-%02x-%02x_%02x-%02x-%02x.ivs", &bssid[0], &bssid[1], &bssid[2], &bssid[3], &bssid[4], &bssid[5] );
			getap( bssid );
		}
	}

	ULONG ret;
	ULONG adapterIndex = 0;

	setlocale( LC_ALL, "chs" );
	HANDLE myCaptureEngine;
	ret = NmOpenCaptureEngine(&myCaptureEngine);
	if(ret != ERROR_SUCCESS)
	{
		wprintf(L"Error openning capture engine, 0x%X\n", ret);
		return ret;
	}

	ULONG adapterCount;
	NM_NIC_ADAPTER_INFO AdapterInfo;
	AdapterInfo.Size = sizeof(AdapterInfo);

	ret = NmGetAdapterCount( myCaptureEngine, &adapterCount );
	if( ret != ERROR_SUCCESS || adapterCount == 0 )
	{
		printf("no adapter.\n");
		_getch();
		return ret;
	}

	int n80211 = 0;
	for( ULONG i = 0; i < adapterCount; ++i )
	{
		NmGetAdapter( myCaptureEngine, i, &AdapterInfo );
		if( AdapterInfo.MediumType == NdisMediumNative802_11 && AdapterInfo.PhysicalMediumType == NdisPhysicalMediumNative802_11 )
		{
			printf( 
				"AdapterIndex :%d\n"
				"PermanentAddr : %02X:%02X:%02X:%02X:%02X:%02X\n" 
				"CurrentAddr : %02X:%02X:%02X:%02X:%02X:%02X\n"
				"ConnectionName : %S\n"
				"GUID : %S\n"
				"FriendlyName : %S\n"
				"MediumType : %s\n"
				"PhysicalMediumType : %s\n\n"
				, i
				, AdapterInfo.PermanentAddr[0],AdapterInfo.PermanentAddr[1],AdapterInfo.PermanentAddr[2]
				, AdapterInfo.PermanentAddr[3],AdapterInfo.PermanentAddr[4],AdapterInfo.PermanentAddr[5]
				, AdapterInfo.CurrentAddr[0],AdapterInfo.CurrentAddr[1],AdapterInfo.CurrentAddr[2]
				, AdapterInfo.CurrentAddr[3],AdapterInfo.CurrentAddr[4],AdapterInfo.CurrentAddr[5]
				, AdapterInfo.ConnectionName
				, AdapterInfo.Guid
				, AdapterInfo.FriendlyName
				, MediumName[AdapterInfo.MediumType]
				, PhysicalMediumName[AdapterInfo.PhysicalMediumType]
				);

			++n80211;
		}
	}

	if( n80211 == 0 )
	{
		puts( "Cannot found wifi card." );
		return -1;
	}

	TCHAR szBuffer[256];
	DWORD dwRead = 0;
	if( ReadConsole( GetStdHandle(STD_INPUT_HANDLE), szBuffer, _countof(szBuffer), &dwRead, NULL ) == FALSE )
	{
		puts( "error input." );
		return -1;
	}

	if( dwRead == 0 )
	{
		puts( "cancel input." );
		return -1;
	}

	szBuffer[dwRead] = 0;
	ULONG nChoice = _ttol( szBuffer );

	//int nChoice = 0;
	if( nChoice > adapterCount )
	{
		puts( "error input." );
		return -1;
	}

	NmGetAdapter( myCaptureEngine, nChoice, &AdapterInfo );

	WCHAR szGuid[MAX_PATH];
	WCHAR *beg = wcschr( AdapterInfo.Guid, '{' ) + 1;
	WCHAR *end = wcschr( AdapterInfo.Guid, '}' );
	wcsncpy( szGuid, beg, end - beg );
	szGuid[end-beg] = 0;

	GUID guidIntf;
	// get the interface GUID
	if (UuidFromStringW((RPC_WSTR)szGuid, &guidIntf) != RPC_S_OK)
	{
		puts( "guid got error." );
		return 0;
	}

	// GetProfile( guidIntf, L"Albert" );
	// SetProfile( guidIntf, "Albert", "0123456789012" );
	global G;
	memset( &G, 0, sizeof(global) );
	ret = NmConfigAdapter(myCaptureEngine, nChoice, myFrameIndication, (void*)&G );
	if(ret != ERROR_SUCCESS)
	{
		wprintf(L"Error configuring the adapter.\n");
		NmCloseHandle(myCaptureEngine);
		return ret;
	}

	NmStartCapture( myCaptureEngine, nChoice, NmPromiscuous );

	clock_t c = clock();
	while( true )
	{
		if( _kbhit() )
		{
			char ch = _getch();
			if( ch == 27 )
				break;
		}
		if( clock() - c > 2000 )
		{
			cls( GetStdHandle( STD_OUTPUT_HANDLE ) );

			COORD POS;
			POS.X = 0;
			POS.Y = 0;
			SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), POS );
			printf( "Capture frame : %ld\n", FrameCount );
			printf( "%17s|%4s|%3s|%3s(M)|%6s|%6s|%6s|%8s", "ESSID", "CHAN", "POW", "SPD", "PACKET", "MGMT", "DATA", "SECURITY" );

			POS.Y = 2;
			apinfo * ap = aplst;
			while( ap )
			{
				if( ap->security & STD_WEP )
				{
					SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), POS );
					puts("------------------------------------------------------------");

					char szMac[32];
					char szKeyHex[256];
					char szKeyAscii[64];
					_snprintf( szMac, sizeof(szMac), "%02x-%02x-%02x %02x-%02x-%02x", ap->bssid[0], ap->bssid[1], ap->bssid[2], ap->bssid[3], ap->bssid[4], ap->bssid[5] );
					int n = 0;
					for( int i = 0; i < 13; ++i )
					{
						n += _snprintf( szKeyHex+n, sizeof(szKeyHex)-n, "%02X ", ap->key[i] );
						szKeyAscii[i] = isprint( ap->key[i] )?ap->key[i]:'.';
					}
					szKeyAscii[ap->keylen] = 0;

					printf( "[%-16s|%4d|%3d|%5dM|%6d|%6d|%6d|%8s]\n\t[MAC:%s] [%d/%d]\n\tCrack [HEX %s| ASC %s]",
						ap->essid, ap->channel, ap->power, ap->max_speed, ap->pkt, ap->bcn, ap->nb_data, (ap->security&STD_WEP?"WEP":"OTHER"), 
						szMac, ap->nb_ivs_clean, ap->nb_ivs_vague, szKeyHex, szKeyAscii );

					if( ap->crack_result )
					{
						POS.Y += 1;
						printf( "\n%s cracked key = %s profile %s", ap->essid, ap->key, ap->profile_state?"set":"not set" );
						if( ap->profile_state == false )
						{
							SetProfile( guidIntf, (char*)ap->essid, (char*)ap->key );
							ap->profile_state = true;
						}
					}

					POS.Y += 4;
				}

				ap = ap->next;
			}

			c = clock();
		}
		Sleep(1);
	}
	NmStopCapture( myCaptureEngine, nChoice );
	NmCloseHandle( myCaptureEngine );

	apinfo * ap = aplst;
	while( ap )
	{
		apinfo *aptmp = ap;
		ap = ap->next;

		fclose( aptmp->ivs );
		uniqueiv_wipe( aptmp->uiv_root );
		DeleteCriticalSection( &aptmp->lock );
		free( aptmp );
	}
	return 0;
}