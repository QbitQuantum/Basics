/*
 * Find Symbol in symbol table
 * To use this, this source must be compiled in debug mode.
 * No solution without /DEBUG option yet.
 */
ACP_EXPORT acp_rc_t acpSymFind(acp_sym_table_t *aSymTable,
                               acp_sym_info_t  *aSymInfo,
                               void            *aAddr)
{
    IMAGEHLP_MODULE64 *sModule = &aSymTable->mModule;
    SYMBOL_INFO       *sSymbol = (SYMBOL_INFO *)aSymTable->mSymbolBuffer;
    BOOL               sRet;

    sRet = SymGetModuleInfo64(GetCurrentProcess(), (DWORD64)aAddr, sModule);

    if (sRet == 0)
    {
        acpStrSetConstCString(&aSymInfo->mFileName, NULL);
        aSymInfo->mFileAddr = NULL;
    }
    else
    {
        acpStrSetConstCString(&aSymInfo->mFileName, sModule->LoadedImageName);
        aSymInfo->mFileAddr = (void *)(acp_ulong_t)sModule->BaseOfImage;
    }

    sRet = SymFromAddr(GetCurrentProcess(), (DWORD64)aAddr, NULL, sSymbol);

    if (sRet == 0)
    {
        acpStrSetConstCString(&aSymInfo->mFuncName, NULL);
        aSymInfo->mFuncAddr = NULL;
    }
    else
    {
        acpStrSetConstCString(&aSymInfo->mFuncName, sSymbol->Name);
        aSymInfo->mFuncAddr = (void *)(acp_ulong_t)sSymbol->Address;
    }

    return ACP_RC_SUCCESS;
}