_WCRTLINK int stat( CHAR_TYPE const *path, struct stat *buf )
{
    const CHAR_TYPE *   ptr;
    CHAR_TYPE           fullpath[_MAX_PATH];
    CHAR_TYPE       *   fullp;
    int                 isrootdir = 0;
    int                 handle;
    int                 RdosAttrib;
    int                 ok;
    CHAR_TYPE           name[_MAX_PATH];
    int                 attrib;
    unsigned long       wr_msb;
    unsigned long       wr_lsb;
    long                size;
    int                 ms;
    int                 us;
    struct tm           tm;
    int                 i;

    /* reject null string and names that has wildcard */
    if( *path == '\0' || _mbspbrk( path, "*?" ) != NULL )
        return( -1 );

    /*** Determine if 'path' refers to a root directory ***/
    if( _fullpath( fullpath, path, _MAX_PATH ) != NULL ) {
        if( isalpha( fullpath[0] )  &&  fullpath[1] == ':'  &&
            fullpath[2] == '\\'  &&  fullpath[3] == '\0' )
        {
            isrootdir = 1;
        }
    }
    else
        return( -1 );

    ptr = path;
    if( *_mbsinc(path ) )  ptr += 2;
    if( ( (ptr[0] == '\\' || ptr[0] == '/') && ptr[1] == '\0' )  ||  isrootdir )
    {
        /* handle root directory */
        CHAR_TYPE       cwd[_MAX_PATH];

        /* save current directory */
        getcwd( cwd, _MAX_PATH );

        /* try to change to specified root */
        if( chdir( path ) != 0 )  return( -1 );

        /* restore current directory */
        chdir( cwd );

        attrib   = _A_SUBDIR;    
        wr_msb   = 0;
        wr_lsb   = 0;
        size     = 0;
        name[0] = NULLCHAR;
    } else {                            /* not a root directory */
        fullp = fullpath + strlen( fullpath ) - 1;
        while( *fullp != '\\' && *fullp != '/' && fullp != fullpath )
            fullp--;
        *fullp = 0;
        fullp++;
        if( strlen( fullpath ) == 0 )
            strcpy( fullpath, "*" );
                        
        handle = RdosOpenDir( fullpath );

        ok = 0;
        i = 0;
        strlwr( fullp );
        while( RdosReadDir( handle, i, _MAX_PATH, name, &size, &RdosAttrib, &wr_msb, &wr_lsb ) ) {
            strlwr( name );        
            if( !strcmp( name, fullp ) ) {
                ok = 1;
                break;
            }
            i++;
        }

        RdosCloseDir( handle );

        if( !ok )
            return( -1 );

        attrib = 0;
        if( RdosAttrib & FILE_ATTRIBUTE_ARCHIVE ) {
            attrib |= _A_ARCH;
        }
        if( RdosAttrib & FILE_ATTRIBUTE_DIRECTORY ) {
            attrib |= _A_SUBDIR;
        }
        if( RdosAttrib & FILE_ATTRIBUTE_HIDDEN ) {
            attrib |= _A_HIDDEN;
        }
        if( RdosAttrib & FILE_ATTRIBUTE_NORMAL ) {
            attrib |= _A_NORMAL;
        }
        if( RdosAttrib & FILE_ATTRIBUTE_READONLY ) {
            attrib |= _A_RDONLY;
        }
        if( RdosAttrib & FILE_ATTRIBUTE_SYSTEM ) {
            attrib |= _A_SYSTEM;
        }
    }

    /* process drive number */
    if( *_mbsinc(path) ) {
        buf->st_dev = tolower( fullpath[0] ) - 'a';
    } else {
        buf->st_dev = RdosGetCurDrive();
    }
    buf->st_rdev = buf->st_dev;

    buf->st_size = size;
    buf->st_mode = at2mode( attrib, name );

    RdosDecodeMsbTics( wr_msb, 
                       &tm.tm_year, 
                       &tm.tm_mon,
                       &tm.tm_mday,
                       &tm.tm_hour );

    RdosDecodeLsbTics( wr_lsb,
                       &tm.tm_min,
                       &tm.tm_sec,
                       &ms,
                       &us );
                           
    tm.tm_year -= 1900;
    tm.tm_mon--;
    tm.tm_isdst = -1;
    tm.tm_wday = -1;
    tm.tm_yday = -1;

    buf->st_mtime = mktime( &tm );
    buf->st_atime = buf->st_ctime = buf->st_btime = buf->st_mtime;

    buf->st_nlink = 1;
    buf->st_ino = buf->st_uid = buf->st_gid = 0;

    buf->st_attr = attrib;
    buf->st_archivedID = 0;
    buf->st_updatedID = 0;
    buf->st_inheritedRightsMask = 0;
    buf->st_originatingNameSpace = 0;

    return( 0 );
}