void RecentsMRL::addRecent( const QString &mrl )
{
    if ( !isActive || ( filter && filter->indexIn( mrl ) >= 0 ) )
        return;

#ifdef _WIN32
    /* Add to the Windows 7 default list in taskbar */
    char* path = make_path( qtu( mrl ) );
    if( path )
    {
        wchar_t *wmrl = ToWide( path );
        SHAddToRecentDocs( SHARD_PATHW, wmrl );
        free( wmrl );
        free( path );
    }
#endif

    int i_index = recents.indexOf( mrl );
    if( 0 <= i_index )
    {
        /* move to the front */
        recents.move( i_index, 0 );
        times.move( i_index, 0 );
    }
    else
    {
        recents.prepend( mrl );
        times.prepend( "-1" );
        if( recents.count() > RECENTS_LIST_SIZE ) {
            recents.takeLast();
            times.takeLast();
        }
    }
    VLCMenuBar::updateRecents( p_intf );
    save();
}