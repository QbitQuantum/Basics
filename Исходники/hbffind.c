static HB_BOOL hb_fsFindNextLow( PHB_FFIND ffind )
{
   HB_BOOL bFound;

   int iYear  = 0;
   int iMonth = 0;
   int iDay   = 0;

   int iHour = 0;
   int iMin  = 0;
   int iSec  = 0;
   int iMSec = 0;

   HB_FATTR raw_attr = 0, nAttr = 0;

   /* Set the default values in case some platforms don't
      support some of these, or they may fail on them. */

   ffind->szName[ 0 ] = '\0';
   ffind->size = 0;

   /* Do platform dependant first/next search */

   hb_vmUnlock();

#if defined( HB_OS_DOS )

   {
      PHB_FFIND_INFO info = ( PHB_FFIND_INFO ) ffind->info;

      /* Handling HB_FA_LABEL doesn't need any special tricks
         under the MS-DOS platform. */

      if( ffind->bFirst )
      {
         ffind->bFirst = HB_FALSE;

         /* tzset(); */

#if defined( __WATCOMC__ )
         bFound = ( _dos_findfirst( ffind->pszFileMask, ( HB_USHORT ) hb_fsAttrToRaw( ffind->attrmask ), &info->entry ) == 0 );
#else
         bFound = ( findfirst( ffind->pszFileMask, &info->entry, ( HB_USHORT ) hb_fsAttrToRaw( ffind->attrmask ) ) == 0 );
#endif
      }
      else
      {
#if defined( __WATCOMC__ )
         bFound = ( _dos_findnext( &info->entry ) == 0 );
#else
         bFound = ( findnext( &info->entry ) == 0 );
#endif
      }

      /* Fill Harbour found file info */

      if( bFound )
      {
         hb_strncpy( ffind->szName, info->entry.ff_name, sizeof( ffind->szName ) - 1 );
         ffind->size = info->entry.ff_fsize;

         raw_attr = info->entry.ff_attrib;

         {
            time_t ftime;
            struct tm * ft;
            struct stat sStat;

            stat( info->entry.ff_name, &sStat );

            ftime = sStat.st_mtime;
            ft = localtime( &ftime );

            iYear  = ft->tm_year + 1900;
            iMonth = ft->tm_mon + 1;
            iDay   = ft->tm_mday;

            iHour  = ft->tm_hour;
            iMin   = ft->tm_min;
            iSec   = ft->tm_sec;
         }
      }
      hb_fsSetIOError( bFound, 0 );
   }

#elif defined( HB_OS_OS2 )

   {
      #define HB_OS2_DIRCNT   16

      PHB_FFIND_INFO info = ( PHB_FFIND_INFO ) ffind->info;
      APIRET ret = NO_ERROR;

      /* TODO: HB_FA_LABEL handling */

      if( ffind->bFirst )
      {
         ffind->bFirst = HB_FALSE;

         info->isWSeB = hb_isWSeB();

         info->findSize = sizeof( FILEFINDBUF3L );
         if( info->findSize & 0x07 )
            info->findSize += 0x08 - ( info->findSize & 0x07 );
         info->findSize *= HB_OS2_DIRCNT;
         if( info->findSize > 0xF000 )
            info->findSize = 0xF000;
         info->findInitCnt = ! info->isWSeB ? info->findSize / 32 : HB_OS2_DIRCNT;

         info->hFindFile = HDIR_CREATE;
         info->findCount = info->findInitCnt;
         ret = DosAllocMem( &info->entry, info->findSize, OBJ_TILE | PAG_COMMIT | PAG_WRITE );
         if( ret == NO_ERROR )
         {
            ret = DosFindFirst( ( PCSZ ) ffind->pszFileMask,
                                &info->hFindFile,
                                ( ULONG ) hb_fsAttrToRaw( ffind->attrmask ),
                                info->entry,
                                info->findSize,
                                &info->findCount,
                                FIL_STANDARDL );
            bFound = ret == NO_ERROR && info->findCount > 0;
            if( bFound )
               info->next = info->entry;
         }
         else
         {
            info->entry = NULL;
            bFound = HB_FALSE;
         }
      }
      else if( info->findCount == 0 )
      {
         info->findCount = info->findInitCnt;
         ret = DosFindNext( info->hFindFile,
                            info->entry,
                            info->findSize,
                            &info->findCount );
         bFound = ret == NO_ERROR && info->findCount > 0;
         if( bFound )
            info->next = info->entry;
      }
      else
         bFound = HB_TRUE;

      if( bFound )
      {
         ULONG oNextEntryOffset;

         if( info->isWSeB )
         {
            PFILEFINDBUF3L pFFB = ( PFILEFINDBUF3L ) info->next;

            hb_strncpy( ffind->szName, pFFB->achName, sizeof( ffind->szName ) - 1 );
            ffind->size = ( HB_FOFFSET ) pFFB->cbFile;
            raw_attr = pFFB->attrFile;

            iYear  = pFFB->fdateLastWrite.year + 1980;
            iMonth = pFFB->fdateLastWrite.month;
            iDay   = pFFB->fdateLastWrite.day;

            iHour = pFFB->ftimeLastWrite.hours;
            iMin  = pFFB->ftimeLastWrite.minutes;
            iSec  = pFFB->ftimeLastWrite.twosecs * 2;

            oNextEntryOffset = pFFB->oNextEntryOffset;
         }
         else
         {
            PFILEFINDBUF3 pFFB = ( PFILEFINDBUF3 ) info->next;

            hb_strncpy( ffind->szName, pFFB->achName, sizeof( ffind->szName ) - 1 );
            ffind->size = ( HB_FOFFSET ) pFFB->cbFile;
            raw_attr = pFFB->attrFile;

            iYear  = pFFB->fdateLastWrite.year + 1980;
            iMonth = pFFB->fdateLastWrite.month;
            iDay   = pFFB->fdateLastWrite.day;

            iHour = pFFB->ftimeLastWrite.hours;
            iMin  = pFFB->ftimeLastWrite.minutes;
            iSec  = pFFB->ftimeLastWrite.twosecs * 2;

            oNextEntryOffset = pFFB->oNextEntryOffset;
         }

         if( oNextEntryOffset > 0 )
         {
            info->next = ( char * ) info->next + oNextEntryOffset;
            info->findCount--;
         }
         else
            info->findCount = 0;
      }

      hb_fsSetError( ( HB_ERRCODE ) ret );
   }

#elif defined( HB_OS_WIN )

   {
      PHB_FFIND_INFO info = ( PHB_FFIND_INFO ) ffind->info;

      bFound = HB_FALSE;

#if ! defined( HB_OS_WIN_CE )
      if( ( ffind->attrmask & HB_FA_LABEL ) != 0 && ! info->fLabelDone )
      {
         TCHAR lpVolName[ HB_PATH_MAX ];
         LPTSTR lpFileMask = NULL;
         char * mask = NULL;

         info->fLabelDone = HB_TRUE;

         if( ffind->pszFileMask && *ffind->pszFileMask )
         {
            PHB_FNAME pFileName = hb_fsFNameSplit( ffind->pszFileMask );
            if( pFileName->szName && pFileName->szName[ 0 ] )
               mask = hb_strdup( pFileName->szName );
            if( pFileName->szPath && pFileName->szPath[ 0 ] &&
                ( pFileName->szPath[ 1 ] ||
                  pFileName->szPath[ 0 ] != HB_OS_PATH_DELIM_CHR ) )
               lpFileMask = HB_CHARDUP( pFileName->szPath );
            hb_xfree( pFileName );
         }
         bFound = GetVolumeInformation( lpFileMask, lpVolName,
                                        HB_SIZEOFARRAY( lpVolName ),
                                        NULL, NULL, NULL, NULL, 0 ) != 0;
         if( bFound )
         {
            HB_OSSTRDUP2( lpVolName, ffind->szName, sizeof( ffind->szName ) - 1 );
            if( mask && *mask && ! hb_strMatchFile( ffind->szName, mask ) )
            {
               ffind->szName[ 0 ] = '\0';
               bFound = HB_FALSE;
            }
         }
         if( lpFileMask )
            hb_xfree( lpFileMask );
         if( mask )
            hb_xfree( mask );
      }
#endif

      if( ! bFound &&
          ( ffind->attrmask & ( HB_FA_LABEL | HB_FA_HIDDEN | HB_FA_SYSTEM |
                                HB_FA_DIRECTORY ) ) != HB_FA_LABEL )
      {
         if( ffind->bFirst )
         {
            LPTSTR lpFileMask = HB_CHARDUP( ffind->pszFileMask );
            ffind->bFirst = HB_FALSE;
            info->dwAttr    = ( DWORD ) hb_fsAttrToRaw( ffind->attrmask );
            info->hFindFile = FindFirstFile( lpFileMask, &info->pFindFileData );
            hb_xfree( lpFileMask );

            if( ( info->hFindFile != INVALID_HANDLE_VALUE ) && _HB_WIN_MATCH() )
               bFound = HB_TRUE;
         }

         if( ! bFound && info->hFindFile != INVALID_HANDLE_VALUE )
         {
            while( FindNextFile( info->hFindFile, &info->pFindFileData ) )
            {
               if( _HB_WIN_MATCH() )
               {
                  bFound = HB_TRUE;
                  break;
               }
            }
         }

         /* Fill Harbour found file info */

         if( bFound )
         {
            HB_OSSTRDUP2( info->pFindFileData.cFileName, ffind->szName, sizeof( ffind->szName ) - 1 );

            if( info->pFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
               ffind->size = 0;
            else
            {
#if defined( __XCC__ ) || ( defined( __POCC__ ) && __POCC__ >= 500 )
               /* NOTE: PellesC 5.00.1 will go into an infinite loop if we don't
                        split this into two operations. [vszakats] */
               ffind->size  = ( HB_FOFFSET ) info->pFindFileData.nFileSizeLow;
               ffind->size += ( HB_FOFFSET ) info->pFindFileData.nFileSizeHigh << 32;
#else
               ffind->size = ( HB_FOFFSET ) info->pFindFileData.nFileSizeLow +
                           ( ( HB_FOFFSET ) info->pFindFileData.nFileSizeHigh << 32 );
#endif
            }

            raw_attr = ( HB_FATTR ) info->pFindFileData.dwFileAttributes;

            /* NOTE: One of these may fail when searching on an UNC path, I
                     don't know yet what's the reason. [vszakats] */

            {
               FILETIME ft;
               SYSTEMTIME time;

               if( FileTimeToLocalFileTime( &info->pFindFileData.ftLastWriteTime, &ft ) &&
                   FileTimeToSystemTime( &ft, &time ) )
               {
                  iYear  = time.wYear;
                  iMonth = time.wMonth;
                  iDay   = time.wDay;
                  iHour  = time.wHour;
                  iMin   = time.wMinute;
                  iSec   = time.wSecond;
                  iMSec  = time.wMilliseconds;
               }
            }
         }
      }
      hb_fsSetIOError( bFound, 0 );
   }

#elif defined( HB_OS_UNIX )

   {
      PHB_FFIND_INFO info = ( PHB_FFIND_INFO ) ffind->info;

      char dirname[ HB_PATH_MAX ];

      bFound = HB_FALSE;

      /* TODO: HB_FA_LABEL handling */

      if( ffind->bFirst )
      {
         char * pos;

         ffind->bFirst = HB_FALSE;

         hb_strncpy( dirname, ffind->pszFileMask, sizeof( dirname ) - 1 );
         pos = strrchr( dirname, HB_OS_PATH_DELIM_CHR );
         if( pos )
         {
            hb_strncpy( info->pattern, pos + 1, sizeof( info->pattern ) - 1 );
            *( pos + 1 ) = '\0';
         }
         else
         {
            hb_strncpy( info->pattern, dirname, sizeof( info->pattern ) - 1 );
            dirname[ 0 ] = '.';
            dirname[ 1 ] = HB_OS_PATH_DELIM_CHR;
            dirname[ 2 ] = '\0';
         }

         /* tzset(); */

         info->dir = opendir( dirname );
         hb_strncpy( info->path, dirname, sizeof( info->path ) - 1 );
      }

      if( info->dir && info->pattern[ 0 ] != '\0' )
      {
         while( ( info->entry = readdir( info->dir ) ) != NULL )
         {
            if( hb_strMatchFile( info->entry->d_name, info->pattern ) )
            {
               bFound = HB_TRUE;
               break;
            }
         }
      }

      /* Fill Harbour found file info */
      if( bFound )
      {
         hb_strncpy( dirname, info->path, sizeof( dirname ) - 1 );
         hb_strncat( dirname, info->entry->d_name, sizeof( dirname ) - 1 );
         {
            time_t ftime;
            struct tm lt;
#if defined( HB_USE_LARGEFILE64 )
            struct stat64 sStat, sStatL;
            if( lstat64( dirname, &sStat ) == 0 )
            {
               if( S_ISLNK( sStat.st_mode ) && ( ffind->attrmask & HB_FA_LINK ) == 0 )
               {
                  if( stat64( dirname, &sStatL ) == 0 )
                     memcpy( &sStat, &sStatL, sizeof( sStat ) );
                  nAttr |= HB_FA_LINK;
               }
#else
            struct stat sStat, sStatL;
            if( lstat( dirname, &sStat ) == 0 )
            {
               if( S_ISLNK( sStat.st_mode ) && ( ffind->attrmask & HB_FA_LINK ) == 0 )
               {
                  if( stat( dirname, &sStatL ) == 0 )
                     memcpy( &sStat, &sStatL, sizeof( sStat ) );
                  nAttr |= HB_FA_LINK;
               }
#endif
               hb_strncpy( ffind->szName, info->entry->d_name, sizeof( ffind->szName ) - 1 );
               ffind->size = sStat.st_size;

               raw_attr = sStat.st_mode;

               ftime = sStat.st_mtime;
#  if defined( HB_HAS_LOCALTIME_R )
               localtime_r( &ftime, &lt );
#  else
               lt = *localtime( &ftime );
#  endif

               iYear  = lt.tm_year + 1900;
               iMonth = lt.tm_mon + 1;
               iDay   = lt.tm_mday;

               iHour = lt.tm_hour;
               iMin  = lt.tm_min;
               iSec  = lt.tm_sec;

#  if defined( HB_OS_LINUX ) && \
      defined( __GLIBC__ ) && defined( __GLIBC_MINOR__ ) && \
      ( __GLIBC__ > 2 || ( __GLIBC__ == 2 && __GLIBC_MINOR__ >= 6 ) )
#     if defined( _BSD_SOURCE ) || defined( _SVID_SOURCE ) || \
         ( __GLIBC_MINOR__ >= 12 && \
           ( ( defined( _POSIX_C_SOURCE ) || _POSIX_C_SOURCE >= 200809L ) || \
             ( defined( _XOPEN_SOURCE ) || _XOPEN_SOURCE >= 700 ) ) )
               iMSec = sStat.st_mtim.tv_nsec / 1000000;
#     else
               iMSec = sStat.st_mtimensec / 1000000;
#     endif
#  endif
            }
            else
               bFound = HB_FALSE;
         }
      }
      hb_fsSetIOError( bFound, 0 );
   }

#else

   {
      int iTODO; /* TODO: for given platform */

      /* HB_SYMBOL_UNUSED( ffind ); */

      HB_SYMBOL_UNUSED( iYear );
      HB_SYMBOL_UNUSED( iMonth );
      HB_SYMBOL_UNUSED( iDay );
      HB_SYMBOL_UNUSED( iHour );
      HB_SYMBOL_UNUSED( iMin );
      HB_SYMBOL_UNUSED( iSec );
      HB_SYMBOL_UNUSED( iMSec );
      HB_SYMBOL_UNUSED( raw_attr );

      bFound = HB_FALSE;

      hb_fsSetIOError( bFound, 0 );
   }

#endif

   /* Fill common Harbour found file info */

   if( bFound )
   {
      /* Do the conversions common for all platforms */
      ffind->szName[ sizeof( ffind->szName ) - 1 ] = '\0';

#if ! defined( HB_OS_WIN )
      /* Convert from OS codepage */
      {
         char * pszFree = NULL;
         HB_SIZE nSize = sizeof( ffind->szName );
         const char * pszResult = hb_osDecodeCP( ffind->szName, &pszFree, &nSize );

         if( pszFree )
         {
            hb_strncpy( ffind->szName, pszResult, sizeof( ffind->szName ) - 1 );
            hb_xfree( pszFree );
         }
      }
#endif
      ffind->attr = hb_fsAttrFromRaw( raw_attr ) | nAttr;

      ffind->lDate = hb_dateEncode( iYear, iMonth, iDay );
      ffind->lTime = hb_timeEncode( iHour, iMin, iSec, iMSec );
      hb_dateStrPut( ffind->szDate, iYear, iMonth, iDay );
      ffind->szDate[ 8 ] = '\0';

      hb_snprintf( ffind->szTime, sizeof( ffind->szTime ), "%02d:%02d:%02d", iHour, iMin, iSec );
   }
   hb_vmLock();

   return bFound;
}

PHB_FFIND hb_fsFindFirst( const char * pszFileMask, HB_FATTR attrmask )
{
   PHB_FFIND ffind = ( PHB_FFIND ) hb_xgrabz( sizeof( HB_FFIND ) );

   /* Allocate platform dependent file find info storage */
   ffind->info = ( void * ) hb_xgrabz( sizeof( HB_FFIND_INFO ) );

   /* Store search parameters */
#if defined( HB_OS_WIN )
   ffind->pszFileMask = pszFileMask;
#else
   /* Convert to OS codepage */
   ffind->pszFileMask = hb_fsNameConv( pszFileMask, &ffind->pszFree );
#endif
   ffind->attrmask = attrmask;
   ffind->bFirst = HB_TRUE;

   /* Find first/next matching file */

   if( hb_fsFindNext( ffind ) )
      return ffind;

   /* If no file found at all, free stuff allocated so far and return NULL. */

   hb_fsFindClose( ffind );

   return NULL;
}