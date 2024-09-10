/// <summary>
/// Get WOW64 TEB
/// </summary>
/// <param name="ppeb">Retrieved TEB</param>
/// <returns>TEB pointer</returns>
ptr_t NativeWow64::getTEB( HANDLE hThread, _TEB32* pteb )
{
    // Target process is x64. TEB32 is not available.
    if (_wowBarrier.targetWow64 == false)
    {
        return 0;
    }
    else
    {
        _THREAD_BASIC_INFORMATION_T<DWORD> tbi = { 0 };
        ULONG bytes = 0;

        if (GET_IMPORT( NtQueryInformationThread )( hThread, (THREADINFOCLASS)0, &tbi, sizeof(tbi), &bytes ) == STATUS_SUCCESS)
            if (pteb)
                ReadProcessMemory( _hProcess, reinterpret_cast<LPCVOID>(tbi.TebBaseAddress), pteb, sizeof(_TEB32), NULL );

        return static_cast<ptr_t>(tbi.TebBaseAddress);
    }
}