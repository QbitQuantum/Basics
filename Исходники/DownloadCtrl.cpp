//----------------------------------------------------------------------------------
// FtpPatchDownloadComplete: The ftp transfer has completed for the patch.  Check 
// the status to see if it worked.
//----------------------------------------------------------------------------------
void DownloadCtrl::FtpPatchDownloadComplete(FTPGetOp* pGetOp)
{
	CustomInfo* pCustInfo = GetCustomInfo();
	ResourceManager* pResMgr = pCustInfo->GetResourceManager();

	// Turn off the timer.
	RequestTimer(false);

	WONStatus aStatus = pGetOp->GetStatus();
	CPatchData* pPatch = pCustInfo->GetSelectedPatch();

	if (aStatus == WS_Success)
	{
		if (pPatch)
			pCustInfo->SaveDefaultSelection(pPatch->GetHostName());
		m_bPatchDownloadSucceeded = true;

		if (! m_bAborted)
		{
			// Set the progress bar to 100%.
			int nLower, nUpper;
			m_pProgressBar->GetRange(nLower, nUpper);
			UpdateProgressBar(nUpper, nUpper);
			ValidatePatch();
		}
	}
	else
	{
		if (! m_bAborted) // If the user aborted don't pop up an error telling them they aborted...
		{
			// Clear the file name (so no one tries to use it), but don't deleted it, 
			// we can resume the download later.
			pCustInfo->SetPatchFile("");

			GUIString sTitle = pResMgr->GetFinishedString(Download_DownloadError_String);
			GUIString sMsg;

			if (pPatch)
				pPatch->SetDownloadFailures(pPatch->GetDownloadFailures() + 1);

			switch (aStatus)
			{
				case WS_FTP_StatusError:
					switch (pGetOp->GetFTPStatus())
					{
						case 500:
							NamePasswordDialog(pGetOp, sTitle, pResMgr->GetFinishedString(Download_InvalidFtpUser_String));
							return;
						case 530:
							NamePasswordDialog(pGetOp, sTitle, pResMgr->GetFinishedString(Download_InvalidFtpPassword_String));
							return;
						case 550:
							MessageBox(GetWindow(), pResMgr->GetFinishedString(Download_InvalidFtpFile_String), sTitle, MD_OK);
							break;
						default:
							sMsg = pResMgr->GetFinishedString(Download_FtpError_String);
							ReplaceSubInt(sMsg, "%ERROR%", pGetOp->GetFTPStatus());
							MessageBox(GetWindow(), sMsg, sTitle, MD_OK);
					} //lint !e788
					break;
				case WS_FTP_InvalidResponse:
					MessageBox(GetWindow(), pResMgr->GetFinishedString(Download_InvalidFtpResp_String), sTitle, MD_OK);
					break;
				case WS_FTP_InvalidPasvResponse:
					MessageBox(GetWindow(), pResMgr->GetFinishedString(Download_InvalidFtpPasvResp_String), sTitle, MD_OK);
					break;
				case WS_WSAECONNREFUSED:
					MessageBox(GetWindow(), pResMgr->GetFinishedString(Download_ConnectionRefused_String), sTitle, MD_OK);
					break;
				default:
					sMsg = pResMgr->GetFinishedString(Download_UnknownFtpError_String);
					ReplaceSubString(sMsg, "%ERROR%", WONStatusToString(aStatus));
					MessageBox(GetWindow(), sMsg, sTitle, MD_OK);
			} //lint !e788

			FireBackButton();
		}
	}

	m_bPatchDownloadComplete = true;
	SendReport();
	EnableControls();
}