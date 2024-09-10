/// <summary>
/// Capture stack frames
/// </summary>
/// <param name="ip">Current instruction pointer</param>
/// <param name="sp">Current stack pointer</param>
/// <param name="results">Found frames.</param>
/// <param name="depth">Frame depth limit</param>
/// <returns>Number of found frames</returns>
size_t TraceHook::StackBacktrace( uintptr_t ip, uintptr_t sp, vecStackFrames& results, uintptr_t depth /*= 10 */ )
{
    SYSTEM_INFO sysinfo = { 0 };
    uintptr_t stack_base = (uintptr_t)((PNT_TIB)NtCurrentTeb())->StackBase;

    GetNativeSystemInfo( &sysinfo );

    // Store exception address
    results.emplace_back( std::make_pair( 0, ip ) );

    // Walk stack
    for (uintptr_t stackPtr = sp; stackPtr < stack_base && results.size() <= depth; stackPtr += sizeof(void*))
    {
        uintptr_t stack_val = *(uintptr_t*)stackPtr;
        MEMORY_BASIC_INFORMATION meminfo = { 0 };

        // Decode value
        uintptr_t original = stack_val & HIGHEST_BIT_UNSET;

        // Invalid value
        if ( original < (uintptr_t)sysinfo.lpMinimumApplicationAddress ||
             original > (uintptr_t)sysinfo.lpMaximumApplicationAddress)
        {
            continue;
        }

        // Check if memory is executable
        if (VirtualQuery( (LPVOID)original, &meminfo, sizeof(meminfo) ) != sizeof(meminfo))
            continue;

        if ( meminfo.Protect != PAGE_EXECUTE_READ &&
             meminfo.Protect != PAGE_EXECUTE_WRITECOPY &&
             meminfo.Protect != PAGE_EXECUTE_READWRITE)
        {
            continue;
        }

        // Detect 'call' instruction
        for (uintptr_t j = 1; j < 8; j++)
        {
            DISASM info = { 0 };
            info.EIP = original - j;

        #ifdef _M_AMD64
            info.Archi = 64;
        #endif  

            if (Disasm( &info ) > 0 && info.Instruction.BranchType == CallType)
            {
                results.emplace_back( std::make_pair( stackPtr, stack_val ) );
                break;
            }
        }

    }

    return results.size();
}