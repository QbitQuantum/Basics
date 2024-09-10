void QueueCoordinator::AddNZBFileToQueue(NZBFile* pNZBFile, NZBInfo* pUrlInfo, bool bAddFirst)
{
    debug("Adding NZBFile to queue");

    NZBInfo* pNZBInfo = pNZBFile->GetNZBInfo();

    DownloadQueue* pDownloadQueue = DownloadQueue::Lock();

    DownloadQueue::Aspect foundAspect = { DownloadQueue::eaNzbFound, pDownloadQueue, pNZBInfo, NULL };
    pDownloadQueue->Notify(&foundAspect);

    NZBInfo::EDeleteStatus eDeleteStatus = pNZBInfo->GetDeleteStatus();

    if (eDeleteStatus != NZBInfo::dsNone)
    {
        bool bAllPaused = !pNZBInfo->GetFileList()->empty();
        for (FileList::iterator it = pNZBInfo->GetFileList()->begin(); it != pNZBInfo->GetFileList()->end(); it++)
        {
            FileInfo* pFileInfo = *it;
            bAllPaused &= pFileInfo->GetPaused();
            if (g_pOptions->GetSaveQueue() && g_pOptions->GetServerMode())
            {
                g_pDiskState->DiscardFile(pFileInfo, true, false, false);
            }
        }
        pNZBInfo->SetDeletePaused(bAllPaused);
    }

    if (eDeleteStatus != NZBInfo::dsManual)
    {
        // NZBInfo will be added either to queue or to history as duplicate
        // and therefore can be detached from NZBFile.
        pNZBFile->DetachNZBInfo();
    }

    if (eDeleteStatus == NZBInfo::dsNone)
    {
        if (g_pOptions->GetDupeCheck() && pNZBInfo->GetDupeMode() != dmForce)
        {
            CheckDupeFileInfos(pNZBInfo);
        }

        if (pUrlInfo)
        {
            // insert at the URL position
            for (NZBList::iterator it = pDownloadQueue->GetQueue()->begin(); it != pDownloadQueue->GetQueue()->end(); it++)
            {
                NZBInfo* pPosNzbInfo = *it;
                if (pPosNzbInfo == pUrlInfo)
                {
                    pDownloadQueue->GetQueue()->insert(it, pNZBInfo);
                    break;
                }
            }
        }
        else if (bAddFirst)
        {
            pDownloadQueue->GetQueue()->push_front(pNZBInfo);
        }
        else
        {
            pDownloadQueue->GetQueue()->push_back(pNZBInfo);
        }
    }

    if (pUrlInfo)
    {
        pNZBInfo->SetID(pUrlInfo->GetID());
        pDownloadQueue->GetQueue()->Remove(pUrlInfo);
        delete pUrlInfo;
    }

    if (eDeleteStatus == NZBInfo::dsNone)
    {
        pNZBInfo->PrintMessage(Message::mkInfo, "Collection %s added to queue", pNZBInfo->GetName());
    }

    if (eDeleteStatus != NZBInfo::dsManual)
    {
        DownloadQueue::Aspect addedAspect = { DownloadQueue::eaNzbAdded, pDownloadQueue, pNZBInfo, NULL };
        pDownloadQueue->Notify(&addedAspect);
    }

    pDownloadQueue->Save();

    DownloadQueue::Unlock();
}