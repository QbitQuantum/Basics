int  stat( REG1 char *name, REG2 struct stat *buf)
{
    struct FileFindBuf findbuf;
    unsigned findcount = 1;     /* Find only 1 match */
    unsigned findhandle = -1;   /* any unused handle */

    char * oldcwd;          /* Pointer to current directory */

    unsigned long dmap;     /* Valid Drive Map (ignored) */
    int drive;          /* A: = 1, B: = 2, etc. */

    /* Don't allow wildcards to be interpreted by system */

    if (strpbrk(name, "?*")) {
        errno = ENOENT;
        _doserrno = E_nofile;
        return(-1);
    }

    /* Try to get disk from name.  If none, get current disk.  */

    if (name[1] == ':'){

        drive = tolower(*name) - 'a' + 1;
    }
    else
        (void) DOSQCURDISK((unsigned far *) &drive,
        (unsigned long far *) &dmap);

    /* Call Find Match File */

    errno = ENOENT;

    if (DOSFINDFIRST((char far *)name, (unsigned far *)&findhandle, A_D|A_S|A_H,
    (struct FileFindBuf far *) &findbuf, sizeof(findbuf),
    (unsigned far *) &findcount, 0L)) {

        if ( STRPBRK(name, "./\\") ) {  /* Possible root directory? */
            if ( ! ( oldcwd = _getdcwd(drive, NULL, -1) ) )
                return( -1 );
            if ( chdir( name ) != -1 ) {
                chdir( oldcwd ); /* Must be a root directory */
                free( oldcwd );
            }
            else {
                free( oldcwd );
                return( -1 );
            }

            findbuf.attributes = A_D;
            findbuf.file_size = 0L;
            findbuf.write_date = (1 << 5) + 1; /* 1 January 1980 */
            findbuf.write_time = 0;        /* 00:00:00 */
            findbuf.access_date =
                findbuf.create_date =
                findbuf.access_time =
                findbuf.create_time = 0;
        }
        else
            return( -1 );

    }
    else
        DOSFINDCLOSE(findhandle);   /* Release Find handle */

    /* Fill in buf */

    buf->st_uid = buf->st_gid = buf->st_ino = 0;

    buf->st_rdev = buf->st_dev = drive - 1; /* A=0, B=1, etc. */

    /* now set the common fields */

    buf->st_mode = _dtoxmode(findbuf.attributes, name);
    buf->st_nlink = 1;
    buf->st_size = findbuf.file_size;
    buf->st_mtime = XTIME(findbuf.write_date, findbuf.write_time);

    /*
     * If create and access times are 0L, use modification time instead
     */
    if( findbuf.create_date || findbuf.create_time )
        buf->st_ctime = XTIME(findbuf.create_date, findbuf.create_time);
    else
        buf->st_ctime = buf->st_mtime;

    if( findbuf.access_date || findbuf.access_time )
        buf->st_atime = XTIME(findbuf.access_date, findbuf.access_time);
    else
        buf->st_atime = buf->st_mtime;

    return(0);
}