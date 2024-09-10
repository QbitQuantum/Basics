HANDLE OpenClientProcess(DWORD processID)
{
    // tries to open the targeted process
    // note: don't use PROCESS_ALL_ACCESS
    HANDLE hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ |
        PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION |
        PROCESS_CREATE_THREAD, FALSE, processID);
    // error?
    if (!hProcess)
    {
        if (GetLastError() == ERROR_ACCESS_DENIED)
        {
            printf("Process open is failed, ERROR_ACCESS_DENIED.\n");
            printf("Trying to override client's security descriptor (DACL) ");
            printf("and will try a re-open.\n");

            // clients before 12213 (this build doesn't contain) or
            // 11723 (don't have this WoW client so can't check)
            // override theirs security descriptor
            // (set flag PROTECTED_DACL_SECURITY_INFORMATION) so
            // the injector can't simply OpenProcess them
            //
            // because of this the injector modifies the
            // client's security descriptor (DACL) to the injector's one
            // so after that OpenProcess should work

            // "global" var which stores an error code
            DWORD error = 0;

            // ACL header
            PACL dacl;
            // that pointer contains the security descriptor
            PSECURITY_DESCRIPTOR securityDescriptor;

            // gets injector's security descriptor
            error = GetSecurityInfo(GetCurrentProcess(), SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, &dacl, NULL, &securityDescriptor);
            if (error)
            {
                printf("ERROR: Can't get injector's security secriptor, ");
                printf("ErrorCode: %u\n", error);
                return NULL;
            }

            // tries again to open the client process but
            // only with an access wich can override its DACL
            hProcess = OpenProcess(WRITE_DAC, FALSE, processID);
            if (!hProcess)
            {
                LocalFree(securityDescriptor);
                printf("ERROR: Process open is failed with only ");
                printf("WRITE_DAC access, ErrorCode: %u\n", GetLastError());
                return NULL;
            }

            // overrides client's DACL with injector's DACL
            error = SetSecurityInfo(hProcess, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION | UNPROTECTED_DACL_SECURITY_INFORMATION, 0, 0, dacl, 0);
            if (error)
            {
                LocalFree(securityDescriptor);
                CloseHandle(hProcess);
                printf("ERROR: Can't override client's DACL, ");
                printf("ErrorCode: %u\n", error);
                return NULL;
            }

            // release resources
            LocalFree(securityDescriptor);
            CloseHandle(hProcess);

            // now this should work
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
        }
        // error!
        if (!hProcess)
        {
            printf("ERROR: Process open is failed, ");
            printf("ErrorCode: %u\n", GetLastError());
            return NULL;
        }
    }
    return hProcess;
}