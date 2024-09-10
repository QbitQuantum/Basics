/* Copy our parent's data.  This is done when we're being changed from autogen
 * to normal. (needed?) */
void Steps::DeAutogen( bool bCopyNoteData )
{
    if( !parent )
        return; /* OK */

    if( bCopyNoteData )
        Decompress();	// fills in m_pNoteData with sliding window transform

    m_sDescription		= Real()->m_sDescription;
    m_Difficulty		= Real()->m_Difficulty;
    m_iMeter		= Real()->m_iMeter;
    copy( Real()->m_CachedRadarValues, Real()->m_CachedRadarValues + NUM_PLAYERS, m_CachedRadarValues );

    parent = NULL;

    if( bCopyNoteData )
        Compress();
}