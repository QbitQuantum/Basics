void IosBackupAdapter::GenerateKeyChain( const std::wstring& appDir )
{
    std::wstring keychainTool = Utils::GetExePath() + L"\\tools\\ios_backup\\keychain_tool.exe";
    std::wstring originDir = appDir;
    std::wstring workDir = appDir;

    if ( Utils::FileExist(workDir + L"\\keychain.csv") )
        return;

    PROCESS_INFORMATION piProcInfo = {0};
    STARTUPINFOA siStartInfo = {0};

    siStartInfo.wShowWindow = SW_HIDE;

    // Create process 'keychain_tool.exe'
    char cmd[1024] = {0};
    wsprintfA(cmd, " -p \"%s\\KeychainDomain\\keychain-backup.plist\" \"%s\\Manifest.plist\"",
              Utils::WideToAnsi(workDir).c_str(),
              Utils::WideToAnsi(workDir).c_str());

    std::string currentDir = "C:\\Temp";
    CreateDirectoryA(currentDir.c_str(), NULL);

    if ( !CreateProcessA(
                Utils::WideToAnsi(keychainTool).c_str(),
                cmd,
                NULL,
                NULL,
                TRUE,
                CREATE_NO_WINDOW,
                NULL,
                currentDir.c_str(),
                &siStartInfo,
                &piProcInfo) )
    {
        Utils::__TRACE(L"[IosBackupAdapter] CreateProcessW failed. [%d] [%s] \r\n", GetLastError(), Utils::AnsiToWide(cmd).c_str());
        return;
    }

    WaitForSingleObject(piProcInfo.hProcess, INFINITE);

    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);

    std::wstring src = Utils::AnsiToWide(currentDir) + L"\\keychain.csv";
    std::wstring dst = workDir + L"\\keychain.csv";

    CopyFileW(src.c_str(), dst.c_str(), FALSE);

    Utils::SHMove(Utils::AnsiToWide(currentDir).c_str(), (workDir+L"\\keychain").c_str());
    Utils::SHDel(Utils::AnsiToWide(currentDir).c_str());
}