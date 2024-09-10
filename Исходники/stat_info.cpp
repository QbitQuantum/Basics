/*
  UNIX note:
  We want to stat the given file. We may be operating as root, but
  root == nobody across most NFS file systems, so we may have to do it
  as condor.  If we succeed, we proceed, if the file has already been
  removed we handle it.  If we cannot do it as either root or condor,
  we report an error.
*/
void
StatInfo::stat_file( const char *path )
{
		// Initialize
	init( );

		// Ok, run stat
	StatWrapper statbuf;
	int status = statbuf.Stat( path, StatWrapper::STATOP_STAT );

# if (! defined WIN32)
	if ( !status ) {
		status = statbuf.Stat( StatWrapper::STATOP_LSTAT );
	}
# endif

		// How'd it go?
	if ( status ) {
		si_errno = statbuf.GetErrno( );

# if (! defined WIN32 )
		if ( EACCES == si_errno ) {
				// permission denied, try as condor
			priv_state priv = set_condor_priv();
			status = statbuf.Retry( );
			set_priv( priv );

			if( status < 0 ) {
				si_errno = statbuf.GetErrno( );
			}
		}
# endif
	}

		// If we've failed, just bail out
	if ( status ) {
		if (( ENOENT == si_errno ) || (EBADF == si_errno) ) {
			si_error = SINoFile;
		} else {
			dprintf( D_FULLDEBUG, 
					 "StatInfo::%s(%s) failed, errno: %d = %s\n",
					 statbuf.GetStatFn(),path,si_errno,strerror(si_errno) );
		}
		return;
	}

	init( &statbuf );

}