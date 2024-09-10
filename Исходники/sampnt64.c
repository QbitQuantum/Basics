void GetNextAddr( void )
{
    struct {
        unsigned long   ptr;
        seg             cs;
        off             ip;
    } stack_entry;
    SIZE_T      len;

    if( commonAddr.segment == 0 ) {
        CGraphOff = 0;
        CGraphSeg = 0;
    } else {
        ReadProcessMemory( processHandle, (LPVOID)Comm.cgraph_top, &stack_entry, sizeof( stack_entry ), &len );
        CGraphOff = stack_entry.ip;
        CGraphSeg = stack_entry.cs;
        Comm.cgraph_top = stack_entry.ptr;
    }
}