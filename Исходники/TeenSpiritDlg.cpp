void CTeenSpiritDlg::OnTimer(UINT nIDEvent)
{
	PrgAPI* pAPI = PRGAPI();
	SQLManager* pSM = pAPI->GetSQLManager();
	switch (nIDEvent)
	{
	case TMR_InitialDelay:
		SetTimer(TMR_PlayerMonitor, PLAYERMONITOR_TIMER_DELAY, NULL);
		pAPI->GetTrayToolTipDlg();
		KillTimer(nIDEvent);
		{
			TracksFilter tf;
			if (pSM->GetTrackCount(tf) == 0)
			{
				TCHAR url[1000];
				pAPI->GetSiteURL(url, 1000, PrgAPI::SA_Help, _T("emptycollection"));
				CMessageDlg dlg(this);
				dlg.SetText(CMessageDlg::TT_Title, pAPI->GetString(IDS_EMPTYCOLLECTION_TITLE));
				dlg.SetText(CMessageDlg::TT_SubTitle, pAPI->GetString(IDS_EMPTYCOLLECTION_DETAIL));
				dlg.SetHelpLink(pAPI->GetString(IDS_HELP_S), url);
				dlg.SetText(CMessageDlg::TT_ButtonRight, pAPI->GetString(IDS_OK));
				switch (dlg.DoModal())
				{
				case CMessageDlg::RES_Close:
					pAPI->GoToSiteURL(PrgAPI::SA_Help, _T("emptycollection"));
					break;
				case CMessageDlg::RES_Right:
					pAPI->GetActionManager()->ShowAddNewCollectionDlg(this);
					UpdateWindow();
					break;
				}
			}
			if (pAPI->GetOption(OPT_GEN_UseNativeOnlineServices) == -1)
			{
				CMessageDlg dlg(this);
				
				dlg.SetText(CMessageDlg::TT_Title, pAPI->GetString(IDS_OPTIONS));
				dlg.SetText(CMessageDlg::TT_SubTitle, pAPI->GetString(IDS_CONFIRMATION));
				TCHAR bf[1000];
				_sntprintf(bf, 1000, _T("%s (beta)"), pAPI->GetString(IDS_TSONLINESERVICES));
				dlg.SetText(CMessageDlg::TT_CheckBox, bf);
				pAPI->GetSiteURL(bf, 1000, PrgAPI::SA_Navigate, _T("onlineservices-about"));
				dlg.SetHelpLink(pAPI->GetString(IDS_HELP_S), bf);
				dlg.SetCheck(TRUE);
				dlg.SetText(CMessageDlg::TT_ButtonRight, pAPI->GetString(IDS_OK));
				if (dlg.DoModal() != CMessageDlg::RES_Close)
					pAPI->SetOption(OPT_GEN_UseNativeOnlineServices, dlg.IsChecked() ? 1 : 0);
			}
			MediaPlayer* pPlayer = PRGAPI()->GetMediaPlayer();
			m_playerBar.SetMediaPlayer(pPlayer);
			if (pAPI->GetOption(OPT_MINIPLR_ShowAtStartup) != 0)
				pAPI->GetMiniPlayerDlg(TRUE)->Show();
		}
		break;
	case TMR_CheckNewVersion:
		KillTimer(nIDEvent);
		if (pAPI->GetOption(OPT_GEN_CheckForUpdates))
		{
			PrgAPI* pAPI = PRGAPI();
			SYSTEMTIME st;
			GetLocalTime(&st);
			DOUBLE thisDay;
			SystemTimeToVariantTime(&st, &thisDay);
			if (INT(thisDay) - pAPI->GetOption(OPT_GEN_CheckLastCheck) >= pAPI->GetOption(OPT_GEN_DaysBetweenCheck))
			{
				pAPI->SetOption(OPT_GEN_CheckLastCheck, INT(thisDay));
				AfxBeginThread(&NewVersionCheckThreadST, (void*)this ,0 ,0 ,0);
			}
		}
		break;
	case TMR_AutoUpdateDB:
		KillTimer(nIDEvent);
		if (pAPI->GetOption(OPT_GEN_AutoUpdateDB) != 0)
			pAPI->GetCollectionManager()->RefreshLocalCollections(TRUE, FALSE, TRUE);
		break;
	//case COLLECTIONREFRESH_TIMER:
	//	{
	//		PrgAPI* pAPI = PRGAPI();
	//		CollectionManager* pCM = pAPI->GetCollectionManager();
	//		if (pCM->GetState() == CollectionManager::S_Working)
	//		{
	//			const CollectionUpdateJob::Progress prog = pCM->GetProgress();
	//			INT curVal = prog.curPos;
	//			if (curVal - m_lastUpdateActionsPerformed > 100)
	//			{
	//				m_lastUpdateActionsPerformed = curVal;
	//			}
	//		}
	//		else
	//			KillTimer(nIDEvent);
	//	}
	//	break;
	case TMR_HeartBeat://Used by BaseDirector for Send/Post Messages
		pAPI->GetStateManager()->HeartBeat();
		break;
	case TMR_AppMonitor://Used for History Tracking, Download Status Update etc
		pAPI->Monitor();
		break;
	case TMR_PlayerMonitor:
		{
			MediaPlayer::Changes changes = pAPI->GetMediaPlayer()->GetChanges();
			if (changes.tickPlayList >= m_monitorPlayerTick)
				pAPI->GetStateManager()->SendMessage(SM_PlayListChanged);
			if (changes.tickMediaChanged >= m_monitorPlayerTick && m_monitorPlayerTick > 0)
				pAPI->GetStateManager()->SendMessage(SM_MediaChanged);
			m_monitorPlayerTick = GetTickCount();
		}
		break;
	case TMR_ShowTrayTooltipOnMouseMove:
		{
			KillTimer(nIDEvent);
			CPoint ptCurPos;
			GetCursorPos(&ptCurPos);
			if (ptCurPos == m_ptTrayCursorPos)
			{
				pAPI->GetTrayToolTipDlg()->OnMouseOverTray(ptCurPos);
			}
		}
		break;
	default:
		CDialog::OnTimer(nIDEvent);
		break;
	}

}