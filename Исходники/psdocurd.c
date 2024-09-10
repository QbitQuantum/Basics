INT
SheChangeDirW(
   register WCHAR *newdir
   )
{
   WCHAR       denvname[ 4 ];
   WCHAR       newpath[ MAX_PATH ];
   WCHAR       denvvalue[ MAX_PATH ];
   WCHAR       c, *s;
   DWORD       attr;

   GetCurrentDirectoryW( MAX_PATH, denvvalue );
   c = (WCHAR)(DWORD)CharUpperW((LPTSTR)(DWORD)denvvalue[0]);

   denvname[0] = WCHAR_EQUAL;
   if (IsCharAlphaW(*newdir) && newdir[1] == WCHAR_COLON) {
      denvname[1] = (WCHAR)(DWORD)CharUpperW((LPTSTR)(DWORD)*newdir);
      newdir += 2;
   } else {
      denvname[ 1 ] = c;
   }
   denvname[ 2 ] = WCHAR_COLON;
   denvname[ 3 ] = WCHAR_NULL;

   if ((*newdir == WCHAR_BSLASH) || (*newdir == WCHAR_SLASH)) {
      newpath[ 0 ] = denvname[ 1 ];
      newpath[ 1 ] = denvname[ 2 ];
      wcscpy( &newpath[ 2 ], newdir );
   } else {
      if (NULL != (s = SheGetEnvVarW( denvname ))) {
         wcscpy( newpath, s );
      } else {
         newpath[ 0 ] = denvname[ 1 ];
         newpath[ 1 ] = denvname[ 2 ];
         newpath[ 2 ] = WCHAR_NULL;
      }
      s = newpath + wcslen( newpath );
      *s++ = WCHAR_BSLASH;
      wcscpy( s, newdir );
   }

   if (!GetFullPathNameW(newpath, MAX_PATH, denvvalue, &s )) {
      return( ERROR_ACCESS_DENIED );
   }

   attr = GetFileAttributesW( denvvalue );
   if (attr == -1 || !(attr & FILE_ATTRIBUTE_DIRECTORY)) {
      return( ERROR_ACCESS_DENIED );
   }

   if (SheSetEnvVarW(denvname,denvvalue)) {
      return( ERROR_NOT_ENOUGH_MEMORY );
   }

   SetCurrentDirectoryW( denvvalue );

   // this seems wrong... SheGetDir(GD_DEFAULT, CurDrvDirW) ;
   wcscpy(CurDrvDirW, denvvalue);   // this seems right to me.
   return(SUCCESS) ;
}