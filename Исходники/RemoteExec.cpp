/// <summary>
/// Execute code in context of our worker thread
/// </summary>
/// <param name="pCode">Cde to execute</param>
/// <param name="size">Code size.</param>
/// <param name="callResult">Execution result</param>
/// <returns>Status</returns>
NTSTATUS RemoteExec::ExecInWorkerThread( PVOID pCode, size_t size, uint64_t& callResult )
{
    NTSTATUS dwResult = STATUS_SUCCESS;

    // Create thread if needed
    CreateRPCEnvironment();

    // Write code
    dwResult = CopyCode( pCode, size );
    if (dwResult != STATUS_SUCCESS)
        return dwResult;

    if (_hWaitEvent)
        ResetEvent( _hWaitEvent );

    // Patch KiUserApcDispatcher 
#ifdef USE64
    if (!_apcPatched && IsWindows7OrGreater() && !IsWindows8OrGreater())
    {
        if (_proc.core().native()->GetWow64Barrier().type == wow_64_32)
        {
            auto patchBase = _proc.nativeLdr().APC64PatchAddress();

            if (patchBase != 0)
            {
                DWORD flOld = 0;
                _memory.Protect(patchBase, 6, PAGE_EXECUTE_READWRITE, &flOld);
                _memory.Write(patchBase + 0x2, (uint8_t)0x0C);
                _memory.Write( patchBase + 0x4, (uint8_t)0x90 );
                _memory.Protect( patchBase, 6, flOld, nullptr );
            }

            _apcPatched = true;
        }
        else
            _apcPatched = true;
    }
#endif

    // Execute code in thread context
    if (QueueUserAPC( _userCode.ptr<PAPCFUNC>(), _hWorkThd.handle(), _userCode.ptr<ULONG_PTR>() ))
    {
        dwResult = WaitForSingleObject( _hWaitEvent, INFINITE );
        callResult = _userData.Read<uint64_t>( RET_OFFSET, 0 );
    }
    else
        return LastNtStatus();

    // Ensure APC function fully returns
    Sleep( 1 );

    return dwResult;
}