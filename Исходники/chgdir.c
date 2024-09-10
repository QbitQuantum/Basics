/* This function handles the WM_COMMAND message.
 */
void FASTCALL ChangeDir_OnCommand( HWND hwnd, int id, HWND hwndCtl, UINT codeNotify )
{
   static BOOL fListHasFocus = FALSE;

   switch( id )
      {
      case IDD_NETWORK:
         if( WNetConnectionDialog( hwnd, WNTYPE_DRIVE ) == WN_SUCCESS )
            {
#ifndef WIN32
            HINSTANCE hinstNetDriver;
            int iDrive;

            hinstNetDriver = (HINSTANCE)WNetGetCaps( 0xFFFF );
            if( hinstNetDriver )
               {
               LPWNETGETLASTCONNECTION lpDialogAPI;

               lpDialogAPI = (LPWNETGETLASTCONNECTION)GetProcAddress( hinstNetDriver, (LPSTR)ORD_WNETGETLASTCONNECTION);
               if( lpDialogAPI != NULL )
                  if( lpDialogAPI( WNTYPE_DRIVE, &iDrive ) == WN_SUCCESS )
                     {
                     ++iDrive;
                     DriveListInitialize( GetDlgItem( hwnd, IDD_DRIVELIST ), GetDlgItem( hwnd, IDD_TEMPLIST ), iDrive );
//                   SendDlgCommand( hwnd, IDD_DRIVELIST, CBN_SELCHANGE );
                     }
               }
#endif
            }
         break;

      case IDD_DIRECTORYLIST:
         if( codeNotify == LBN_SETFOCUS )
            fListHasFocus = TRUE;
         else if( codeNotify == LBN_KILLFOCUS )
            fListHasFocus = FALSE;
         else if( codeNotify == LBN_DBLCLK ) {
            UINT i;
            DWORD dw;
            char szDir[_MAX_PATH];
            char szCurDir[_MAX_PATH];
            LPSTR lpsz;

            /* On double-click, change directory and reinit the
             * listbox.  But all we stored in the string was
             * the directory's single name, so we use the bitmap
             * type to tell if we're below the current directory
             * (in which case we just chdir to our name) or above
             * (in which case we prepend "..\"'s as necessary.
             */
            i = ListBox_GetCurSel( hwndCtl );
            dw = ListBox_GetItemData( hwndCtl, i );

            /* If out bitmap is IDB_FOLDERCLOSED or the root,
             * then just .  If we're IDB_FOLDEROPENSELECT,
             * don't do anything.  If we're IDB_FOLDEROPEN then
             * we get the full current path and truncate it
             * after the directory to which we're switching.
             */
            if( IDB_FOLDEROPENSELECT == HIWORD( dw ) )
               {
               id = IDOK;
               goto CloseDialog;
               }

            /* Get get the directory for sub-directory changes. */
            ListBox_GetText( hwndCtl, i, szCurDir );
            if( IDB_FOLDEROPEN == HIWORD( dw ) && 0 != i )
               {
               /* Get the current path and find us in this path */
               GetWindowText( hwndCtl, szDir, sizeof( szDir ) );
               lpsz=_fstrstr( szDir, szCurDir );

               /* Null terminate right after us. */
               *( lpsz + strlen( szCurDir ) ) = '\0';

               /* Get this new directory in the right place */
               strcpy( szCurDir, szDir );
               }
            /* chdir has a nice way of validating for us. */
            if( 0 == _chdir( szCurDir ) )
               {
               /* Get the new full path. */
               Amdir_GetCurrentDirectory( szCurDir, _MAX_PATH );
               DirectoryListInitialize( hwndCtl, GetDlgItem( hwnd, IDD_TEMPLIST ), szCurDir );
               //???? YH18/04/96 AnsiLower( szCurDir );
               SetDlgItemText( hwnd, IDD_EDIT, szCurDir );
               }
            }
         break;

      case IDD_DRIVELIST:
         if( codeNotify == CBN_SELCHANGE )
            {
            UINT i, iCurDrive;
            char szCurDir[ _MAX_PATH ];
            char szDrive[ _MAX_PATH ]; /* Enough for drive:volume */

            /* Get the first letter in the current selection */
            i = ComboBox_GetCurSel( hwndCtl );
            ComboBox_GetLBText( hwndCtl, i, szDrive );
            iCurDrive = _getdrive();  /* Save in case of restore */

            /* Attempt to set the drive and get the current
             * directory on it.  Both must work for the change
             * to be certain.  If we are certain, reinitialize
             * the directories.  Note that we depend on drives
             * stored as lower case in the combobox.
             */
            if( _chdrive( (int)( szDrive[ 0 ] - 'a' + 1 ) ) == 0 && ( Amdir_GetCurrentDirectory( szCurDir, _MAX_PATH ) != 0 ) )
               {
               DirectoryListInitialize( GetDlgItem( hwnd, IDD_DIRECTORYLIST ), GetDlgItem( hwnd, IDD_TEMPLIST ), szCurDir );

               /* Insure that the root is visible (UI guideline) */
               SendDlgItemMessage( hwnd, IDD_DIRECTORYLIST, LB_SETTOPINDEX, 0, 0L );
               AnsiLower( szCurDir );
               SetDlgItemText( hwnd, IDD_EDIT, szCurDir );
               break;
               }

            /* Changing drives failed so restore drive and selection */
            _chdrive( (int)iCurDrive );
            wsprintf( szDrive, "%c:", (char)( iCurDrive + 'a' - 1 ) );
            ComboBox_SelectString( hwndCtl, -1, szDrive );
            }
         break;

      case IDD_EDIT:
         if( codeNotify == EN_UPDATE )
            EnableControl( hwnd, IDOK, Edit_GetTextLength( hwndCtl ) > 0 );
         break;

      case IDOK: {
         LPCHGDIR lpChgDir;

         if( fListHasFocus )
            {
//          PostDlgCommand( hwnd, IDD_DIRECTORYLIST, LBN_DBLCLK );
            break;
            }
CloseDialog:
         lpChgDir = (LPCHGDIR)GetWindowLong( hwnd, DWL_USER );
         Edit_GetText( GetDlgItem( hwnd, IDD_EDIT ), lpChgDir->szPath, sizeof( lpChgDir->szPath ) );
         }

      case IDCANCEL: {
         register int i;

         for( i = IDB_DRIVEMIN; i <= IDB_DRIVEMAX; i++ )
            DeleteBitmap( rghBmpDrives[ i - IDB_DRIVEMIN ] );
         for( i = IDB_FOLDERMIN; i <= IDB_FOLDERMAX; i++ )
            DeleteBitmap( rghBmpFolders[ i - IDB_FOLDERMIN ] );
         fBitmapsLoaded = FALSE;
         _chdrive( iCurDrive );
         _chdir( szDefDir );
         EndDialog( hwnd, id == IDOK );
         break;
         }
      }
}