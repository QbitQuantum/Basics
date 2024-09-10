void NTServerManager::PacketProcessingThread()
{
    // A ping of < 30ms should be acceptable.
    std::chrono::milliseconds SleepDuration(30);

    while (true)
    {
        std::this_thread::sleep_for(SleepDuration);

        for (auto Iterator = Host_ServerAddresses.begin(); Iterator != Host_ServerAddresses.end(); ++Iterator)
        {
            try
            {
                Iterator->second->Internal_RunServerFrame();
            }
            catch (const std::exception &Exception)
            {
                DebugPrint("\n\n\n==========================================================");
                DebugPrint("OpenNet error");
                DebugPrint(Exception.what());
                DebugPrint("\n=============================================\n");

                DebugPrint("One of the local socket processes threw an unhandled exception.");
                DebugPrint("The plugin may still work in offline mode but should be restarted.");

                HANDLE hFile = INVALID_HANDLE_VALUE;
                hFile = CreateFileA("OpenNetCrash.dmp", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

                if (hFile != INVALID_HANDLE_VALUE)
                {
                    if(strstr(GetCommandLineA(), "-handledump"))
                        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithHandleData, NULL, NULL, NULL);
                    else
                        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, NULL, NULL, NULL);

                    if (hFile != INVALID_HANDLE_VALUE)
                        CloseHandle(hFile);
                }
            }
        }
    }
}