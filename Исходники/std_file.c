static Bool mygetline(FILELIST *flptr)
{
  register int32    i ;
  register int32    temp ;
  register FILELIST *flinptr , *floutptr ;
  register int32    count ;
  register uint8    *ptr ;

  flinptr  = theIStdin ( workingsave ) ;
  floutptr = theIStdout( workingsave ) ;

  if (! isIOpenFileFilterById( theISaveStdinFilterId( workingsave ), flinptr)) {
    SetIIOErrFlag( flptr ) ;
    return error_handler(IOERROR);
  }
  if ( stream_echo_flag &&
      ! isIOpenFileFilterById( theISaveStdoutFilterId( workingsave ), floutptr)) {
    SetIIOErrFlag( flptr ) ;
    return error_handler(IOERROR);
  }

  count = 0 ;
  ptr = theIPtr( flptr ) = theIBuffer( flptr ) ;

  if (( temp = Getc( flinptr )) == EOF ) {
    SetIEofFlag( flptr ) ;
    if ( isIIOError( flinptr )) {
      SetIIOErrFlag( flptr ) ;
      return (*theIFileLastError( flinptr ))( flinptr ) ;
    }
    else
      return FALSE ;
  }
  UnGetc( temp , flinptr ) ;

  do {
    if (( temp = Getc( flinptr )) == EOF ) {
      SetIEofFlag( flptr ) ;
      if ( isIIOError( flinptr )) {
        SetIIOErrFlag( flptr ) ;
        return (*theIFileLastError( flinptr ))( flinptr ) ;
      }
      else
        return FALSE ;
    }

    switch ( temp ) {
    case controlU :
      if ( stream_echo_flag ) {
        for ( i = 0 ; i < count ; ++i )
          if ( Putc( controlH , floutptr ) == EOF )
            return (*theIFileLastError( flptr ))( floutptr ) ;

        if ((*theIMyFlushFile( floutptr ))( floutptr ) == EOF )
          return (*theIFileLastError( flptr ))( floutptr ) ;
      }
      count = 0 ;
      break ;
    case controlR :
      if ( stream_echo_flag ) {
        if ( Putc( '\r' , floutptr ) == EOF )
          return (*theIFileLastError( flptr ))( floutptr ) ;

        for ( i = 0 ; i < count ; ++i )
          if ( Putc( theIBuffer( flptr )[ i ] , floutptr ) == EOF )
            return (*theIFileLastError( flptr ))( floutptr ) ;

        if ((*theIMyFlushFile( floutptr ))( floutptr ) == EOF )
          return (*theIFileLastError( flptr ))( floutptr ) ;
      }
      break ;
    case controlC :
      if ( stream_echo_flag ) {
        if ( Putc( '\r' , floutptr ) == EOF )
          return (*theIFileLastError( flptr ))( floutptr ) ;

        if ((*theIMyFlushFile( floutptr ))( floutptr ) == EOF )
          return (*theIFileLastError( flptr ))( floutptr ) ;
      }
      count = 0 ;
      break ;
    case controlH :
      if ( count > 0 ) {
        count-- ;
        ptr-- ;
        if ( stream_echo_flag ) {
          if ( Putc( controlH , floutptr ) == EOF )
            return (*theIFileLastError( flptr ))( floutptr ) ;

          if ((*theIMyFlushFile( floutptr ))( floutptr ) == EOF )
            return (*theIFileLastError( flptr ))( floutptr ) ;
        }
      }
      break ;
    default:
      if ( count == LINEMAX ) {
        SetIIOErrFlag( flptr ) ;
        return error_handler( IOERROR ) ;
      }
      *ptr = (uint8) temp ; count++ ; ptr++ ;

      if ( stream_echo_flag ) {
        if ( Putc( temp , floutptr ) == EOF )
          return (*theIFileLastError( flptr ))( floutptr ) ;
        if ((*theIMyFlushFile( floutptr ))( floutptr ) == EOF )
          return (*theIFileLastError( flptr ))( floutptr ) ;
      }
    }
  } while ( ! (( temp == LF ) || ( temp == CR ))) ;

  theICount( flptr ) = count ;
  return TRUE ;
}