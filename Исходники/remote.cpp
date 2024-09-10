void IPC::process()
{
    IPCLock(this);
    for (unsigned i = 0; i < N_SLOTS; i++){
        if (s[i] != SLOT_IN)
            continue;
        QString in;
        QString out;
        string name = prefix();
        name += number(i);
        HANDLE hMem = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, name.c_str());
        if (hMem == NULL){
            s[i] = SLOT_NONE;
            PulseEvent(hEventOut);
            continue;
        }
        unsigned short *mem = (unsigned short*)MapViewOfFile(hMem, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if (mem == NULL){
            log(L_WARN, "Map error");
            s[i] = SLOT_NONE;
            PulseEvent(hEventOut);
            continue;
        }
        unsigned short *p;
        for (p = mem; *p; p++)
            in += QChar(*p);

        bool bError = false;
        bool bRes = remote->command(in, out, bError);
        p = mem;
        unsigned size = 0;
        if (!bError){
            if (bRes){
                *(p++) = QChar('>').unicode();
            }else{
                *(p++) = QChar('?').unicode();
            }
            size = out.length();
            if (size > 0x3F00)
                size = 0x3F00;
            memcpy(p, out.unicode(), size * sizeof(unsigned short));
            size++;
        }
        p[size] = 0;
        UnmapViewOfFile(mem);
        CloseHandle(hMem);
        s[i] = SLOT_OUT;
        PulseEvent(hEventOut);
    }
}