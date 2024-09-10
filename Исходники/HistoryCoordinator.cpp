void HistoryCoordinator::HistoryReturn(DownloadQueue* pDownloadQueue, HistoryList::iterator itHistory, HistoryInfo* pHistoryInfo, bool bReprocess)
{
	char szNiceName[1024];
	pHistoryInfo->GetName(szNiceName, 1024);
	debug("Returning %s from history back to download queue", szNiceName);
	NZBInfo* pNZBInfo = NULL;

	if (bReprocess && pHistoryInfo->GetKind() != HistoryInfo::hkNzb)
	{
		error("Could not restart postprocessing for %s: history item has wrong type", szNiceName);
		return;
	}

	if (pHistoryInfo->GetKind() == HistoryInfo::hkNzb)
	{
		pNZBInfo = pHistoryInfo->GetNZBInfo();

		// unpark files
		bool bUnparked = false;
		for (FileList::iterator it = pNZBInfo->GetFileList()->begin(); it != pNZBInfo->GetFileList()->end(); it++)
		{
			FileInfo* pFileInfo = *it;
			detail("Unpark file %s", pFileInfo->GetFilename());
			bUnparked = true;
		}

		if (!(bUnparked || bReprocess))
		{
			warn("Could not return %s back from history to download queue: history item does not have any files left for download", szNiceName);
			return;
		}

		pDownloadQueue->GetQueue()->push_front(pNZBInfo);
		pHistoryInfo->DiscardNZBInfo();

		// reset postprocessing status variables
		pNZBInfo->SetParCleanup(false);
		if (!pNZBInfo->GetUnpackCleanedUpDisk())
		{
			pNZBInfo->SetUnpackStatus(NZBInfo::usNone);
			pNZBInfo->SetCleanupStatus(NZBInfo::csNone);
			pNZBInfo->SetRenameStatus(NZBInfo::rsNone);
			pNZBInfo->SetPostTotalSec(pNZBInfo->GetPostTotalSec() - pNZBInfo->GetUnpackSec());
			pNZBInfo->SetUnpackSec(0);

			if (ParParser::FindMainPars(pNZBInfo->GetDestDir(), NULL))
			{
				pNZBInfo->SetParStatus(NZBInfo::psNone);
				pNZBInfo->SetPostTotalSec(pNZBInfo->GetPostTotalSec() - pNZBInfo->GetParSec());
				pNZBInfo->SetParSec(0);
				pNZBInfo->SetRepairSec(0);
				pNZBInfo->SetParFull(false);
			}
		}
		pNZBInfo->SetDeleteStatus(NZBInfo::dsNone);
		pNZBInfo->SetDeletePaused(false);
		pNZBInfo->SetMarkStatus(NZBInfo::ksNone);
		pNZBInfo->GetScriptStatuses()->Clear();
		pNZBInfo->SetParkedFileCount(0);
		if (pNZBInfo->GetMoveStatus() == NZBInfo::msFailure)
		{
			pNZBInfo->SetMoveStatus(NZBInfo::msNone);
		}
		pNZBInfo->SetReprocess(bReprocess);
	}

	if (pHistoryInfo->GetKind() == HistoryInfo::hkUrl)
	{
		pNZBInfo = pHistoryInfo->GetNZBInfo();
		pHistoryInfo->DiscardNZBInfo();
		pNZBInfo->SetUrlStatus(NZBInfo::lsNone);
		pNZBInfo->SetDeleteStatus(NZBInfo::dsNone);
		pDownloadQueue->GetQueue()->push_front(pNZBInfo);
	}

	pDownloadQueue->GetHistory()->erase(itHistory);
	// the object "pHistoryInfo" is released few lines later, after the call to "NZBDownloaded"
	pNZBInfo->PrintMessage(Message::mkInfo, "%s returned from history back to download queue", szNiceName);

	if (bReprocess)
	{
		// start postprocessing
		debug("Restarting postprocessing for %s", szNiceName);
		g_pPrePostProcessor->NZBDownloaded(pDownloadQueue, pNZBInfo);
	}

	delete pHistoryInfo;
}