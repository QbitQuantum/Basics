extern "C" HRESULT CALLBACK DebugExtensionInitialize(PULONG Version, PULONG Flags)
{
    HRESULT hRes=E_FAIL;

    if(bInitialized)
    {
        return S_OK;
    }

    //
    // Initialize the version information
    //
    *Version=DEBUG_EXTENSION_VERSION(1, 0);
    *Flags=0;

    //
    // Initialize required COM interface pointers
    //
    if(FAILED(hRes=DebugCreate(__uuidof(IDebugClient), 
                               (void**) &pDebugClient)))
    {
        return hRes;
    }

    if(FAILED(hRes=pDebugClient->QueryInterface(__uuidof(IDebugControl), (void**) &pDebugControl)))
    {
        ReleaseComPointers();
        return hRes;
    }

    //
    // Initialize WinDbg extension data
    //
    ExtensionApis.nSize=sizeof(ExtensionApis);
    hRes=pDebugControl->GetWindbgExtensionApis64(&ExtensionApis);

    if(FAILED((hRes=pDebugClient->QueryInterface(__uuidof(IDebugDataSpaces), (void**) &pDataSpaces))))
    {
        dprintf( "Failed to get required COM interface\n");
        ReleaseComPointers();
        return hRes;
    }
       
    if(FAILED(hRes=pDebugClient->QueryInterface(__uuidof(IDebugSymbols), (void**) &pSymbols)))
    {
        dprintf( "Failed to get required COM interface\n");
        ReleaseComPointers();
        return hRes;
    }

    if(FAILED(hRes=pDebugClient->QueryInterface(__uuidof(IDebugSymbols3), (void**) &pSymbols3)))
    {
        dprintf( "Failed to get required COM interface\n");
        ReleaseComPointers();        
        return hRes;
    }

    //
    // Initialize type information
    //
    if(FAILED(hRes=pSymbols->GetModuleByModuleName("11bstree", 
                                                   0, 
                                                   NULL, 
                                                   &pBase)))
    {
        dprintf("Failed to get module information for bstree.exe\n");
        ReleaseComPointers();        
        return hRes;
    }
    if(FAILED(hRes=pSymbols3->GetTypeId(pBase, 
                                        "CBinaryTree::_TreeNode",    
                                        &pNodeIndex)))
    {
        dprintf("Failed to get type id\n");
        ReleaseComPointers();        
        return hRes;
    }
    if(FAILED(hRes=pSymbols->GetTypeSize(pBase, 
                                         pNodeIndex, 
                                         &pSize)))
    {
        dprintf("Failed to get type size\n");
        ReleaseComPointers();        
        return hRes;
    }

    if(FAILED(hRes=pSymbols->GetFieldOffset(pBase, 
                                            pNodeIndex, 
                                            "pLeftChild", 
                                            &ulLeftOffset)))
    {
        dprintf("Failed to get left child offset\n");			
        ReleaseComPointers();        
        return hRes;
    }

    if(FAILED(hRes=pSymbols->GetFieldOffset(pBase, 
                                            pNodeIndex, 
                                            "pRightChild", 
                                            &ulRightOffset)))
    {
        dprintf("Failed to get right child offset\n");			
        ReleaseComPointers();        
        return hRes;
    }

    if(FAILED(hRes=pSymbols->GetFieldOffset(pBase, 
                                            pNodeIndex, 
                                            "data", 
                                            &ulDataOffset)))
    {
        dprintf("Failed to get data offset\n");			
        ReleaseComPointers();        
        return hRes;
    }

    bInitialized=TRUE;
    hRes=S_OK;

    return hRes;
}