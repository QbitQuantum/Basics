uint QFile::size() const
{
    STATBUF st;
    if ( isOpen() ) {
	FSTAT( fh ? FILENO(fh) : fd, &st );
        return st.st_size;
    } else {
#if defined(__CYGWIN32_)
	STAT( QFile::encodeName(fn), &st );
#else
        QString str = fn;
        reslashify(str);
#ifdef QT_LARGEFILE_SUPPORT
        if ( _wstati64( (wchar_t*) str.ucs2(), &st ) != -1 ) {
#else
        if ( _wstat( (wchar_t*) str.ucs2(), &st ) != -1 ) {
#endif
#endif
            return st.st_size;
        }
    }
    return 0;
}

/*!
  \fn int QFile::at() const
  Returns the file index.
  \sa size()
*/

/*!
  Sets the file index to \e pos. Returns TRUE if successful, otherwise FALSE.

  Example:
  \code
    QFile f( "data.bin" );
    f.open( IO_ReadOnly );			// index set to 0
    f.at( 100 );				// set index to 100
    f.at( f.at()+50 );				// set index to 150
    f.at( f.size()-80 );			// set index to 80 before EOF
    f.close();
  \endcode

  \warning The result is undefined if the file was \link open() opened\endlink
  using the \c IO_Append specifier.

  \sa size(), open()
*/

bool QFile::at( int pos )
{
    if ( !isOpen() ) {
#if defined(CHECK_STATE)
	qWarning( "QFile::at: File is not open" );
#endif
	return FALSE;
    }
    bool ok;
    if ( isRaw() ) {				// raw file
	pos = (int)LSEEK(fd, pos, SEEK_SET);
	ok = pos != -1;
    } else {					// buffered file
	ok = fseek(fh, pos, SEEK_SET) == 0;
    }
    if ( ok )
	ioIndex = pos;
#if defined(CHECK_RANGE)
    else
	qWarning( "QFile::at: Cannot set file position %d", pos );
#endif
    return ok;
}

/*!
  Reads at most \e len bytes from the file into \e p and returns the
  number of bytes actually read.

  Returns -1 if a serious error occurred.

  \warning We have experienced problems with some C libraries when a buffered
  file is opened for both reading and writing. If a read operation takes place
  immediately after a write operation, the read buffer contains garbage data.
  Worse, the same garbage is written to the file. Calling flush() before
  readBlock() solved this problem.

  \sa writeBlock()
*/

int QFile::readBlock( char *p, uint len )
{
#if defined(CHECK_NULL)
    if ( !p )
	qWarning( "QFile::readBlock: Null pointer error" );
#endif
#if defined(CHECK_STATE)
    if ( !isOpen() ) {				// file not open
	qWarning( "QFile::readBlock: File not open" );
	return -1;
    }
    if ( !isReadable() ) {			// reading not permitted
	qWarning( "QFile::readBlock: Read operation not permitted" );
	return -1;
    }
#endif
    int nread;					// number of bytes read
    if ( isRaw() ) {				// raw file
	nread = READ( fd, p, len );
	if ( len && nread <= 0 ) {
	    nread = 0;
	    setStatus(IO_ReadError);
	}
    } else {					// buffered file
	nread = (int)fread( p, 1, len, fh );
	if ( (uint)nread != len ) {
	    if ( ferror( fh ) || nread==0 )
		setStatus(IO_ReadError);
	}
    }
    ioIndex += nread;
    return nread;
}

/*! \overload int writeBlock( const QByteArray& data )
*/

/*! \reimp

  Writes \e len bytes from \e p to the file and returns the number of
  bytes actually written.

  Returns -1 if a serious error occurred.

  \warning When working with buffered files, data may not be written
  to the file at once. Call flush() to make sure the data is really
  written.

  \sa readBlock()
*/

int QFile::writeBlock( const char *p, uint len )
{
#if defined(CHECK_NULL)
    if ( p == 0 && len != 0 )
	qWarning( "QFile::writeBlock: Null pointer error" );
#endif
#if defined(CHECK_STATE)
    if ( !isOpen() ) {				// file not open
	qWarning( "QFile::writeBlock: File not open" );
	return -1;
    }
    if ( !isWritable() ) {			// writing not permitted
	qWarning( "QFile::writeBlock: Write operation not permitted" );
	return -1;
    }
#endif
    int nwritten;				// number of bytes written
    if ( isRaw() )				// raw file
	nwritten = WRITE( fd, p, len );
    else					// buffered file
	nwritten = (int)fwrite( p, 1, len, fh );
    if ( nwritten != (int)len ) {		// write error
	if ( errno == ENOSPC )			// disk is full
	    setStatus( IO_ResourceError );
	else
	    setStatus( IO_WriteError );
	if ( isRaw() )				// recalc file position
	    ioIndex = (int)LSEEK( fd, 0, SEEK_CUR );
	else
	    ioIndex = fseek( fh, 0, SEEK_CUR );
    } else {
	ioIndex += nwritten;
    }
    if ( ioIndex > length )			// update file length
	length = ioIndex;
    return nwritten;
}

/*!
  Returns the file handle of the file.

  This is a small positive integer, suitable for use with C library
  functions such as fdopen() and fcntl(), as well as with QSocketNotifier.

  If the file is not open or there is an error, handle() returns -1.

  \sa QSocketNotifier
*/

int QFile::handle() const
{
    if ( !isOpen() )
	return -1;
    else if ( fh )
	return FILENO( fh );
    else
	return fd;
}

/*!
  Closes an open file.

  The file is not closed if it was opened with an existing file handle.
  If the existing file handle is a \c FILE*, the file is flushed.
  If the existing file handle is an \c int file descriptor, nothing
  is done to the file.

  Some "write-behind" filesystems may report an unspecified error on
  closing the file. These errors only indicate that something may
  have gone wrong since the previous open(). In such a case status()
  reports IO_UnspecifiedError after close(), otherwise IO_Ok.

  \sa open(), flush()
*/


void QFile::close()
{
    bool ok = FALSE;
    if ( isOpen() ) {				// file is not open
	if ( fh ) {				// buffered file
	    if ( ext_f )
		ok = fflush( fh ) != -1;	// flush instead of closing
	    else
		ok = fclose( fh ) != -1;
	} else {				// raw file
	    if ( ext_f )
		ok = TRUE;			// cannot close
	    else
		ok = CLOSE( fd ) != -1;
	}
	init();					// restore internal state
    }
    if (!ok)
	setStatus (IO_UnspecifiedError);

    return;
}