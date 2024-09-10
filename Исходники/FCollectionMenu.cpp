int FCollectionMenu::ShowContextMenu(HWND hWndParent, const FArray<FString> &aVids)
{
	FArray<FDownload> aVideos; 
	size_t videoCount = BuildDownloadArray(aVideos, aVids); 

	if (videoCount == 0)
		return 0; 


	vidtype videoID = aVideos[0].m_Detail.m_VideoID; 
	FDownload &pVideo = aVideos[0];

	HMENU hmenu = CreatePopupMenu();
	int i = 0; 

	if (videoCount == 1 )
	{
		if (pVideo.m_dwFlags & FLAG_DOWNLOAD_FINISHED)
			_InsertMenuItem(hmenu, i++, miPlay, "Play");

		if (!pVideo.IsDownloadFinished())
		{
			if (pVideo.m_dwFlags & FLAG_DOWNLOAD_QUEUED )
				_InsertMenuItem(hmenu, i++, miStart, "Start Download");
			else
				_InsertMenuItem(hmenu, i++, miSuspend, pVideo.IsPaused() ? "Resume Download" : "Suspend Download");
		}
		else
		{
			if (pVideo.IsDownloadableStream())
				_InsertMenuItem(hmenu, i++, miStart, "Download Video");
		}

		_InsertMenuItem(hmenu, i++, miInfo, "Info...");
		_InsertMenuItem(hmenu, i++, miRename, "Rename");
	}

	_InsertMenuItem(hmenu, i++, miDelete, "Delete");
	_InsertMenuSeparator(hmenu, i++); 


	FLabels aAllLabels; 
	FLabels aCommonLabels; 
	BuildLabelsUnion(aVideos, aAllLabels, aCommonLabels); 

	HMENU hSub = CreateLabelsSubmenu(aCommonLabels, 100); 

	_InsertSubMenu(hmenu, i++, "Label", hSub); 

	if (videoCount == 1)
		_InsertMenuItem(hmenu, i++, miRevealFiles, "Reveal Files"); 

	BOOL bShowReveal = g_AppSettings.m_LogEnabled; 
#ifdef _DEBUG
	bShowReveal = TRUE; 
#endif

	if (bShowReveal)
		_InsertMenuItem(hmenu, i++, miRevealMTTI, "Reveal MTTI");

	POINT pt;
	GetCursorPos(&pt);

	int nCmd = TrackPopupMenu(hmenu, TPM_RETURNCMD, pt.x, pt.y, 0, hWndParent, NULL);

	if (nCmd < 100)
	{
		switch(nCmd)
		{
		case miPlay:
			g_MainFrame->PlayMediaFile(videoID); 
			break; 
		case miRename:
			{
				FString StrNewName = ShowRenameDlg(hWndParent, pVideo.m_Detail.m_VideoName);
				if (StrNewName != "")
				{
					pVideo.m_Detail.m_VideoName = StrNewName;
					g_Objects._DownloadManager.SaveVideoDetails(pVideo.GetVideoID(), pVideo.m_Detail); 
				}
			}
			break;

		case miSuspend:
			for (size_t k = 0; k < aVideos.GetCount(); k++)
			{
				FDownload& pVideo = aVideos[k];
				if (!pVideo.IsPaused())
					g_Objects._DownloadManager.PauseDownload(videoID); 
				else
					g_Objects._DownloadManager.ResumeDownload(videoID);
			}
			break; 
		case miDelete:
			for (size_t k = 0; k < aVideos.GetCount(); k++)
			{
				g_MainFrame->RemoveVideo(aVideos[k].m_Detail.m_VideoID);
				//g_Objects._DownloadManager.RemoveDownload(aVideos[k].m_Detail.m_VideoID); 
			}
			break; 
		case miRevealFiles:
			{
				FString StrExec;
				if (pVideo.m_Clips.GetCount() > 0)
					StrExec	= pVideo.m_Clips[0]->m_DataPath; 
				ShellExecute(NULL, "open", StrExec, "", "", SW_SHOW);
			}
			break; 
		case miRevealMTTI:
			{
				FString MTTFileName = g_Objects._DownloadManager.GetDownloadMTTI(videoID);
				ShellExecute(NULL, "open", "notepad", MTTFileName, "", SW_SHOW);
			}
			break; 
		case miStart:
			{
				IVideoPlayer* pPlayer = g_MainFrame->GetPlayer(); 
				if (pPlayer)
				{
					if (pPlayer->GetVideoID() == videoID)
						pPlayer->Stop(); 
				}
				g_Objects._DownloadManager.StartQueuedDownload(videoID); 
			}
			break; 
		case miInfo:
			{
				//Navigate to details if episodeID exists.
				//If it's a RSS Feed, GoToChannelById()
				//If it's neither, open the folder
				g_MainFrame->EpisodeDetails(videoID); 

			}
			break; 
		}
	}

	if (nCmd >= 100)
	{
		int idStr = nCmd - 100; 
		if (idStr == 0)
		{
			FString StrLabel = ShowAddLabelDlg(hWndParent, ""); 

			if (StrLabel.GetLength() > 0)
			{
				g_Objects._LabelManager.AddLabel(StrLabel);
				for (size_t k = 0; k < aVideos.GetCount(); k++)
				{
					g_Objects._DownloadManager.AddLabel(aVideos[k].m_Detail.m_VideoID, StrLabel);
				}
			}
			nCmd = 0; 
		}
		else
			if (idStr > 0 && idStr <= (int)m_zeLabels.GetCount())
			{
				FString SelectedLabel = m_zeLabels[idStr - 1];
				UINT uState = GetMenuState(hSub, idStr + 100, MF_BYCOMMAND);
				if (uState != (UINT)-1)
				{
					for (size_t k = 0; k < aVideos.GetCount(); k++)
					{
						if (uState == MF_CHECKED)
							g_Objects._DownloadManager.RemoveLabel(aVideos[k].m_Detail.m_VideoID, SelectedLabel); 
						else
							g_Objects._DownloadManager.AddLabel(aVideos[k].m_Detail.m_VideoID, SelectedLabel); 
					}
				}
			}
	}


	DestroyMenu(hSub);
	DestroyMenu(hmenu);

	return nCmd; 
}