bool KSFLoader::LoadGlobalData( const CString &sPath, Song &out )
{
    MsdFile msd;
    if( !msd.ReadFile( sPath ) )
        RageException::Throw( "Error opening file \"%s\": %s", sPath.c_str(), msd.GetError().c_str() );

    float BPMPos2 = -1, BPM2 = -1, BPMPos3 = -1, BPM3 = -1;;

    for( unsigned i=0; i < msd.GetNumValues(); i++ )
    {
        const MsdFile::value_t &sParams = msd.GetValue(i);
        CString sValueName = sParams[0];

        // handle the data
        if( 0==stricmp(sValueName,"TITLE") )
            LoadTags(sParams[1], out);
        else if( 0==stricmp(sValueName,"BPM") )
            out.AddBPMSegment( BPMSegment(0, strtof(sParams[1], NULL)) );
        else if( 0==stricmp(sValueName,"BPM2") )
            BPM2 = strtof( sParams[1], NULL );
        else if( 0==stricmp(sValueName,"BPM3") )
            BPM3 = strtof( sParams[1], NULL );
        else if( 0==stricmp(sValueName,"BUNKI") )
            BPMPos2 = strtof( sParams[1], NULL ) / 100.0f;
        else if( 0==stricmp(sValueName,"BUNKI2") )
            BPMPos3 = strtof( sParams[1], NULL ) / 100.0f;
        else if( 0==stricmp(sValueName,"STARTTIME") )
            out.m_Timing.m_fBeat0OffsetInSeconds = -strtof( sParams[1], NULL )/100;
        else if( 0==stricmp(sValueName,"TICKCOUNT") ||
                 0==stricmp(sValueName,"STEP") ||
                 0==stricmp(sValueName,"DIFFICULTY"))
            ; /* Handled in LoadFromKSFFile; don't warn. */
        else
            LOG->Trace( "Unexpected value named '%s'", sValueName.c_str() );
    }

    /* This doesn't work yet: we also need to move the data around, I think, and
     * we should handle more than one BPM change. */
    if( BPM2 > 0 && BPMPos2 > 0 )
    {
        const float BeatsPerSecond = out.GetBPMAtBeat(0) / 60.0f;
        const float beat = BPMPos2 * BeatsPerSecond;
        LOG->Trace("BPM %f, BPS %f, BPMPos2 %f, beat %f",
                   out.GetBPMAtBeat(0), BeatsPerSecond, BPMPos2, beat);
        out.AddBPMSegment( BPMSegment(beat, BPM2) );
    }

    if( BPM3 > 0 && BPMPos3 > 0 )
    {
        const float BeatsPerSecond = out.GetBPMAtBeat(0) / 60.0f;
        const float beat = BPMPos3 * BeatsPerSecond;
        LOG->Trace("BPM %f, BPS %f, BPMPos3 %f, beat %f",
                   out.GetBPMAtBeat(0), BeatsPerSecond, BPMPos3, beat);
        out.AddBPMSegment( BPMSegment(beat, BPM3) );
    }

    /* Try to fill in missing bits of information from the pathname. */
    {
        CStringArray asBits;
        split( sPath, "/", asBits, true);

        ASSERT(asBits.size() > 1);
        LoadTags(asBits[asBits.size()-2], out);
    }

    // search for music with song in the file name
    CStringArray arrayPossibleMusic;
    GetDirListing( out.GetSongDir() + CString("song.mp3"), arrayPossibleMusic );
    GetDirListing( out.GetSongDir() + CString("song.ogg"), arrayPossibleMusic );
    GetDirListing( out.GetSongDir() + CString("song.wav"), arrayPossibleMusic );

    if( !arrayPossibleMusic.empty() )		// we found a match
        out.m_sMusicFile = arrayPossibleMusic[0];

    return true;
}