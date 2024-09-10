BOOL WINAPI CNdiskd::IsNdisHook(ULONG64 PtrHandler)
{
    CHAR moduleName[MAX_MODULE_NAME] = { 0 };
    BOOL boolIsHooked, boolWhitelisted = false;

    do
    {
        if (utils::getNameByOffset(PtrHandler, moduleName) == NULL)
            break;

        if (strlen(moduleName) > 0)
        {
            // Convert to lower case
            _strlwr_s(moduleName, sizeof(moduleName));
#if VVERBOSE_MODE
            DbgPrint("DEBUG: %s:%d:%s Checking integrity of module name \"%s\"\n", __FILE__, __LINE__, __FUNCTION__, moduleName);
#endif
            // Check white-listed NDIS module name
            if (CNdiskd::IsWhitelistedNdisModule(moduleName))
            {
                boolWhitelisted = true;
            }
            else
            {
                DbgPrint("DEBUG: %s:%d:%s Module name %s is not whitelisted!\n", __FILE__, __LINE__, __FUNCTION__, moduleName);
            }
        }
    } while (false);

    if (boolWhitelisted)
        boolIsHooked = false;
    else
        boolIsHooked = (PtrHandler < m_ndisBaseAddress) && (m_ndisEndAddress > PtrHandler);

#if VVERBOSE_MODE
    DbgPrint("DEBUG: %s:%d:%s %#I64x vs (%#I64x-%#I64x)\n", __FILE__, __LINE__, __FUNCTION__, PtrHandler, m_ndisBaseAddress, m_ndisEndAddress);
#endif

    if (boolIsHooked)
        return true;
    else
        return false;
}