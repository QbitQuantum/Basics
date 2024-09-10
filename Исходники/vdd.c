BOOL
VDDInitialize(IN HANDLE Module, IN DWORD Reason, IN LPVOID Reserved)
{
    FUNC_ENTER();

    DBG_PRINT((DBG_PREFIX "OpencbmVDD.Entry: " __DATE__ " " __TIME__));

    switch (Reason) 
    {
        case DLL_PROCESS_ATTACH:
            vdd_handle = Module;
            VDDInstallUserHook(vdd_handle, NULL, NULL, VDDBlockHandler, NULL);
            break;

        case DLL_PROCESS_DETACH:
            DBG_ASSERT(vdd_handle == Module);
            vdd_uninstall_iohook_internal();
            VDDDeInstallUserHook(Module);

            // make sure all CBM_FILE handles are closed
            // whenever this VDD is unloaded
            vdd_cbmfile_closeall();
            break;

        default:
            break;

    }

    FUNC_LEAVE_BOOL(TRUE);
}