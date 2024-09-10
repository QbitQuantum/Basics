/**
 * Gets the process ID of the mmdrv.exe process that is running the VuGen script that called
 * this function.
 *
 * @return    This function returns the process ID of the calling process.
 *
 * Example code:
 *     // Print the vuser's process ID
 *     int vuser_pid; vuser_pid = wi_get_vuser_pid();
 *     lr_output_message("vuser_pid: %d", vuser_pid);
 *
 * Note: This function only works on Windows.
 * From lr-libc.
 */
int wi_get_vuser_pid() {
    int rc=LR_PASS; // return code
    int pid=0; // the process id (usually 4 digits)
    static int is_msvcrt_dll_loaded = FALSE; // A static variable inside a function keeps its value between
                                   // invocations. The FALSE value is assigned only on the first
                                   // invocation.
    char* dll_name = "MSVCRT.DLL"; // This DLL contains the _getpid() function. It is a standard
                                   // Windows DLL, usually found in C:\WINDOWS\system32.
                                   // Note: on Windows platforms, if you do not specify a path,
                                   // lr_load_dll searches for the DLL using the standard sequence
                                   // used by the C++ function, LoadLibrary.

    // Only load the DLL the first time this function is called:
    if (is_msvcrt_dll_loaded == FALSE) {
        rc = lr_load_dll(dll_name);
        if (rc != 0) {
            lr_error_message("Error loading %s.", dll_name);
            lr_abort();
        }
        is_msvcrt_dll_loaded = TRUE;
    }

    pid = _getpid();

    return pid;
} // wi_get_vuser_pid