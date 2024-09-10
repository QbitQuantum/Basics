  //---------------------------------------------------------------------------
  // receives only one character
  bool Serial::receive( char & c )
  {

    if ( !isPortOpened_ )
    {
      if ( !openPort() )
      {
        // some error occured by opening port
        return false;
      }
    }

    int numberOfBytes;
    numberOfBytes =::read( descriptor_, & c, 1 );

    if ( numberOfBytes == 1 )
    {
      return true;
    }
    else
    {
      setStatusString( "error: could not receive the character" );
      return false;
    }
  }