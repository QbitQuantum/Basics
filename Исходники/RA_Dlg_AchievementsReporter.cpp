INT_PTR CALLBACK Dlg_AchievementsReporter::AchievementsReporterProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_INITDIALOG:
		{
			HWND hList = GetDlgItem( hDlg, IDC_RA_REPORTBROKENACHIEVEMENTSLIST );
			SetupColumns( hList );

			for( size_t i = 0; i < g_pActiveAchievements->NumAchievements(); ++i )
				AddAchievementToListBox( hList, &g_pActiveAchievements->GetAchievement( i ) );

			ListView_SetExtendedListViewStyle( hList, LVS_EX_CHECKBOXES | LVS_EX_HEADERDRAGDROP );
			SetDlgItemText( hDlg, IDC_RA_BROKENACH_BUGREPORTER, Widen( RAUsers::LocalUser().Username() ).c_str() );
		}
		return FALSE;

	case WM_COMMAND:
		switch( LOWORD( wParam ) )
		{
		case IDOK:
		{
			HWND hList = GetDlgItem( hDlg, IDC_RA_REPORTBROKENACHIEVEMENTSLIST );

			const bool bProblem1Sel = ( IsDlgButtonChecked( hDlg, IDC_RA_PROBLEMTYPE1 ) == BST_CHECKED );
			const bool bProblem2Sel = ( IsDlgButtonChecked( hDlg, IDC_RA_PROBLEMTYPE2 ) == BST_CHECKED );

			if( ( bProblem1Sel == false ) && ( bProblem2Sel == false ) )
			{
				MessageBox( nullptr, L"Please select a problem type.", L"Warning", MB_ICONWARNING );
				return FALSE;
			}

			int nProblemType = bProblem1Sel ? 1 : bProblem2Sel ? 2 : 0;	// 0==?
			const char* sProblemTypeNice = PROBLEM_STR[ nProblemType ];

			char sBuggedIDs[ 1024 ];
			sprintf_s( sBuggedIDs, 1024, "" );

			int nReportCount = 0;

			const size_t nListSize = ListView_GetItemCount( hList );
			for( size_t i = 0; i < nListSize; ++i )
			{
				if( ListView_GetCheckState( hList, i ) != 0 )
				{
					//	NASTY big assumption here...
					char buffer[ 1024 ];
					sprintf_s( buffer, 1024, "%d,", g_pActiveAchievements->GetAchievement( i ).ID() );
					strcat_s( sBuggedIDs, 1024, buffer );

					//ListView_GetItem( hList );	
					nReportCount++;
				}
			}

			if( nReportCount > 5 )
			{
				if( MessageBox( nullptr, L"You have over 5 achievements selected. Is this OK?", L"Warning", MB_YESNO ) == IDNO )
					return FALSE;
			}

			wchar_t sBugReportCommentWide[ 4096 ];
			GetDlgItemText( hDlg, IDC_RA_BROKENACHIEVEMENTREPORTCOMMENT, sBugReportCommentWide, 4096 );
			std::string sBugReportComment = Narrow( sBugReportCommentWide );

			char sBugReportInFull[ 8192 ];
			sprintf_s( sBugReportInFull, 8192,
					"--New Bug Report--\n"
					"\n"
					"Game: %s\n"
					"Achievement IDs: %s\n"
					"Problem: %s\n"
					"Reporter: %s\n"
					"ROM Checksum: %s\n"
					"\n"
					"Comment: %s\n"
					"\n"
					"Is this OK?",
					CoreAchievements->GameTitle().c_str(),
					sBuggedIDs,
					sProblemTypeNice,
					RAUsers::LocalUser().Username().c_str(),
					g_sCurrentROMMD5.c_str(),
					sBugReportComment.c_str() );

			if( MessageBox( nullptr, Widen( sBugReportInFull ).c_str(), L"Summary", MB_YESNO ) == IDNO )
				return FALSE;

			PostArgs args;
			args[ 'u' ] = RAUsers::LocalUser().Username();
			args[ 't' ] = RAUsers::LocalUser().Token();
			args[ 'i' ] = sBuggedIDs;
			args[ 'p' ] = std::to_string( nProblemType );
			args[ 'n' ] = sBugReportComment.c_str();
			args[ 'm' ] = g_sCurrentROMMD5;

			Document doc;
			if( RAWeb::DoBlockingRequest( RequestSubmitTicket, args, doc ) )
			{
				if( doc[ "Success" ].GetBool() )
				{
					char buffer[ 2048 ];
					sprintf_s( buffer, 2048, "Submitted OK!\n"
							"\n"
							"Thankyou for reporting that bug(s), and sorry it hasn't worked correctly.\n"
							"\n"
							"The development team will investigate this bug as soon as possible\n"
							"and we will send you a message on RetroAchievements.org\n"
							"as soon as we have a solution.\n"
							"\n"
							"Thanks again!" );

					MessageBox( hDlg, Widen( buffer ).c_str(), L"Success!", MB_OK );
					EndDialog( hDlg, TRUE );
					return TRUE;
				}
				else
				{
					char buffer[ 2048 ];
					sprintf_s( buffer, 2048,
							"Failed!\n"
							"\n"
							"Response From Server:\n"
							"\n"
							"Error code: %d", doc.GetParseError() );
					MessageBox( hDlg, Widen( buffer ).c_str(), L"Error from server!", MB_OK );
					return FALSE;
				}
			}
			else
			{
				MessageBox( hDlg,
							L"Failed!\n"
							L"\n"
							L"Cannot reach server... are you online?\n"
							L"\n",
							L"Error!", MB_OK );
				return FALSE;
			}
		}
		break;

		case IDCANCEL:
			EndDialog( hDlg, TRUE );
			return TRUE;
		}
		return FALSE;

	case WM_CLOSE:
		EndDialog( hDlg, FALSE );
		return TRUE;

	default:
		return FALSE;
	}
}