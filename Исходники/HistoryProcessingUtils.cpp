/**
 * Process orphaned index files, those that exist but do not have a
 * corresponding history file.
 *
 * Process all .idx files looking for the corresponding HistoryFile in
 * the history file map.
 */
void
aviary::history::processOrphanedIndices()
{
    const char *file = NULL;

    Directory dir ( m_path.Value() );
    dir.Rewind();
    while ( ( file = dir.Next() ) )
    {
        // Skip all non-history index files, e.g. history and history.*
        if ( strncmp ( file, "history.", 8 ) ||
                strncmp ( file + ( strlen ( file ) - 4 ), HISTORY_INDEX_SUFFIX, 4 ) ) continue;

        // XXX: This is ugly because it indicates we know details
        // of how HistoryFile implements index files.

        // The index file is "history.%ld.idx" where %ld is the id
        // of the history file the index is for.

        long unsigned int id;
        int count = sscanf ( file, "history.%ld.idx", &id );
        if ( 1 != count )
        {
            dprintf ( D_ALWAYS, "Error parsing %s, skipping.\n", file );
            continue;
        }

        HistoryFileListType::iterator entry = m_historyFiles.find ( id );
        if ( m_historyFiles.end() == entry )
        {
            // The index is dangling, remove it.
            if ( !dir.Remove_Current_File() )
            {
               dprintf ( D_ALWAYS, "Failed to remove: %s\n", file );
            }
        }
    }
}