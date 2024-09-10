void efi_init() {
    // Determine if running UEFI. If no -> then exit
    FIRMWARE_TYPE fwtype;    
    DWORD dwRet;
    GetFirmwareType(&fwtype);
    if (fwtype != FirmwareTypeUefi) {
        printf("You are not running UEFI!\n");
        exit(-1);
    }

    ObtainPrivileges(SE_SYSTEM_ENVIRONMENT_NAME);

    // Perform check if UEFI variables are present.
    // If not, we get ERROR_INVALID_FUNCTION on this.
    // If yes, we get ERROR_NOACCESS because we are accessing not-existing variable.
    // Any other errors are unexpected.
    dwRet = 0;
    if (GetFirmwareEnvironmentVariable(___T(""), ___T("{00000000-0000-0000-0000-000000000000}"), NULL, 0) == 0) {
        if (GetLastError() == ERROR_INVALID_FUNCTION) {
            printf("Cannot access UEFI (are you running BIOS?)\n");
            exit(-1);
        }
        else if (GetLastError() == ERROR_NOACCESS) {
            // Expected
        }
        else {
            PrintError(GetLastError());
            exit(GetLastError());
        }
    }
}