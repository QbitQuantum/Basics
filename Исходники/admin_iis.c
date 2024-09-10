static app_mode_t get_app_mode() {
    SYSTEM_INFO sys_info;
    GetNativeSystemInfo(&sys_info);
    if (sys_info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {
        return MODE_X86;
    } else if (sys_info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
        return MODE_X64;
    }
    return MODE_UNKNOWN;
}