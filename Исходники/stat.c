static unsigned short at2mode( int attr, char *fname )
/****************************************************/
{
    unsigned short  mode;
    char            *ext;

    if( attr & _A_SUBDIR ) {
        mode = S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
    } else if( attr & AT_ISCHR ) {
        mode = S_IFCHR;
    } else {
        mode = S_IFREG;
        /* determine if file is executable, very PC specific */
        if( (ext = _mbschr( fname, '.' )) != NULL ) {
            ++ext;
            if( _mbscmp( ext, "EXE" ) == 0 || _mbscmp( ext, "COM" ) == 0 ) {
                mode |= S_IXUSR | S_IXGRP | S_IXOTH;
            }
        }
    }
    mode |= S_IRUSR | S_IRGRP | S_IROTH;
    if( !(attr & _A_RDONLY) )                   /* if file is not read-only */
        mode |= S_IWUSR | S_IWGRP | S_IWOTH;    /* - indicate writeable     */
    return( mode );
}