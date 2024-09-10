/// <summary>
/// Write virtual memory
/// </summary>
/// <param name="lpBaseAddress">Memory address</param>
/// <param name="lpBuffer">Buffer to write</param>
/// <param name="nSize">Number of bytes to read</param>
/// <param name="lpBytes">Mumber of bytes read</param>
/// <returns>Status code</returns>
NTSTATUS Native::WriteProcessMemoryT( ptr_t lpBaseAddress, LPCVOID lpBuffer, size_t nSize, DWORD64 *lpBytes /*= nullptr */ )
{
    SetLastNtStatus( STATUS_SUCCESS );
    WriteProcessMemory( _hProcess, reinterpret_cast<LPVOID>(lpBaseAddress), lpBuffer, nSize, reinterpret_cast<SIZE_T*>(lpBytes) );
    return LastNtStatus();
}