int EBuffer::ShowPosition() {
    int CLine, NLines;
    int CAct, NAct;
    int CColumn, NColumns;
    int CCharPos, NChars;
#ifdef HEAPWALK
    unsigned long MemUsed = 0, MemFree = 0, BlkUsed = 0, BlkFree = 0, BigFree = 0, BigUsed = 0;
#endif

    if (!View)
        return 0;

    CLine = CP.Row + 1;
    NLines = VCount;
    CAct = VToR(CP.Row) + 1;
    NAct = RCount;
    CColumn = CP.Col + 1;
    NColumns = LineLen(CP.Row);
    CCharPos = CharOffset(VLine(CP.Row), CP.Col) + 1;
    NChars = VLine(CP.Row)->Count;

#ifdef HEAPWALK
    if (_heapchk() != _HEAPOK) {
        MemUsed = -1;
    } else {
        _HEAPINFO hi;

        hi._pentry = NULL;
        while (_heapwalk(&hi) == _HEAPOK) {
            if (hi._useflag == _USEDENTRY) {
                BlkUsed++;
                MemUsed += hi._size;
                if (hi._size > BigUsed)
                    BigUsed = hi._size;
                //fprintf(stderr, "USED %d\n", hi._size);
            } else {
                BlkFree++;
                MemFree += hi._size;
                if (hi._size > BigFree)
                    BigFree = hi._size;
                //fprintf(stderr, "FREE %d\n", hi._size);
            }
        }
    }
#endif

    int NN = -1;
    if (US.UndoPtr > 0)
        NN = US.Top[US.UndoPtr - 1];
    Msg(S_INFO,
#ifdef HEAPWALK
        "M%ld,%ld B%ld,%ld S%ld,%ld"
#endif
        "L%d/%d G%d/%d/%d A%d/%d C%d/%d P%d/%d "
        "U%d/%d/%d "
        "H%d/%d/%d",
#ifdef HEAPWALK
        MemUsed, MemFree, BlkUsed, BlkFree, BigUsed, BigFree,
#endif
        CLine, NLines,
        RGap, RCount, RAllocated,
        CAct, NAct,
        CColumn, NColumns,
        CCharPos, NChars,
        US.UndoPtr, US.Num, NN,
        StartHilit, MinRedraw, MaxRedraw);
    return 1;
}