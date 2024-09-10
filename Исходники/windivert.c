/*
 * Open a WinDivert handle.
 */
extern HANDLE WinDivertOpen(const char *filter, WINDIVERT_LAYER layer,
    INT16 priority, UINT64 flags)
{
    struct windivert_ioctl_filter_s object[WINDIVERT_FILTER_MAXLEN];
    UINT obj_len;
    ERROR comp_err;
    DWORD err;
    HANDLE handle;
    SC_HANDLE service;
    UINT32 priority32;

    // Parameter checking.
    if (!WINDIVERT_FLAGS_VALID(flags) || layer > WINDIVERT_LAYER_MAX)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return INVALID_HANDLE_VALUE;
    }
    priority32 = WINDIVERT_PRIORITY(priority);
    if (priority32 < WINDIVERT_PRIORITY_MIN ||
        priority32 > WINDIVERT_PRIORITY_MAX)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return INVALID_HANDLE_VALUE;
    }

    // Compile the filter:
    comp_err = WinDivertCompileFilter(filter, layer, object, &obj_len);
    if (IS_ERROR(comp_err))
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return INVALID_HANDLE_VALUE;
    }

#ifdef WINDIVERT_DEBUG
    WinDivertFilterDump(object, obj_len);
#endif

    // Attempt to open the WinDivert device:
    handle = CreateFile(L"\\\\.\\" WINDIVERT_DEVICE_NAME,
        GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, INVALID_HANDLE_VALUE);
    if (handle == INVALID_HANDLE_VALUE)
    {
        err = GetLastError();
        if (err != ERROR_FILE_NOT_FOUND && err != ERROR_PATH_NOT_FOUND)
        {
            return INVALID_HANDLE_VALUE;
        }

        // Open failed because the device isn't installed; install it now.
        SetLastError(0);
        service = WinDivertDriverInstall();
        if (service == NULL)
        {
            if (GetLastError() == 0)
            {
                SetLastError(ERROR_OPEN_FAILED);
            }
            return INVALID_HANDLE_VALUE;
        }
        handle = CreateFile(L"\\\\.\\" WINDIVERT_DEVICE_NAME,
            GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
            INVALID_HANDLE_VALUE);

        // Schedule the service to be deleted (once all handles are closed).
        DeleteService(service);
        CloseServiceHandle(service);

        if (handle == INVALID_HANDLE_VALUE)
        {
            return INVALID_HANDLE_VALUE;
        }
    }

    // Set the layer:
    if (layer != WINDIVERT_LAYER_DEFAULT)
    {
        if (!WinDivertIoControl(handle, IOCTL_WINDIVERT_SET_LAYER, 0,
                (UINT64)layer, NULL, 0, NULL))
        {
            CloseHandle(handle);
            return INVALID_HANDLE_VALUE;
        }
    }

    // Set the flags:
    if (flags != 0)
    {
        if (!WinDivertIoControl(handle, IOCTL_WINDIVERT_SET_FLAGS, 0,
                (UINT64)flags, NULL, 0, NULL))
        {
            CloseHandle(handle);
            return INVALID_HANDLE_VALUE;
        }
    }

    // Set the priority:
    if (priority32 != WINDIVERT_PRIORITY_DEFAULT)
    {
        if (!WinDivertIoControl(handle, IOCTL_WINDIVERT_SET_PRIORITY, 0,
                (UINT64)priority32, NULL, 0, NULL))
        {
            CloseHandle(handle);
            return INVALID_HANDLE_VALUE;
        }
    }

    // Start the filter:
    if (!WinDivertIoControl(handle, IOCTL_WINDIVERT_START_FILTER, 0, 0,
            object, obj_len*sizeof(struct windivert_ioctl_filter_s), NULL))
    {
        CloseHandle(handle);
        return INVALID_HANDLE_VALUE;
    }

    // Success!
    return handle;
}