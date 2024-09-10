bool SMLoader::LoadFromSMFile( CString sPath, Song &out )
{
	LOG->Trace( "Song::LoadFromSMFile(%s)", sPath.c_str() );

	MsdFile msd;
	if( !msd.ReadFile( sPath ) )
		RageException::Throw( "Error opening file \"%s\": %s", sPath.c_str(), msd.GetError().c_str() );

	out.m_Timing.m_sFile = sPath;
	LoadTimingFromSMFile( msd, out.m_Timing );

	for( unsigned i=0; i<msd.GetNumValues(); i++ )
	{
		int iNumParams = msd.GetNumParams(i);
		const MsdFile::value_t &sParams = msd.GetValue(i);
		const CString sValueName = sParams[0];

		// handle the data
		/* Don't use GetMainAndSubTitlesFromFullTitle; that's only for heuristically
		 * splitting other formats that *don't* natively support #SUBTITLE. */
		if( 0==stricmp(sValueName,"TITLE") )
			out.m_sMainTitle = sParams[1];

		else if( 0==stricmp(sValueName,"SUBTITLE") )
			out.m_sSubTitle = sParams[1];

		else if( 0==stricmp(sValueName,"ARTIST") )
			out.m_sArtist = sParams[1];

		else if( 0==stricmp(sValueName,"TITLETRANSLIT") )
			out.m_sMainTitleTranslit = sParams[1];

		else if( 0==stricmp(sValueName,"SUBTITLETRANSLIT") )
			out.m_sSubTitleTranslit = sParams[1];

		else if( 0==stricmp(sValueName,"ARTISTTRANSLIT") )
			out.m_sArtistTranslit = sParams[1];

		else if( 0==stricmp(sValueName,"CREDIT") )
			out.m_sCredit = sParams[1];

		else if( 0==stricmp(sValueName,"BANNER") )
			out.m_sBannerFile = sParams[1];

		else if( 0==stricmp(sValueName,"BACKGROUND") )
			out.m_sBackgroundFile = sParams[1];

		/* Save "#LYRICS" for later, so we can add an internal lyrics tag. */
		else if( 0==stricmp(sValueName,"LYRICSPATH") )
			out.m_sLyricsFile = sParams[1];

		else if( 0==stricmp(sValueName,"CDTITLE") )
			out.m_sCDTitleFile = sParams[1];

		else if( 0==stricmp(sValueName,"MUSIC") )
			out.m_sMusicFile = sParams[1];

		else if( 0==stricmp(sValueName,"MUSICLENGTH") )
		{
			if(!FromCache)
				continue;
			out.m_fMusicLengthSeconds = strtof( sParams[1], NULL );
		}

		else if( 0==stricmp(sValueName,"MUSICBYTES") )
			; /* ignore */

		/* We calculate these.  Some SMs in circulation have bogus values for
		 * these, so make sure we always calculate it ourself. */
		else if( 0==stricmp(sValueName,"FIRSTBEAT") )
		{
			if(!FromCache)
				continue;
			out.m_fFirstBeat = strtof( sParams[1], NULL );
		}

		else if( 0==stricmp(sValueName,"LASTBEAT") )
		{
			if(!FromCache)
				LOG->Trace("Ignored #LASTBEAT (cache only)");
			out.m_fLastBeat = strtof( sParams[1], NULL );
		}
		else if( 0==stricmp(sValueName,"SONGFILENAME") )
		{
			if( FromCache )
				out.m_sSongFileName = sParams[1];
		}
		else if( 0==stricmp(sValueName,"HASMUSIC") )
		{
			if( FromCache )
				out.m_bHasMusic = atoi( sParams[1] ) != 0;
		}
		else if( 0==stricmp(sValueName,"HASBANNER") )
		{
			if( FromCache )
				out.m_bHasBanner = atoi( sParams[1] ) != 0;
		}

		else if( 0==stricmp(sValueName,"SAMPLESTART") )
			out.m_fMusicSampleStartSeconds = HHMMSSToSeconds( sParams[1] );

		else if( 0==stricmp(sValueName,"SAMPLELENGTH") )
			out.m_fMusicSampleLengthSeconds = HHMMSSToSeconds( sParams[1] );

		else if( 0==stricmp(sValueName,"DISPLAYBPM") )
		{
			// #DISPLAYBPM:[xxx][xxx:xxx]|[*]; 
			if( sParams[1] == "*" )
				out.m_DisplayBPMType = Song::DISPLAY_RANDOM;
			else 
			{
				out.m_DisplayBPMType = Song::DISPLAY_SPECIFIED;
				out.m_fSpecifiedBPMMin = strtof( sParams[1], NULL );
				if( sParams[2].empty() )
					out.m_fSpecifiedBPMMax = out.m_fSpecifiedBPMMin;
				else
					out.m_fSpecifiedBPMMax = strtof( sParams[2], NULL );
			}
		}

		else if( 0==stricmp(sValueName,"SELECTABLE") )
		{
			if(!stricmp(sParams[1],"YES"))
				out.m_SelectionDisplay = out.SHOW_ALWAYS;
			else if(!stricmp(sParams[1],"NO"))
				out.m_SelectionDisplay = out.SHOW_NEVER;
			else if(!stricmp(sParams[1],"ROULETTE"))
				out.m_SelectionDisplay = out.SHOW_ROULETTE;
			else
				LOG->Warn( "The song file '%s' has an unknown #SELECTABLE value, '%s'; ignored.", sPath.c_str(), sParams[1].c_str());
		}

		else if( 0==stricmp(sValueName,"BGCHANGES") || 0==stricmp(sValueName,"ANIMATIONS") )
		{
			CStringArray aBGChangeExpressions;
			split( sParams[1], ",", aBGChangeExpressions );

			for( unsigned b=0; b<aBGChangeExpressions.size(); b++ )
			{
				BackgroundChange change;
				if( LoadFromBGChangesString( change, aBGChangeExpressions[b] ) )
					out.AddBackgroundChange( change );
			}
		}

		else if( 0==stricmp(sValueName,"FGCHANGES") )
		{
			CStringArray aFGChangeExpressions;
			split( sParams[1], ",", aFGChangeExpressions );

			for( unsigned b=0; b<aFGChangeExpressions.size(); b++ )
			{
				BackgroundChange change;
				if( LoadFromBGChangesString( change, aFGChangeExpressions[b] ) )
					out.AddForegroundChange( change );
			}
		}

		else if( 0==stricmp(sValueName,"NOTES") )
		{
			if( iNumParams < 7 )
			{
				LOG->Trace( "The song file '%s' is has %d fields in a #NOTES tag, but should have at least %d.", sPath.c_str(), iNumParams, 7 );
				continue;
			}

			Steps* pNewNotes = new Steps;
			ASSERT( pNewNotes );

			LoadFromSMTokens( 
				sParams[1], sParams[2], sParams[3], sParams[4], sParams[5], sParams[6], (iNumParams>=8)?sParams[7]:CString(""),
				*pNewNotes);

			out.AddSteps( pNewNotes );
		}
		else if( 0==stricmp(sValueName,"OFFSET") || 0==stricmp(sValueName,"BPMS") ||
				 0==stricmp(sValueName,"STOPS") || 0==stricmp(sValueName,"FREEZES") )
				 ;
		else
			LOG->Trace( "Unexpected value named '%s'", sValueName.c_str() );
	}

	return true;
}