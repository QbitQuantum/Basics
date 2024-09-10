void CBackgroundInfoLoader::Run()
{
    try
    {
        if (m_vecItems.size() > 0)
        {
            OnLoaderStart();

            for (std::vector<CFileItemPtr>::const_iterator iter = m_vecItems.begin(); iter != m_vecItems.end(); ++iter)
            {
                CFileItemPtr pItem = *iter;

                // Ask the callback if we should abort
                if ((m_pProgressCallback && m_pProgressCallback->Abort()) || m_bStop)
                    break;

                try
                {
                    if (LoadItem(pItem.get()) && m_pObserver)
                        m_pObserver->OnItemLoaded(pItem.get());
                }
                catch (...)
                {
                    CLog::Log(LOGERROR, "CBackgroundInfoLoader::LoadItem - Unhandled exception for item %s", CURL::GetRedacted(pItem->GetPath()).c_str());
                }
            }
        }

        OnLoaderFinish();
        m_bIsLoading = false;
    }
    catch (...)
    {
        m_bIsLoading = false;
        CLog::Log(LOGERROR, "%s - Unhandled exception", __FUNCTION__);
    }
}