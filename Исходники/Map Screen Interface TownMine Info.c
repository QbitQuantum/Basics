// adds text to town info box
void AddTextToTownBox( void )
{
	UINT32 hStringHandle = 0;
	CHAR16 wString[ 64 ];
	UINT8 ubTownId = 0;
	UINT16 usTownSectorIndex;
	INT16 sMineSector = 0;


	// remember town id
	ubTownId = GetTownIdForSector( bCurrentTownMineSectorX, bCurrentTownMineSectorY );
	Assert((ubTownId >= FIRST_TOWN) && (ubTownId < NUM_TOWNS));

	usTownSectorIndex = SECTOR( bCurrentTownMineSectorX, bCurrentTownMineSectorY );

	switch( usTownSectorIndex )
	{
		case SEC_B13:
			AddMonoString( &hStringHandle, pLandTypeStrings[ DRASSEN_AIRPORT_SITE ] );
			break;
		case SEC_F8:
			AddMonoString( &hStringHandle, pLandTypeStrings[ CAMBRIA_HOSPITAL_SITE ] );
			break;
		case SEC_J9: //Tixa
			if( !fFoundTixa )
				AddMonoString( &hStringHandle, pLandTypeStrings[ SAND ] );
			else
				AddMonoString( &hStringHandle, pTownNames[ TIXA ] );
			break;
		case SEC_K4: //Orta
			if( !fFoundOrta )
				AddMonoString( &hStringHandle, pLandTypeStrings[ SWAMP ] );
			else
				AddMonoString( &hStringHandle, pTownNames[ ORTA ] );
			break;
		case SEC_N3:
			AddMonoString( &hStringHandle, pLandTypeStrings[ MEDUNA_AIRPORT_SITE ] );
			break;
		default:
			if( usTownSectorIndex == SEC_N4 && fSamSiteFound[ SAM_SITE_FOUR ] )
			{	//Meduna's SAM site
				AddMonoString( &hStringHandle, pLandTypeStrings[ MEDUNA_SAM_SITE ] );
			}
			else
			{ // town name
				swprintf( wString, L"%s", pTownNames[ ubTownId ] );
				AddMonoString( &hStringHandle, wString );
			}
			break;
	}
	// blank line
	AddMonoString( &hStringHandle, L"" );

	// sector
	AddSectorToBox();

	// town size
	swprintf( wString, L"%s:", pwTownInfoStrings[ 0 ] );
	AddMonoString( &hStringHandle, wString );
	swprintf( wString, L"%d",  GetTownSectorSize( ubTownId ) );
	AddSecondColumnMonoString( &hStringHandle, wString );

	// main facilities
	swprintf( wString, L"%s:", pwTownInfoStrings[ 8 ] );
	AddMonoString( &hStringHandle, wString );
	wcscpy(wString, L"");
	GetSectorFacilitiesFlags( bCurrentTownMineSectorX, bCurrentTownMineSectorY, wString );
	AddSecondColumnMonoString( &hStringHandle, wString );

	// the concept of control is only meaningful in sectors where militia can be trained
	if ( MilitiaTrainingAllowedInSector( bCurrentTownMineSectorX, bCurrentTownMineSectorY, 0 ) )
	{
		// town control
		swprintf( wString, L"%s:", pwTownInfoStrings[ 2 ] );
		AddMonoString( &hStringHandle, wString );
		swprintf( wString, L"%d%%%%",  (GetTownSectorsUnderControl( ubTownId ) * 100) / GetTownSectorSize( ubTownId ));
		AddSecondColumnMonoString( &hStringHandle, wString );
	}

	// the concept of town loyalty is only meaningful in towns where loyalty is tracked
	if( gTownLoyalty[ ubTownId ].fStarted && gfTownUsesLoyalty[ ubTownId ])
	{
		// town loyalty
		swprintf( wString, L"%s:", pwTownInfoStrings[ 5 ] );
		AddMonoString( &hStringHandle, wString );
		swprintf( wString, L"%d%%%%", gTownLoyalty[ ubTownId ].ubRating );
		AddSecondColumnMonoString( &hStringHandle, wString );
	}

	// if the town has a mine
	sMineSector = GetMineSectorForTown( ubTownId );
	if( sMineSector != -1 )
	{
		// Associated Mine: Sector
	  swprintf( wString, L"%s:",  pwTownInfoStrings[ 4 ] );
		AddMonoString( &hStringHandle, wString );
	  GetShortSectorString( ( INT16 )( sMineSector % MAP_WORLD_X ), ( INT16 )( sMineSector / MAP_WORLD_X ), wString );
		AddSecondColumnMonoString( &hStringHandle, wString );
	}
}