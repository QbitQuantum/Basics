// init_xsave_info
void init_xsave_info()
{
    int xsave_size = FXSAVE_SIZE; 
    uint64_t xcr0 = 0;
    if(try_read_xcr0(&xcr0))
    {
        // CPUID function 0DH, sub-function 0 
        // EBX enums the size (in bytes) required by XSAVE for all the components currently set in XCR0
        int cpu_info[4] = {0};
        __cpuid(cpu_info, 0xD);
        xsave_size = cpu_info[1];
        g_xsave_enabled = 1;
    }
    set_xsave_info(xsave_size, (xcr0 & XFRM_YMM_BITMASK) ? 1 : 0);
}