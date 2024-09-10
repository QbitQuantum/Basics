int CALLBACK AssertDialogProc(
  HWND hDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
	switch( uMsg )
	{
		case WM_INITDIALOG:
		{
#ifdef TCHAR_IS_WCHAR
			SetDlgItemTextW( hDlg, IDC_ASSERT_MSG_CTRL, g_Info.m_pExpression );
			SetDlgItemTextW( hDlg, IDC_FILENAME_CONTROL, g_Info.m_pFilename );
#else
			SetDlgItemText( hDlg, IDC_ASSERT_MSG_CTRL, g_Info.m_pExpression );
			SetDlgItemText( hDlg, IDC_FILENAME_CONTROL, g_Info.m_pFilename );
#endif
			SetDlgItemInt( hDlg, IDC_LINE_CONTROL, g_Info.m_iLine, false );
			SetDlgItemInt( hDlg, IDC_IGNORE_NUMLINES, g_iLastLineRange, false );
			SetDlgItemInt( hDlg, IDC_IGNORE_NUMTIMES, g_nLastIgnoreNumTimes, false );
		
			// Center the dialog.
			RECT rcDlg, rcDesktop;
			GetWindowRect( hDlg, &rcDlg );
			GetWindowRect( GetDesktopWindow(), &rcDesktop );
			SetWindowPos( 
				hDlg, 
				HWND_TOP, 
				((rcDesktop.right-rcDesktop.left) - (rcDlg.right-rcDlg.left)) / 2,
				((rcDesktop.bottom-rcDesktop.top) - (rcDlg.bottom-rcDlg.top)) / 2,
				0,
				0,
				SWP_NOSIZE );
		}
		return true;

		case WM_COMMAND:
		{
			switch( LOWORD( wParam ) )
			{
				case IDC_IGNORE_FILE:
				{
					IgnoreAssertsInCurrentFile();
					EndDialog( hDlg, 0 );
					return true;
				}

				// Ignore this assert N times.
				case IDC_IGNORE_THIS:
				{
					BOOL bTranslated = false;
					UINT value = GetDlgItemInt( hDlg, IDC_IGNORE_NUMTIMES, &bTranslated, false );
					if ( bTranslated && value > 1 )
					{
						CAssertDisable *pDisable = IgnoreAssertsNearby( 0 );
						pDisable->m_nIgnoreTimes = value - 1;
						g_nLastIgnoreNumTimes = value;
					}

					EndDialog( hDlg, 0 );
					return true;
				}

				// Always ignore this assert.
				case IDC_IGNORE_ALWAYS:
				{
					IgnoreAssertsNearby( 0 );
					EndDialog( hDlg, 0 );
					return true;
				}
				
				case IDC_IGNORE_NEARBY:
				{
					BOOL bTranslated = false;
					UINT value = GetDlgItemInt( hDlg, IDC_IGNORE_NUMLINES, &bTranslated, false );
					if ( !bTranslated || value < 1 )
						return true;

					IgnoreAssertsNearby( value );
					EndDialog( hDlg, 0 );
					return true;
				}

				case IDC_IGNORE_ALL:
				{
					g_bAssertsEnabled = false;
					EndDialog( hDlg, 0 );
					return true;
				}

				case IDC_BREAK:
				{
					g_bBreak = true;
					EndDialog( hDlg, 0 );
					return true;
				}
			}

			case WM_KEYDOWN:
			{
				// Escape?
				if ( wParam == 2 )
				{
					// Ignore this assert.
					EndDialog( hDlg, 0 );
					return true;
				}
			}
					
		}
		return true;
	}

	return FALSE;
}