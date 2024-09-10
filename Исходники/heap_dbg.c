/*******************MemHeap内存改写处理************************/
INT find_maps(ULONG addr, ULONG *start, ULONG *end)
{
#ifdef _OS_LINUX_
    char mapFile[30];
    char buf[120];
    char attr[4];
    FILE *fp;
    ULONG  pid = vos_get_pid();

    sprintf(mapFile, "/proc/%lu/maps", pid);

    if(NULL == (fp = fopen(mapFile, "r")))
    	return FALSE;

    while(NULL != fgets(buf, 120, fp))
    {
        sscanf(buf, "%lx-%lx %s", start, end, attr);

        if((addr >= *start) && (addr < *end) &&
            (attr[0] == 'r') && (attr[1] == 'w'))
        {
            fclose(fp);
            return TRUE;
        }
        else if(addr < *start)/* 位于空洞 */
            break;
        else/* 下一个 */
            continue;
    }

    fclose(fp);
    *start = (ULONG)NULL; *end = (ULONG)NULL;
    return FALSE;
#endif

#ifdef _OS_WINNT_
    MEMORY_BASIC_INFORMATION info;
    BYTE *head, *tail;
    BYTE *page = (BYTE*)round_down(addr, PAGE_SIZE);

    *start = (ULONG)NULL; *end = (ULONG)NULL;

    if(0 == VirtualQuery(page, &info, sizeof(info)))
        return FALSE;

    if((info.Protect != PAGE_READWRITE) ||
        (info.AllocationProtect != PAGE_READWRITE) ||
        (info.State  != MEM_COMMIT))
        return FALSE;

    *end = (ULONG)(page + info.RegionSize);

    tail = (BYTE*)(info.AllocationBase);
    do
    {
        head = tail;
        VirtualQuery(head, &info, sizeof(info));
        tail = head + info.RegionSize;
    }while(addr >= (ULONG)tail);

    *start = (ULONG)head;
    return TRUE;
#endif
}