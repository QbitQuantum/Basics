int ast_get_firmware_type (enum AST_FIRMWARE_TYPE *type)
{
    // NOTE: Since Windows 8, there's a WinAPI called GetFirmwareType
    //   (https://msdn.microsoft.com/en-us/library/windows/desktop/hh848321(v=vs.85).aspx),
    //   which can quickly determine the computer's firmware.
    //
    //   Use GetFirmwareType on newer Windows, or the traditional way -- passing dummy UUID
    //   and variable name to GetFirmwareEnvironmentVariable and check return value.
    if (IsWindows8OrGreater () == TRUE) {
        if (_ast_get_firmware_type_on_win8_or_greater (type) == EXIT_SUCCESS) {
            return EXIT_SUCCESS;
        } else {
            fprintf (stderr, " ** cannot get firmware type.\n");
            return EXIT_FAILURE;
        }
    } else {
        if (_ast_get_firmware_type_on_win8_lesser (type) == EXIT_SUCCESS) {
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, " ** cannot get firmware type.\n");
        }
    }

    // Whatever.
    return EXIT_FAILURE;
}