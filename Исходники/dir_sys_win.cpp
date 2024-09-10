bool fal_move( const String &filename, const String &dest, int32 &fsStatus )
{
   String fname1 = filename;
   Path::uriToWin( fname1 );
   String fname2 = dest;
   Path::uriToWin( fname2 );

   AutoWString wBuffer1( fname1 );
   AutoWString wBuffer2( fname2 );
   BOOL res = MoveFileW( wBuffer1.w_str(), wBuffer2.w_str() );

	if( ! res && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED )
	{
      AutoCString cBuffer1( fname1 );
      AutoCString cBuffer2( fname2 );
      res = MoveFile( cBuffer1.c_str(), cBuffer2.c_str() );
	}

   if ( res == TRUE ) {
      return true;
   }
   fsStatus = GetLastError();
   return false;
}