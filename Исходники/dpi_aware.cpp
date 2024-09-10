bool IsProcessDpiAware() {
    typedef BOOL(WINAPI *IsProcessDPIAwarePtr)(VOID);
    IsProcessDPIAwarePtr is_process_dpi_aware_func =
            reinterpret_cast<IsProcessDPIAwarePtr>(
                GetProcAddress(GetModuleHandleA("user32.dll"), 
                    "IsProcessDPIAware"));
    BOOL is_aware = FALSE;
    if (is_process_dpi_aware_func) {
        is_aware = is_process_dpi_aware_func();
        if (is_aware == TRUE) {
            return true;
        }
    }
    // GetProcessDpiAwareness is available only on Win8. So it
    // should be called only as a back-up plan after IsProcessDPIAware
    // was called. Also if IsProcessDPIAware returned false,
    // then GetProcessDpiAwareness is called as well.
    if (GetProcessDpiAwareness() != PROCESS_DPI_UNAWARE) {
        return true;
    }
    return false;
}