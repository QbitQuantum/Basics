void NotifyPlayerOfMercDepartureAndPromptEquipmentPlacement( SOLDIERTYPE *pSoldier, BOOLEAN fAddRehireButton )
{
	// will tell player this character is leaving and ask where they want the equipment left
	CHAR16 sString[ 1024 ];
	BOOLEAN fInSector = FALSE;
//	INT16					zTownIDString[50];
	CHAR16				zShortTownIDString[ 50 ];

	// use YES/NO Pop up box, settup for particular screen
	SGPRect pCenteringRect= {0, 0, 640, 480};

	//GetSectorIDString( pSoldier->sSectorX, pSoldier->sSectorY, pSoldier->bSectorZ, zTownIDString, TRUE );

	GetShortSectorString( pSoldier->sSectorX ,pSoldier->sSectorY, zShortTownIDString );

	// Set string for generic button
	swprintf( gzUserDefinedButton1, L"%s", zShortTownIDString );


	pLeaveSoldier = pSoldier;

	if( pSoldier->fSignedAnotherContract == TRUE )
	{
		fAddRehireButton = FALSE;
	}

	if( pSoldier->fSignedAnotherContract == TRUE )
	{
		fAddRehireButton = FALSE;
	}

	if( pSoldier->ubWhatKindOfMercAmI != MERC_TYPE__AIM_MERC )
	{
		fAddRehireButton = FALSE;
	}

	//if the character is an RPC
	if( pSoldier->ubProfile >= FIRST_RPC && pSoldier->ubProfile < FIRST_NPC )
	{
		if( gMercProfiles[ pSoldier->ubProfile ].bSex == MALE )
		{
			swprintf( sString, pMercHeLeaveString[ 4 ], pSoldier->name, zShortTownIDString );
		}
		else
		{
			swprintf( sString, pMercSheLeaveString[ 4 ], pSoldier->name, zShortTownIDString );
		}
		fInSector = TRUE;
	}

	// check if drassen controlled
	else if( StrategicMap[  ( AIRPORT_X + ( MAP_WORLD_X * AIRPORT_Y ) ) ].fEnemyControlled == FALSE )
	{
		
		if( ( pSoldier->sSectorX == AIRPORT_X ) && ( pSoldier->sSectorY == AIRPORT_Y ) && ( pSoldier->bSectorZ == 0 ) )
		{
			if( gMercProfiles[ pSoldier->ubProfile ].bSex == MALE )
			{
				swprintf( sString, L"%s %s", pSoldier->name, pMercHeLeaveString[ 3 ] );
			}
			else
			{
				swprintf( sString, L"%s %s", pSoldier->name, pMercSheLeaveString[ 3 ] );
			}
			fInSector = TRUE;
		}
		else
		{
			// Set string for generic button
			swprintf( gzUserDefinedButton2, L"B13" );

			if( gMercProfiles[ pSoldier->ubProfile ].bSex == MALE )
			{
				swprintf( sString, pMercHeLeaveString[ 0 ], pSoldier->name, zShortTownIDString );
			}
			else
			{
				swprintf( sString, pMercSheLeaveString[ 0 ], pSoldier->name, zShortTownIDString );
			}
			
		}
	}
	else
	{
		if( ( pSoldier->sSectorX == OMERTA_LEAVE_EQUIP_SECTOR_X ) && ( pSoldier->sSectorY == OMERTA_LEAVE_EQUIP_SECTOR_Y ) && ( pSoldier->bSectorZ == 0 ) )
		{
			if( gMercProfiles[ pSoldier->ubProfile ].bSex == MALE )
			{
				swprintf( sString, L"%s %s", pSoldier->name, pMercHeLeaveString[ 2 ] );
			}
			else
			{
				swprintf( sString, L"%s %s", pSoldier->name, pMercSheLeaveString[ 2 ] );
			}
			fInSector = TRUE;
		}
		else
		{
			// Set string for generic button
			swprintf( gzUserDefinedButton2, L"A9" );

			if( gMercProfiles[ pSoldier->ubProfile ].bSex == MALE )
			{
				swprintf( sString, pMercHeLeaveString[ 1 ], pSoldier->name, zShortTownIDString );
			}
			else
			{
				swprintf( sString, pMercSheLeaveString[ 1 ], pSoldier->name, zShortTownIDString );
			}
		}
	}

	/// which screen are we in?
	if ( (guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
	{
		if( fInSector == FALSE )
		{			
			// set up for mapscreen
			DoMapMessageBox( MSG_BOX_BASIC_STYLE, sString, MAP_SCREEN, ( UINT16 )( ( fAddRehireButton ? MSG_BOX_FLAG_GENERICCONTRACT : MSG_BOX_FLAG_GENERIC ) ), MercDepartEquipmentBoxCallBack );
		}
		else
		{
			DoMapMessageBox( MSG_BOX_BASIC_STYLE, sString, MAP_SCREEN, ( UINT16 )( ( fAddRehireButton ? MSG_BOX_FLAG_OKCONTRACT : MSG_BOX_FLAG_OK  ) ), MercDepartEquipmentBoxCallBack );
		}

	}
	else
	{
		if( fInSector == FALSE )
		{
			// set up for all otherscreens
			DoMessageBox(  MSG_BOX_BASIC_STYLE, sString,  guiCurrentScreen, ( UINT16 ) ( MSG_BOX_FLAG_USE_CENTERING_RECT | ( fAddRehireButton ? MSG_BOX_FLAG_GENERICCONTRACT : MSG_BOX_FLAG_GENERIC ) ),  MercDepartEquipmentBoxCallBack,  &pCenteringRect );
		}
		else
		{
			DoMessageBox(  MSG_BOX_BASIC_STYLE, sString,  guiCurrentScreen, ( UINT16 ) ( MSG_BOX_FLAG_USE_CENTERING_RECT | ( fAddRehireButton ? MSG_BOX_FLAG_OKCONTRACT : MSG_BOX_FLAG_OK  ) ) ,  MercDepartEquipmentBoxCallBack,  &pCenteringRect );
		}
	}
	
	if( pSoldier->fSignedAnotherContract == TRUE )
	{
		//fCurrentMercFired = FALSE;
	}

}