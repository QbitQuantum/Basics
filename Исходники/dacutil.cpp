HRESULT STDMETHODCALLTYPE
LiveProcDataTarget::ReadVirtual( 
    /* [in] */ CLRDATA_ADDRESS address,
    /* [length_is][size_is][out] */ PBYTE buffer,
    /* [in] */ ULONG32 request,
    /* [optional][out] */ ULONG32 *done)
{
    // ReadProcessMemory will fail if any part of the
    // region to read does not have read access.  This
    // routine attempts to read the largest valid prefix
    // so it has to break up reads on page boundaries.

    HRESULT status = S_OK;
    ULONG32 totalDone = 0;
    SIZE_T read;
    ULONG32 readSize;

    while (request > 0)
    {
        // Calculate bytes to read and don't let read cross
        // a page boundary.
        readSize = OS_PAGE_SIZE - (ULONG32)(address & (OS_PAGE_SIZE - 1));
        readSize = min(request, readSize);

        if (!ReadProcessMemory(m_process, (PVOID)(ULONG_PTR)address,
                               buffer, readSize, &read))
        {
            if (totalDone == 0)
            {
                // If we haven't read anything indicate failure.
                status = E_FAIL;
            }
            break;
        }

        totalDone += (ULONG32)read;
        address += read;
        buffer += read;
        request -= (ULONG32)read;
    }

    *done = totalDone;
    return status;
}