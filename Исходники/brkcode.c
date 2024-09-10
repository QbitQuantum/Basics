void allocBreakPoint(HANDLE hProcess, BREAKPOINT *pt)
{
    unsigned char bf;
    if (!pt->active && pt->addresses)
    {
        int i =0,j;
        int *p;
        for (p = pt->addresses; *p !=0; ++p)
            i++;
        if (!pt->tempvals)
        {
             pt->tempvals = calloc(i, sizeof(int));
        }
        strcpy(pt->name, "unknown");
        for (i=0, p = pt->addresses; *p !=0; ++p, ++i)
        {
            DWORD len;
            if (ReadProcessMemory(hProcess, (LPVOID)pt->addresses[i], (LPVOID) &bf, 1,
                &len))
            {
                if (!len)
                    return ;
                if (bf == 0xcc)
                {
                    pt->tempvals[i] = -1;
                }
                else
                {
                    WriteBreakPoint(hProcess, pt->addresses[i], 0xcc);
                    pt->active = TRUE;
                    pt->tempvals[i] = bf;
                }
                
            }
            if (i == 0)
            {
                char name[256];
                DWORD n = FindFunctionName(name, pt->addresses[i], NULL, NULL);
                if (n)
                    sprintf(pt->name, "%s + 0x%x", name, pt->addresses[i]-n);
            }
        }
    }
}