HANDLE AdvanceOpenProcess(DWORD pid, DWORD dwAccessRights)
{
    HANDLE hProcess = OpenProcess(dwAccessRights, FALSE, pid);

    if (hProcess == NULL)
    {
        HANDLE hpWriteDAC = OpenProcess(WRITE_DAC, FALSE, pid);

        if (hpWriteDAC == NULL)
        {
            HANDLE htok;
            TOKEN_PRIVILEGES tpOld;

            if (!OpenProcessToken(GetCurrentProcess(), 
                 TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &htok))
            {
                return false;
            }

            if (EnableTokenPrivilege(htok, SE_TAKE_OWNERSHIP_NAME, &tpOld))
            {
                HANDLE hpWriteOwner = OpenProcess(WRITE_OWNER, FALSE, pid);

                if (hpWriteOwner != NULL)
                {
                    BYTE buf[512];
                    DWORD cb = sizeof buf;

                    if (GetTokenInformation(htok, TokenUser, buf, cb, &cb))
                    {
                        DWORD err = SetSecurityInfo(hpWriteOwner, SE_KERNEL_OBJECT, 
                                    OWNER_SECURITY_INFORMATION, 
                                    ((TOKEN_USER *)(buf))->User.Sid, 0, 0, 0);
                        
                        if (err == ERROR_SUCCESS)
                        {
                            if (!DuplicateHandle(GetCurrentProcess(), hpWriteOwner, 
                                 GetCurrentProcess(), &hpWriteDAC, 
                                 WRITE_DAC, FALSE, 0))
                            {
                                hpWriteDAC = NULL;
                            }
                        }
                    }

                    CloseHandle(hpWriteOwner);
                }

                AdjustTokenPrivileges(htok, FALSE, &tpOld, 0, 0, 0);
            }

            CloseHandle(htok);
        }

        if (hpWriteDAC)
        {
            AdjustDacl(hpWriteDAC, dwAccessRights);

            if (!DuplicateHandle(GetCurrentProcess(), hpWriteDAC, 
                GetCurrentProcess(), &hProcess, dwAccessRights, FALSE, 0))
            {
                hProcess = NULL;
            }

            CloseHandle(hpWriteDAC);
        }
    }

    return (hProcess);
}