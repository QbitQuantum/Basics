std::shared_ptr<CClientIFP> CIFPEngine::EngineLoadIFP(CResource* pResource, CClientManager* pManager, const SString& strFile, bool bIsRawData, const SString& strBlockName)
{
    // Grab the resource root entity
    CClientEntity*     pRoot = pResource->GetResourceIFPRoot();
    const unsigned int u32BlockNameHash = HashString(strBlockName.ToLower());

    // Check whether the IFP blockname exists or not
    if (g_pClientGame->GetIFPPointerFromMap(u32BlockNameHash) == nullptr)
    {
        // Create a IFP element
        std::shared_ptr<CClientIFP> pIFP(new CClientIFP(pManager, INVALID_ELEMENT_ID));

        // Try to load the IFP file
        if (pIFP->LoadIFP(strFile, bIsRawData, strBlockName))
        {
            // We can use the map to retrieve correct IFP by block name later
            g_pClientGame->InsertIFPPointerToMap(u32BlockNameHash, pIFP);

            // Success loading the file. Set parent to IFP root
            pIFP->SetParent(pRoot);
            return pIFP;
        }
    }
    return nullptr;
}