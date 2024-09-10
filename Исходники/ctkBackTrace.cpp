// --------------------------------------------------------------------------
std::string ctkBackTracePrivate::getSymbol(void* ptr) const
{
    if(ptr==0)
        return std::string();

    ctk::DebugSymInitialize();
    std::ostringstream ss;
    ss.imbue(std::locale::classic());
    ss << ptr;
    if(syms_ready)
    {
        DWORD64  dwDisplacement = 0;
        DWORD64  dwAddress = (DWORD64)ptr;

        std::vector<char> buffer(sizeof(SYMBOL_INFO) + MAX_SYM_NAME);
        PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)&buffer.front();

        pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        pSymbol->MaxNameLen = MAX_SYM_NAME;

        if (SymFromAddr(hProcess, dwAddress, &dwDisplacement, pSymbol))
        {
            ss <<": " << pSymbol->Name << std::hex << " + 0x" << dwDisplacement;
        }
        else
        {
            ss << ": ???";
        }

        std::vector<char> moduleBuffer(sizeof(IMAGEHLP_MODULE64));
        PIMAGEHLP_MODULE64 pModuleInfo = (PIMAGEHLP_MODULE64)&moduleBuffer.front();
        pModuleInfo->SizeOfStruct = sizeof(IMAGEHLP_MODULE64);
        if (SymGetModuleInfo64(hProcess, pSymbol->ModBase, pModuleInfo))
        {
            ss << " in " << pModuleInfo->LoadedImageName;
        }
    }
    return ss.str();
}