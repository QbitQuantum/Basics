void AbstractBTGenerator::LoadSymbols()
{
    TModulesMap modules = m_process.GetModules();
    for (TModulesMap::iterator i = modules.begin(); i != modules.end(); i++)
    {
        MODULEINFO modInfo;
        ZeroMemory(&modInfo, sizeof(modInfo));

        QString strModule = i.key();

        GetModuleInformation(m_process.GetHandle(), i.value(), &modInfo, sizeof(modInfo));
        SymLoadModuleEx(
            m_process.GetHandle(),
            NULL,
            (CHAR*) i.key().toLatin1().constData(),
            (CHAR*) i.key().toLatin1().constData(),
            (DWORD64) modInfo.lpBaseOfDll,
            modInfo.SizeOfImage,
            NULL,
            0);

        LoadSymbol(strModule, (DWORD64) modInfo.lpBaseOfDll);

        if (!IsSymbolLoaded(strModule))
        {
            emit MissingSymbol(strModule);
        }
    }

    emit DebugLine(QString());
}