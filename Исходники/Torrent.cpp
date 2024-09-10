void CTorrent::OnFileHashed()
{
    CFile* pFile = GetFile();
    ASSERT(m_TorrentInfo);
    if(m_TorrentInfo->IsEmpty()) // are we making a torrent
    {
        QStringList Shared = theCore->Cfg()->GetStringList("Content/Shared");
        Shared.append(theCore->GetIncomingDir());
        Shared.append(theCore->GetTempDir());

        QList<CTorrentInfo::SFileInfo> Files;
        if(CJoinedPartMap* pParts = qobject_cast<CJoinedPartMap*>(pFile->GetPartMap()))
        {
            QMap<uint64, SPartMapLink*> Links = pParts->GetJoints();
            for(QMap<uint64, SPartMapLink*>::iterator I = Links.end(); I != Links.begin();)
            {
                SPartMapLink* pLink = *(--I);

                CFile* pSubFile = pFile->GetList()->GetFileByID(pLink->ID);
                if(!pSubFile)
                {
                    LogLine(LOG_DEBUG | LOG_ERROR, tr("A sub file of %1 has been being removed befoure the torrent was created").arg(pFile->GetFileName()));
                    pFile->TorrentHashed(this, false);
                    return;
                }

                CTorrentInfo::SFileInfo File;
                QString Root;
                QStringList Path = GetRelativeSharedPath(pSubFile->GetFilePath(), Shared, Root).split("/", QString::SkipEmptyParts);
                if(!Path.isEmpty())
                {
                    if(Path.count() > 1)
                        Path.removeFirst();
                    File.FileName = Path.takeLast();
                    File.FilePath = Path;
                }
                else
                    File.FileName = "unknown";
                File.Length = pSubFile->GetFileSize();
                Files.append(File);
            }
        }

        if(CFileHashTree* pHashTree = qobject_cast<CFileHashTree*>(m_pHash.data()))
            m_TorrentInfo->MakeMetadata(Files, pHashTree->GetPartSize(), QList<QByteArray>(), pHashTree->GetRootHash());
        else if(CFileHashSet* pHashSet = qobject_cast<CFileHashSet*>(m_pHash.data()))
            m_TorrentInfo->MakeMetadata(Files, pHashSet->GetPartSize(), pHashSet->GetHashSet());
        else {
            ASSERT(0);
        }

        if(!pFile->IsPending())
            SaveTorrentToFile();

        m_pHash->SetHash(m_TorrentInfo->GetInfoHash());
        theCore->m_TorrentManager->RegisterInfoHash(m_TorrentInfo->GetInfoHash());

        pFile->TorrentHashed(this, true);
    }
    else // we are importing a torrent
    {
        bool bMatch = false;

        if(CFileHashTree* pHashTree = qobject_cast<CFileHashTree*>(m_pHash.data()))
            bMatch = m_TorrentInfo->GetRootHash() == pHashTree->GetRootHash();
        else if(CFileHashSet* pHashSet = qobject_cast<CFileHashSet*>(m_pHash.data()))
            bMatch = m_TorrentInfo->GetPieceHashes() == pHashSet->GetHashSet();
        else {
            ASSERT(0);
        }

        if(bMatch)
        {
            if(!pFile->IsPending())
                SaveTorrentToFile();

            m_pHash->SetHash(m_TorrentInfo->GetInfoHash());
            theCore->m_TorrentManager->RegisterInfoHash(m_TorrentInfo->GetInfoHash());
        }

        pFile->TorrentHashed(this, bMatch);
    }
}