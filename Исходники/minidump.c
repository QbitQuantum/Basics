/******************************************************************
 *		fetch_process_info
 *
 * reads system wide process information, and make spi point to the record
 * for process of id 'pid'
 */
static BOOL fetch_process_info(struct dump_context* dc)
{
    ULONG       buf_size = 0x1000;
    NTSTATUS    nts;

    dc->pcs_buffer = NULL;
    if (!(dc->pcs_buffer = HeapAlloc(GetProcessHeap(), 0, buf_size))) return FALSE;
    for (;;)
    {
        nts = NtQuerySystemInformation(SystemProcessInformation, 
                                       dc->pcs_buffer, buf_size, NULL);
        if (nts != STATUS_INFO_LENGTH_MISMATCH) break;
        dc->pcs_buffer = HeapReAlloc(GetProcessHeap(), 0, dc->pcs_buffer, 
                                     buf_size *= 2);
        if (!dc->pcs_buffer) return FALSE;
    }

    if (nts == STATUS_SUCCESS)
    {
        dc->spi = dc->pcs_buffer;
        for (;;)
        {
            if (dc->spi->dwProcessID == dc->pid) return TRUE;
            if (!dc->spi->dwOffset) break;
            dc->spi = (SYSTEM_PROCESS_INFORMATION*)     
                ((char*)dc->spi + dc->spi->dwOffset);
        }
    }
    HeapFree(GetProcessHeap(), 0, dc->pcs_buffer);
    dc->pcs_buffer = NULL;
    dc->spi = NULL;
    return FALSE;
}