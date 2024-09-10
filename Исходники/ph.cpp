ushort
DWordXorShift(
    LPSSTR lpsstr,
    WORD wModulo,
    LPUL lpul
    )
{
    LPB   lpbName  = lpsstr->lpName;
    UNALIGNED ULONG* lpulName = (UNALIGNED ULONG*) lpbName;
    int   cb       = lpsstr->cb;
    int   cul;
    int   iul;
    ULONG ulSum    = 0;
    ULONG ulEnd    = 0;

    while (cb & 3) {
        ulEnd |= byt_toupper (lpbName [ cb - 1 ]);
        ulEnd <<= 8;
        cb -= 1;
    }

    cul = cb / 4;

    for (iul = 0; iul < cul; iul++) {
        ulSum ^= dwrd_toupper(lpulName[iul]);
        ulSum = _lrotl (ulSum, 4);
    }
    ulSum ^= ulEnd;

    *lpul = ulSum;

    return (ushort) (ulSum % wModulo);
}