/***********************************************************************
 *             VirtualFreeEx   (KERNEL32.@)
 *
 * Releases or decommits a region of pages in virtual address space.
 *
 * PARAMS
 *  process [I] Handle to process.
 *  addr    [I] Address of region to free.
 *  size    [I] Size of region.
 *  type    [I] Type of operation.
 *
 * RETURNS
 *	Success: TRUE.
 *	Failure: FALSE.
 */
BOOL WINAPI VirtualFreeEx( HANDLE process, LPVOID addr, SIZE_T size, DWORD type )
{
    NTSTATUS status = NtFreeVirtualMemory( process, &addr, &size, type );
    if (status) SetLastError( RtlNtStatusToDosError(status) );
    return !status;
}