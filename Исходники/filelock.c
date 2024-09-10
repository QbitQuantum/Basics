static int
filelock_lock( FileLock*  lock )
{
    int    ret;
#ifdef _WIN32
    int  pidfile_fd = -1;

    ret = _mkdir( lock->lock );
    if (ret < 0) {
        if (errno == ENOENT) {
            D( "could not access directory '%s', check path elements", lock->lock );
            return -1;
        } else if (errno != EEXIST) {
            D( "_mkdir(%s): %s", lock->lock, strerror(errno) );
            return -1;
        }

        
        
        D("directory '%s' already exist, waiting a bit to ensure that no other emulator instance is starting", lock->lock );
        {
            int  _sleep = 200;
            int  tries;

            for ( tries = 4; tries > 0; tries-- )
            {
                pidfile_fd = open( lock->temp, O_RDONLY );

                if (pidfile_fd >= 0)
                    break;

                Sleep( _sleep );
                _sleep *= 2;
            }
        }

        if (pidfile_fd < 0) {
            D( "no pid file in '%s', assuming stale directory", lock->lock );
        }
        else
        {
            
            char            buf[16];
            int             len, lockpid;
            HANDLE          processSnapshot;
            PROCESSENTRY32  pe32;
            int             is_locked = 0;

            len = read( pidfile_fd, buf, sizeof(buf)-1 );
            if (len < 0) {
                D( "could not read pid file '%s'", lock->temp );
                close( pidfile_fd );
                return -1;
            }
            buf[len] = 0;
            lockpid  = atoi(buf);

            
            if (lockpid == 0)
                lockpid = -1;

            close( pidfile_fd );

            pe32.dwSize     = sizeof( PROCESSENTRY32 );
            processSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

            if ( processSnapshot == INVALID_HANDLE_VALUE ) {
                D( "could not retrieve the list of currently active processes\n" );
                is_locked = 1;
            }
            else if ( !Process32First( processSnapshot, &pe32 ) )
            {
                D( "could not retrieve first process id\n" );
                CloseHandle( processSnapshot );
                is_locked = 1;
            }
            else
            {
                do {
                    if (pe32.th32ProcessID == lockpid) {
                        is_locked = 1;
                        break;
                    }
                } while (Process32Next( processSnapshot, &pe32 ) );

                CloseHandle( processSnapshot );
            }

            if (is_locked) {
                D( "the file '%s' is locked by process ID %d\n", lock->file, lockpid );
                return -1;
            }
        }
    }

    
    pidfile_fd = open( lock->temp, O_WRONLY | O_CREAT | O_TRUNC );
    if (pidfile_fd < 0) {
        if (errno == EACCES) {
            if ( path_delete_file( lock->temp ) < 0 ) {
                D( "could not remove '%s': %s\n", lock->temp, strerror(errno) );
                return -1;
            }
            pidfile_fd = open( lock->temp, O_WRONLY | O_CREAT | O_TRUNC );
        }
        if (pidfile_fd < 0) {
            D( "could not create '%s': %s\n", lock->temp, strerror(errno) );
            return -1;
        }
    }

    {
        char  buf[16];
        sprintf( buf, "%ld", GetCurrentProcessId() );
        ret = write( pidfile_fd, buf, strlen(buf) );
        close(pidfile_fd);
        if (ret < 0) {
            D( "could not write PID to '%s'\n", lock->temp );
            return -1;
        }
    }

    lock->locked = 1;
    return 0;
#else
    int    temp_fd = -1;
    int    lock_fd = -1;
    int    rc, tries, _sleep;
    FILE*  f = NULL;
    char   pid[8];
    struct stat  st_temp;

    strcpy( lock->temp, lock->file );
    strcat( lock->temp, TEMP_NAME );
    temp_fd = mkstemp( lock->temp );

    if (temp_fd < 0) {
        D("cannot create locking temp file '%s'", lock->temp );
        goto Fail;
    }

    sprintf( pid, "%d", getpid() );
    ret = write( temp_fd, pid, strlen(pid)+1 );
    if (ret < 0) {
        D( "cannot write to locking temp file '%s'", lock->temp);
        goto Fail;
    }
    close( temp_fd );
    temp_fd = -1;

    CHECKED(rc, lstat( lock->temp, &st_temp ));
    if (rc < 0) {
        D( "can't properly stat our locking temp file '%s'", lock->temp );
        goto Fail;
    }

    
    _sleep = 0;
    for ( tries = 4; tries > 0; tries-- )
    {
        struct stat  st_lock;
        int          rc;

        if (_sleep > 0) {
            if (_sleep > 2000000) {
                D( "cannot acquire lock file '%s'", lock->lock );
                goto Fail;
            }
            usleep( _sleep );
        }
        _sleep += 200000;

        
        CHECKED(rc, link( lock->temp, lock->lock ));

        CHECKED(rc, lstat( lock->lock, &st_lock ));
        if (rc == 0 &&
            st_temp.st_rdev == st_lock.st_rdev &&
            st_temp.st_ino  == st_lock.st_ino  )
        {
            
            lock->locked = 1;
            CHECKED(rc, unlink( lock->temp ));
            return 0;
        }

        
        
        if (rc == 0) {
            char    buf[16];
            time_t  now;
            int     lockpid = 0;
            int     lockfd;
            int     stale = 2;  
            struct stat  st;

            CHECKED(rc, time( &now));
            st.st_mtime = now - 120;

            CHECKED(lockfd, open( lock->lock,O_RDONLY ));
            if ( lockfd >= 0 ) {
                int  len;

                CHECKED(len, read( lockfd, buf, sizeof(buf)-1 ));
                buf[len] = 0;
                lockpid = atoi(buf);

                CHECKED(rc, fstat( lockfd, &st ));
                if (rc == 0)
                  now = st.st_atime;

                CHECKED(rc, close(lockfd));
            }
            
            if (lockpid > 0) {
                CHECKED(rc, kill( lockpid, 0 ));
                if (rc == 0 || errno == EPERM) {
                    stale = 0;
                } else if (rc < 0 && errno == ESRCH) {
                    stale = 1;
                }
            }
            if (stale == 2) {
                
                stale = (now >= st.st_mtime + 60);
            }

            if (stale) {
                D( "removing stale lockfile '%s'", lock->lock );
                CHECKED(rc, unlink( lock->lock ));
                _sleep = 0;
                tries++;
            }
        }
    }
    D("file '%s' is already in use by another process", lock->file );

Fail:
    if (f)
        fclose(f);

    if (temp_fd >= 0) {
        close(temp_fd);
    }

    if (lock_fd >= 0) {
        close(lock_fd);
    }

    unlink( lock->lock );
    unlink( lock->temp );
    return -1;
#endif
}