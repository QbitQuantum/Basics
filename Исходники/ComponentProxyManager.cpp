void CComponentProxyManager::CloseFile(uint32_t uFileId)
{
    ReSaveFreshFile(); // the file we are about to close may be in the fresh file list, so we always try to save it before it is closed.
    // TODO: Lock id manager, since we will recycle id in component's un-initialize function.
    // However, we don't want that, so we lock the id manager for now.
    m_pIdManager->Lock();
    std::vector<CComponentBase*> unloadProxyList;
    UnloadFile(uFileId, &unloadProxyList);
    std::vector<CComponentBase*> componentToDelete;
    for (size_t i = 0; i < unloadProxyList.size(); ++i)
    {
        CComponentProxy* pProxy = static_cast<CComponentProxy*>(unloadProxyList[i]);
        componentToDelete.push_back(pProxy->GetHostComponent());
    }
    for (uint32_t i = 0; i < componentToDelete.size(); ++i)
    {
        CComponentBase* pComponentBase = componentToDelete[i];
        BEATS_ASSERT(!pComponentBase->IsLoaded());
        if (pComponentBase->IsInitialized())
        {
            pComponentBase->Uninitialize();
        }
    }
    for (uint32_t i = 0; i < componentToDelete.size(); ++i)
    {
        CComponentBase* pComponentBase = componentToDelete[i];
        BEATS_ASSERT(!pComponentBase->IsInitialized());
        BEATS_SAFE_DELETE(pComponentBase);
    }
    if (GetCurrentViewFileId() == uFileId)
    {
        SetCurrentViewFileId(0xFFFFFFFF);
    }
    if (GetCurrLoadFileId() == uFileId)
    {
        SetCurrLoadFileId(0xFFFFFFFF);
    }
    m_pIdManager->UnLock();
}