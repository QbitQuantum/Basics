static bool InitPhysX()
{
#ifdef HS_BUILD_FOR_WIN32
    plSimulationMgr::Init();
    if (!plSimulationMgr::GetInstance()) {
        if (plFileInfo(s_physXSetupExe).Exists()) {
            // launch the PhysX installer
            SHELLEXECUTEINFOW info;
            memset(&info, 0, sizeof(info));
            info.cbSize = sizeof(info);
            info.lpFile = s_physXSetupExe.AsString().to_wchar();
            info.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC;
            ShellExecuteExW(&info);

            // wait for completion
            WaitForSingleObject(info.hProcess, INFINITE);

            // cleanup
            CloseHandle(info.hProcess);
        } else {
            hsMessageBox("You must install PhysX before you can play URU.", "Error", hsMessageBoxNormal, hsMessageBoxIconError);
            return false;
        }
    }
    if (plSimulationMgr::GetInstance()) {
        plSimulationMgr::GetInstance()->Suspend();
        return true;
    } else {
        hsMessageBox("PhysX install failed. You will not be able to play URU.", "Error", hsMessageBoxNormal, hsMessageBoxIconError);
        return false;
    }
#else
    return false;
#endif // HS_BUILD_FOR_WIN32
}