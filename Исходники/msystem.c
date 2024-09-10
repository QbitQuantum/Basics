WORD
MAllocMem(
    DWORD Size,
    LPBYTE * pBuffer
    )
{

    NetapipBufferAllocate(Size, (LPVOID *) pBuffer);

    return(0);

}