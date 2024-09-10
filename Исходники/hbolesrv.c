STDAPI DllRegisterServer( void )
{
   TCHAR lpKeyName[ MAX_REGSTR_SIZE ];
   TCHAR lpNameBuf[ MAX_REGSTR_SIZE ];
   TCHAR lpValue  [ MAX_REGSTR_SIZE ];
   LPCTSTR lpValName;
   HRESULT hr = S_OK;
   HKEY hKey;
   long err;
   int i;

   for( i = 0; i < ( int ) HB_SIZEOFARRAY( s_regTable ); ++i )
   {
      s_getKeyValue( s_regTable[ i ][ 0 ], lpKeyName, MAX_REGSTR_SIZE );
      if( s_regTable[ i ][ 1 ] )
      {
         s_getKeyValue( s_regTable[ i ][ 1 ], lpNameBuf, MAX_REGSTR_SIZE );
         lpValName = lpNameBuf;
      }
      else
         lpValName = NULL;
      s_getKeyValue( s_regTable[ i ][ 2 ], lpValue, MAX_REGSTR_SIZE );

      err = RegCreateKeyEx( HKEY_CLASSES_ROOT, lpKeyName,
                            0, NULL, REG_OPTION_NON_VOLATILE,
                            KEY_SET_VALUE | KEY_CREATE_SUB_KEY,
                            NULL, &hKey, NULL );

      if( err == ERROR_SUCCESS )
      {
         err = RegSetValueEx( hKey, lpValName, 0, REG_SZ,
                              ( const BYTE * ) lpValue,
                              ( lstrlen( lpValue ) + 1 ) * sizeof( TCHAR ) );
         RegCloseKey( hKey );
      }
      if( err != ERROR_SUCCESS )
      {
         DllUnregisterServer();
         hr = SELFREG_E_CLASS;
         break;
      }
   }

   return hr;
}