PVOID FASTCALL HMValidateSharedHandle(
    HANDLE h,
    BYTE bType)
{
    DWORD dwError;
    KERNEL_PVOID pobj = NULL;

#if DBG != 0 && !defined(_USERK_)

    /*
     * We don't want 32 bit apps passing 16 bit handles
     *  we should consider failing this before we get
     *  stuck supporting it (Some VB apps do this).
     */
    if ((h != NULL)
           && (HMUniqFromHandle(h) == 0)
           && !(GetClientInfo()->dwTIFlags & TIF_16BIT)) {
        RIPMSG3(RIP_WARNING, "HMValidateHandle: 32bit process [%d] using 16 bit handle [%#p] bType:%#lx",
                HandleToUlong(NtCurrentTeb()->ClientId.UniqueProcess), h, (DWORD)bType);
    }
#endif

    /*
     * Validation macro. Falls through if the handle is invalid.
     */
    ValidateSharedHandleMacro(pobj, h, bType);

    if (pobj != NULL)
        return pobj;

    switch (bType) {
        case TYPE_MONITOR:
            dwError = ERROR_INVALID_MONITOR_HANDLE;
            break;

        default:
            UserAssertMsg0(0, "Logic error in HMValidateSharedHandle");
            break;
    }

    RIPERR2(dwError,
            RIP_WARNING,
            "HMValidateSharedHandle: Invalid:%#p Type:%#lx",
            h, (DWORD)bType);

    /*
     * If we get here, it's an error.
     */
    return NULL;
}