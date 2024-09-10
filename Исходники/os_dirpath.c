int opal_os_dirpath_access(const char *path, const mode_t in_mode ) {
#ifndef __WINDOWS__
    struct stat buf;
#else
#  ifndef _MSC_VER
    struct stat buf;
#  else
    struct __stat64 buf;
#  endif
#endif
    mode_t loc_mode = S_IRWXU;  /* looking for full rights */

    /*
     * If there was no mode specified, use the default mode
     */
    if( 0 != in_mode ) {
        loc_mode = in_mode;
    }

#ifndef __WINDOWS__
    if (0 == stat(path, &buf)) { /* exists - check access */
#else
    if (0 == _stat64(path, &buf)) { /* exist -- check */
#endif
        if ((buf.st_mode & loc_mode) == loc_mode) { /* okay, I can work here */
            return(OPAL_SUCCESS);
        }
        else {
            /* Don't have access rights to the existing path */
            return(OPAL_ERROR);
        }
    }
    else {
        /* We could not find the path */
        return( OPAL_ERR_NOT_FOUND );
    }
}