//===========================================================================
extern "C" BOOL WINAPI DllMain (HINSTANCE hDLLInst, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // The DLL is being loaded for the first time by a given process.
        // Perform per-process initialization here.  If the initialization
        // is successful, return TRUE; if unsuccessful, return FALSE.

        // TODO: DisableThreadLibraryCalls screws with msvcrt
        // TODO: RegisterWindowMessage is not safe to called from the dllmain, it can lead to deadlocks.
        //       we should put it into some initializer instead.

        hInstance = hDLLInst;
        DisableThreadLibraryCalls(hDLLInst);
        bbSkinMsg = RegisterWindowMessage(BBLEANSKIN_MSG);
        //dbg_printf("Attached to %x HHOOKs: CW %x GM %x", hDLLInst, hCallWndHook, hGetMsgHook);
        break;

    case DLL_PROCESS_DETACH:
        // The DLL is being unloaded by a given process.  Do any
        // per-process clean up here, such as undoing what was done in
        // DLL_PROCESS_ATTACH.  The return value is ignored.
        //dbg_printf("unloaded.");
        break;

    case DLL_THREAD_ATTACH:
        // A thread is being created in a process that has already loaded
        // this DLL.  Perform any per-thread initialization here.  The
        // return value is ignored.
        //dbg_printf("new thread");
        break;

    case DLL_THREAD_DETACH:
        // A thread is exiting cleanly in a process that has already
        // loaded this DLL.  Perform any per-thread clean up here.  The
        // return value is ignored.
        //dbg_printf("end thread");
        break;
    }
    return TRUE;
}