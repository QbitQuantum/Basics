 // Path to user home directory
 bool GetHomePath( std::string& path )
 {
   char szBuffer[ MAX_PATH ];
   ZeroMemory( szBuffer, MAX_PATH );
   
   DWORD dwRet = ExpandEnvironmentStringsA( "%USERPROFILE%", szBuffer, MAX_PATH );
   if ( dwRet == 0 )
   {
     dwRet = ExpandEnvironmentStringsA( "%HOMEDRIVE%", szBuffer, MAX_PATH );
     if ( dwRet == 0 )
     {
       return false;
     }
     path = szBuffer;
     dwRet = ExpandEnvironmentStringsA( "%HOMEPATH%", szBuffer, MAX_PATH );
     if ( dwRet == 0 )
     {
       return false;
     }
     path += szBuffer;
   }
   else
   {
     path = szBuffer;
   }
   if ( path.at( path.length() - 1 ) != PATH_SEPARATOR )
   {
       path += PATH_SEPARATOR;
   }
   return true;
 }