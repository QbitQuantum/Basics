/**
 * Gets the process ID of the mmdrv.exe process running the VuGen script calling this function.
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
                                   // On Windows platforms, if a path is not specified,
                                   // lr_load_dll searches for the DLL using the standard sequence.

 	#ifdef  USING_WINDOWS

    // Only load the DLL the first time this function is called:
    if (is_msvcrt_dll_loaded == FALSE) {
        rc = lr_load_dll(dll_name);
        if (rc == 0) {
	        is_msvcrt_dll_loaded = TRUE;
		    pid = _getpid();
        }else{
	        is_msvcrt_dll_loaded = FALSE;
		    lr_error_message(">> Error loading %s to get WIN32 pid in wi_get_vuser_pid.", dll_name);
            // lr_abort();
        }
    }

	#endif // USING_WINDOWS

	return pid;
} // wi_get_vuser_pid