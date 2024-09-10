// Create an Archive from the specified File List.
VFS_BOOL VFS_Archive_CreateFromFileList( const VFS_String& strArchiveFileName, const VFS_FileNameMap& Files, const VFS_FilterNameList& UsedFilters )
{
    static VFS_BYTE Chunk[ FILE_COPY_CHUNK_SIZE ];

    // If there's already an Archive with the same File Name and it's open...
    VFS_EntityInfo Info;
    if( VFS_Archive_GetInfo( ToLower( strArchiveFileName ), Info ) )
    {
        // Check if the Archive is open.
        if( GetOpenArchives().find( ToLower( Info.strPath ) ) != GetOpenArchives().end() )
        {
            // Check if the Reference Count is != 0.
            if( GetOpenArchives()[ ToLower( Info.strPath ) ]->GetRefCount() > 0 )
            {
                // We don't want to manipulate an open Archive, do we?
                SetLastError( VFS_ERROR_IN_USE );
                return VFS_FALSE;
            }
            else
            {
                // Free the Archive.
                delete GetOpenArchives()[ ToLower( Info.strPath ) ];
                GetOpenArchives().erase( ToLower( Info.strPath ) );
            }
        }
    }
    else
    {
        Info.strPath = ToLower( strArchiveFileName );
        SetLastError( VFS_ERROR_NONE );
    }

    // Check the Filter Names and make a List of all Filter Pointers.
    VFS_FilterList Filters;
    for( VFS_FilterNameList::const_iterator iter = UsedFilters.begin(); iter != UsedFilters.end(); iter++ )
    {
        // Bad Filter Name?
        if( !VFS_ExistsFilter( *iter ) )
        {
            SetLastError( VFS_ERROR_INVALID_PARAMETER );
            return VFS_FALSE;
        }

        // Add the Filter.
        Filters.push_back( VFS_GetFilter( *iter ) );
    }

    // Check all Files.
    for( VFS_FileNameMap::const_iterator iter2 = Files.begin(); iter2 != Files.end(); iter2++ )
    {
        if( !VFS_File_Exists( ( *iter2 ).first ) )
        {
            SetLastError( VFS_ERROR_NOT_FOUND );
            return VFS_FALSE;
        }

        VFS_String strName;
        VFS_Util_GetName( ( *iter2 ).second, strName );
        if( strName.size() > VFS_MAX_NAME_LENGTH )
        {
            SetLastError( VFS_ERROR_INVALID_PARAMETER );
            return VFS_FALSE;
        }
    }

    // Make a list of the Directories to create.
    typedef vector< VFS_String > NameMap;
    NameMap Dirs;
    for( VFS_FileNameMap::const_iterator iter3 = Files.begin(); iter3 != Files.end(); iter3++ )
    {
        VFS_String strDir;
        VFS_Util_GetPath( ( *iter3 ).second, strDir );
        strDir = ToLower( strDir );
        if( strDir != VFS_TEXT( "" ) && find( Dirs.begin(), Dirs.end(), strDir ) == Dirs.end() )
        {
            // Add the top-level Dirs.
            while( strDir.rfind( VFS_PATH_SEPARATOR ) != VFS_String::npos )
            {
                if( find( Dirs.begin(), Dirs.end(), strDir ) != Dirs.end() )
                    break;
                Dirs.push_back( ToLower( strDir ) );
                if( strDir.size() > VFS_MAX_NAME_LENGTH )
                {
                    SetLastError( VFS_ERROR_INVALID_PARAMETER );
                    return VFS_FALSE;
                }

                strDir = strDir.substr( 0, strDir.rfind( VFS_PATH_SEPARATOR ) );
            }

            if( find( Dirs.begin(), Dirs.end(), strDir ) == Dirs.end() )
            {
                Dirs.push_back( ToLower( strDir ) );
                if( strDir.size() > VFS_MAX_NAME_LENGTH )
                {
                    SetLastError( VFS_ERROR_INVALID_PARAMETER );
                    return VFS_FALSE;
                }
            }
        }
    }

    // (Re)create the Target File.
    VFS_Handle hFile = VFS_File_Create( Info.strPath + VFS_TEXT( "." ) + VFS_ARCHIVE_FILE_EXTENSION, VFS_READ | VFS_WRITE );
    if( hFile == VFS_INVALID_HANDLE_VALUE )
        return VFS_FALSE;

    // Write the Header.
    ARCHIVE_HEADER Header;
    memcpy( Header.ID, ARCHIVE_ID, sizeof( ARCHIVE_ID ) );
    Header.wVersion = VFS_VERSION;
    Header.dwNumFilters = ( VFS_DWORD )Filters.size();
    Header.dwNumDirs = ( VFS_DWORD )Dirs.size();
    Header.dwNumFiles = ( VFS_DWORD )Files.size();
    VFS_DWORD dwWritten;
    if( !VFS_File_Write( hFile, ( const VFS_BYTE* ) &Header, sizeof( ARCHIVE_HEADER ), &dwWritten ) )
    {
        VFS_File_Close( hFile );
        return VFS_FALSE;
    }

    // Write the Filters.
    for( VFS_FilterList::iterator iter4 = Filters.begin(); iter4 != Filters.end(); iter4++ )
    {
        ARCHIVE_FILTER Filter;
        strcpy( Filter.szName, ToLower( ( *iter4 )->GetName() ).c_str() );
        if( !VFS_File_Write( hFile, ( const VFS_BYTE* ) &Filter, sizeof( ARCHIVE_FILTER ) ) )
        {
            VFS_File_Close( hFile );
            return VFS_FALSE;
        }
    }

    // Write the Directories.
    for( NameMap::iterator iter5 = Dirs.begin(); iter5 != Dirs.end(); iter5++ )
    {
        ARCHIVE_DIR Dir;

        // Get the Name of the Dir and add it.
        VFS_String strName;
        VFS_Util_GetName( *iter5, strName );
        strcpy( Dir.szName, ToLower( strName ).c_str() );

        // Remove the <pathsep> and the Name from the path; the rest should be the Parent Directory.
        if( ( *iter5 ).find( VFS_PATH_SEPARATOR ) != VFS_String::npos )
        {
            // Get the Name of the Parent Directory.
            VFS_String strParentDir = ( *iter5 ).substr( 0, ( *iter5 ).rfind( VFS_PATH_SEPARATOR ) );

            // Get the Index of the Parent Directory.
            assert( find( Dirs.begin(), Dirs.end(), ToLower( strParentDir ) ) != Dirs.end() );
            Dir.dwParentIndex = ( VFS_DWORD )( find( Dirs.begin(), Dirs.end(), ToLower( strParentDir ) ) - Dirs.begin() );
        }
        else
            Dir.dwParentIndex = DIR_INDEX_ROOT;

        if( !VFS_File_Write( hFile, ( const VFS_BYTE* ) &Dir, sizeof( ARCHIVE_DIR ) ) )
        {
            VFS_File_Close( hFile );
            return VFS_FALSE;
        }
    }

    // Get the starting offset for the file data.
    VFS_DWORD dwOffset = sizeof( ARCHIVE_HEADER ) + Header.dwNumFilters * sizeof( ARCHIVE_FILTER ) +
                         Header.dwNumDirs * sizeof( ARCHIVE_DIR ) + Header.dwNumFiles * sizeof( ARCHIVE_FILE );

    // Let the Filters store the configuration Data.
    for( VFS_FilterList::iterator iter6 = Filters.begin(); iter6 != Filters.end(); iter6++ )
    {
        // Setup diverse global Variables.
        g_ToBuffer.clear();

        // Call the Saver Proc.
        if( !( *iter6 )->SaveConfigData( Writer ) )
        {
            VFS_File_Close( hFile );
            return VFS_FALSE;
        }

        // Save it.
        VFS_DWORD dwPos = VFS_File_Tell( hFile );
        VFS_File_Seek( hFile, dwOffset, VFS_SET );
        VFS_File_Write( hFile, &*g_ToBuffer.begin(), ( VFS_DWORD )g_ToBuffer.size() );
        VFS_File_Seek( hFile, dwPos, VFS_SET );
        dwOffset += ( VFS_DWORD )g_ToBuffer.size();
    }

    // Write the Files.
    for( VFS_FileNameMap::const_iterator iter7 = Files.begin(); iter7 != Files.end(); iter7++ )
    {
        // Prepare the record.
        ARCHIVE_FILE File;

        // Get the Name of the File and add it.
        VFS_String strName;
        VFS_Util_GetName( ( *iter7 ).second, strName );
        strcpy( File.szName, ToLower( strName ).c_str() );

        // Get the Parent Dir ID.
        if( ( *iter7 ).second.find( VFS_PATH_SEPARATOR ) != VFS_String::npos )
        {
            // Get the Name of the Parent Directory.
            VFS_String strParentDir = ( *iter7 ).second.substr( 0, ( *iter7 ).second.rfind( VFS_PATH_SEPARATOR ) );

            // Get the Index of the Parent Directory.
            assert( find( Dirs.begin(), Dirs.end(), ToLower( strParentDir ) ) != Dirs.end() );
            File.dwDirIndex = ( VFS_DWORD )( find( Dirs.begin(), Dirs.end(), ToLower( strParentDir ) ) - Dirs.begin() );
        }
        else
            File.dwDirIndex = DIR_INDEX_ROOT;

        // Open the Source File.
        VFS_Handle hSrc = VFS_File_Open( ( *iter7 ).first, VFS_READ );
        if( hSrc == VFS_INVALID_HANDLE_VALUE )
        {
            VFS_File_Close( hFile );
            return VFS_FALSE;
        }

        // Store the uncompressed size.
        File.dwUncompressedSize = VFS_File_GetSize( hSrc );

        // Setup diverse global Variables.
        g_FromBuffer.clear();
        g_ToBuffer.clear();

        // Read in the File.
        VFS_DWORD dwRead;
        g_FromPos = 0;
        do
        {
            if( !VFS_File_Read( hSrc, Chunk, FILE_COPY_CHUNK_SIZE, &dwRead ) )
            {
                VFS_File_Close( hSrc );
                VFS_File_Close( hFile );
                return VFS_FALSE;
            }
            g_FromBuffer.reserve( g_FromBuffer.size() + dwRead );
            for( VFS_DWORD dwIndex = 0; dwIndex < dwRead; dwIndex++ )
                g_FromBuffer.push_back( Chunk[ dwIndex ] );
        }
        while( dwRead > 0 );

        // Close the File.
        VFS_File_Close( hSrc );

        // Call the Filters.
        VFS_EntityInfo Info;
        VFS_File_GetInfo( ( *iter7 ).first, Info );
        for( VFS_FilterList::iterator iter8 = Filters.begin(); iter8 != Filters.end(); iter8++ )
        {
            g_FromPos = 0;
            if( !( *iter8 )->Encode( Reader, Writer, Info ) )
            {
                VFS_ErrorCode eError = VFS_GetLastError();
                if( eError == VFS_ERROR_NONE )
                    eError = VFS_ERROR_GENERIC;
                SetLastError( eError );
                VFS_File_Close( hFile );
                return VFS_FALSE;
            }
            g_FromBuffer = g_ToBuffer;
            g_ToBuffer.clear();
        }

        // Store the final Result.
        VFS_DWORD dwPos = VFS_File_Tell( hFile );
        VFS_File_Seek( hFile, dwOffset, VFS_SET );
        VFS_File_Write( hFile, &*g_FromBuffer.begin(), ( VFS_DWORD )g_FromBuffer.size() );
        File.dwCompressedSize = ( VFS_DWORD )g_FromBuffer.size();
        VFS_File_Seek( hFile, dwPos, VFS_SET );
        dwOffset += File.dwCompressedSize;

        if( !VFS_File_Write( hFile, ( const VFS_BYTE* ) &File, sizeof( ARCHIVE_FILE ) ) )
        {
            VFS_File_Close( hFile );
            return VFS_FALSE;
        }
    }

    // Close the File.
    if( !VFS_File_Close( hFile ) )
        return VFS_FALSE;

    return VFS_TRUE;
}