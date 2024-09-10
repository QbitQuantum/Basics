void CComponentInstanceManager::CloseFile(uint32_t uFileId)
{
    std::vector<CComponentBase*> componentToDelete;
    UnloadFile(uFileId, &componentToDelete);
    BEYONDENGINE_CHECK_HEAP;
    for (size_t i = 0; i < componentToDelete.size(); ++i)
    {
        CComponentBase* pComponentBase = componentToDelete[i];
        if (pComponentBase->IsInitialized())
        {
            pComponentBase->Uninitialize();
        }
        else
        {
            uint32_t uComponentId = pComponentBase->GetId();
            if (uComponentId != 0xFFFFFFFF)
            {
                CComponentInstanceManager::GetInstance()->UnregisterInstance(pComponentBase);
                CComponentInstanceManager::GetInstance()->GetIdManager()->RecycleId(uComponentId);
            }
        }
        BEYONDENGINE_CHECK_HEAP;
    }
    for (uint32_t i = 0; i < componentToDelete.size(); ++i)
    {
        BEATS_SAFE_DELETE(componentToDelete[i]);
        BEYONDENGINE_CHECK_HEAP;
    }
}