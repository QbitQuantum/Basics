void BGAnimation::LoadFromAniDir( CString sAniDir )
{
	Unload();

	if( sAniDir.empty() )
		 return;

	if( sAniDir.Right(1) != "/" )
		sAniDir += "/";

	ASSERT_M( IsADirectory(sAniDir), sAniDir + " isn't a directory" );

	CString sPathToIni = sAniDir + "BGAnimation.ini";

	if( DoesFileExist(sPathToIni) )
	{
		// This is a new style BGAnimation (using .ini)
		AddLayersFromAniDir( sAniDir, m_SubActors, m_bGeneric );	// TODO: Check for circular load

		IniFile ini;
		ini.ReadFile( sPathToIni );
		if( !ini.GetValue( "BGAnimation", "LengthSeconds", m_fLengthSeconds ) )
		{
			/* XXX: if m_bGeneric, simply constructing the BG layer won't run "On",
			 * so at this point GetMaxTweenTimeLeft is probably 0 */
			m_fLengthSeconds = this->GetTweenTimeLeft();
		}

		bool bUseScroller;
		if( ini.GetValue( "BGAnimation", "UseScroller", bUseScroller ) && bUseScroller )
		{
			// TODO: Move this into ActorScroller
			
#define REQUIRED_GET_VALUE( szName, valueOut ) \
	if( !ini.GetValue( "Scroller", szName, valueOut ) ) \
		Dialog::OK( ssprintf("File '%s' is missing the value Scroller::%s", sPathToIni.c_str(), szName) );

			float fSecondsPerItem = 1;
			int iNumItemsToDraw = 7;
			RageVector3	vRotationDegrees = RageVector3(0,0,0);
			RageVector3	vTranslateTerm0 = RageVector3(0,0,0);
			RageVector3	vTranslateTerm1 = RageVector3(0,0,0);
			RageVector3	vTranslateTerm2 = RageVector3(0,0,0);
			float fItemPaddingStart = 0;
			float fItemPaddingEnd = 0;

			REQUIRED_GET_VALUE( "SecondsPerItem", fSecondsPerItem );
			REQUIRED_GET_VALUE( "NumItemsToDraw", iNumItemsToDraw );
			REQUIRED_GET_VALUE( "RotationDegreesX", vRotationDegrees[0] );
			REQUIRED_GET_VALUE( "RotationDegreesY", vRotationDegrees[1] );
			REQUIRED_GET_VALUE( "RotationDegreesZ", vRotationDegrees[2] );
			REQUIRED_GET_VALUE( "TranslateTerm0X", vTranslateTerm0[0] );
			REQUIRED_GET_VALUE( "TranslateTerm0Y", vTranslateTerm0[1] );
			REQUIRED_GET_VALUE( "TranslateTerm0Z", vTranslateTerm0[2] );
			REQUIRED_GET_VALUE( "TranslateTerm1X", vTranslateTerm1[0] );
			REQUIRED_GET_VALUE( "TranslateTerm1Y", vTranslateTerm1[1] );
			REQUIRED_GET_VALUE( "TranslateTerm1Z", vTranslateTerm1[2] );
			REQUIRED_GET_VALUE( "TranslateTerm2X", vTranslateTerm2[0] );
			REQUIRED_GET_VALUE( "TranslateTerm2Y", vTranslateTerm2[1] );
			REQUIRED_GET_VALUE( "TranslateTerm2Z", vTranslateTerm2[2] );
			REQUIRED_GET_VALUE( "ItemPaddingStart", fItemPaddingStart );
			REQUIRED_GET_VALUE( "ItemPaddingEnd", fItemPaddingEnd );
#undef REQUIRED_GET_VALUE

			ActorScroller::Load( 
				fSecondsPerItem,
				iNumItemsToDraw,
				vRotationDegrees,
				vTranslateTerm0,
				vTranslateTerm1,
				vTranslateTerm2 );
			ActorScroller::SetCurrentAndDestinationItem( int(-fItemPaddingStart) );
			ActorScroller::SetDestinationItem( int(m_SubActors.size()-1+fItemPaddingEnd) );
		}

		CString InitCommand;
		if( ini.GetValue( "BGAnimation", "InitCommand", InitCommand ) )
		{
			/* There's an InitCommand.  Run it now.  This can be used to eg. change Z to
			 * modify draw order between BGAs in a Foreground.  Most things should be done
			 * in metrics.ini commands, not here. */
			this->Command( InitCommand );
		}
	}
	else
	{
		// This is an old style BGAnimation (not using .ini)

		// loading a directory of layers
		CStringArray asImagePaths;
		ASSERT( sAniDir != "" );

		GetDirListing( sAniDir+"*.png", asImagePaths, false, true );
		GetDirListing( sAniDir+"*.jpg", asImagePaths, false, true );
		GetDirListing( sAniDir+"*.gif", asImagePaths, false, true );
		GetDirListing( sAniDir+"*.avi", asImagePaths, false, true );
		GetDirListing( sAniDir+"*.mpg", asImagePaths, false, true );
		GetDirListing( sAniDir+"*.mpeg", asImagePaths, false, true );
		GetDirListing( sAniDir+"*.sprite", asImagePaths, false, true );

		SortCStringArray( asImagePaths );

		for( unsigned i=0; i<asImagePaths.size(); i++ )
		{
			const CString sPath = asImagePaths[i];
			if( Basename(sPath).Left(1) == "_" )
				continue;	// don't directly load files starting with an underscore
			BGAnimationLayer* pLayer = new BGAnimationLayer( m_bGeneric );
			pLayer->LoadFromAniLayerFile( asImagePaths[i] );
			AddChild( pLayer );
		}
	}
}