/******************************************************************
 *            EnumMetaFile   (GDI.175)
 *
 */
BOOL16 WINAPI EnumMetaFile16( HDC16 hdc16, HMETAFILE16 hmf,
			      MFENUMPROC16 lpEnumFunc, LPARAM lpData )
{
    METAHEADER *mh = MF_GetMetaHeader16(hmf);
    METARECORD *mr;
    HANDLETABLE16 *ht;
    HDC hdc = HDC_32(hdc16);
    HGLOBAL16 hHT;
    SEGPTR spht;
    unsigned int offset = 0;
    WORD i, seg;
    HPEN hPen;
    HBRUSH hBrush;
    HFONT hFont;
    WORD args[8];
    BOOL16 result = TRUE;

    TRACE("(%p, %04x, %p, %08lx)\n", hdc, hmf, lpEnumFunc, lpData);

    if(!mh) return FALSE;

    /* save the current pen, brush and font */
    hPen = GetCurrentObject(hdc, OBJ_PEN);
    hBrush = GetCurrentObject(hdc, OBJ_BRUSH);
    hFont = GetCurrentObject(hdc, OBJ_FONT);

    /* create the handle table */

    hHT = GlobalAlloc16(GMEM_MOVEABLE | GMEM_ZEROINIT,
		     sizeof(HANDLETABLE16) * mh->mtNoObjects);
    spht = WOWGlobalLock16(hHT);

    seg = hmf | 7;
    offset = mh->mtHeaderSize * 2;

    /* loop through metafile records */

    args[7] = hdc16;
    args[6] = SELECTOROF(spht);
    args[5] = OFFSETOF(spht);
    args[4] = seg + (HIWORD(offset) << __AHSHIFT);
    args[3] = LOWORD(offset);
    args[2] = mh->mtNoObjects;
    args[1] = HIWORD(lpData);
    args[0] = LOWORD(lpData);

    while (offset < (mh->mtSize * 2))
    {
        DWORD ret;

	mr = (METARECORD *)((char *)mh + offset);

        WOWCallback16Ex( (DWORD)lpEnumFunc, WCB16_PASCAL, sizeof(args), args, &ret );
        if (!LOWORD(ret))
	{
	    result = FALSE;
	    break;
	}

	offset += (mr->rdSize * 2);
        args[4] = seg + (HIWORD(offset) << __AHSHIFT);
        args[3] = LOWORD(offset);
    }

    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);
    SelectObject(hdc, hFont);

    ht = GlobalLock16(hHT);

    /* free objects in handle table */
    for(i = 0; i < mh->mtNoObjects; i++)
      if(*(ht->objectHandle + i) != 0)
        DeleteObject( (HGDIOBJ)(ULONG_PTR)(*(ht->objectHandle + i) ));

    /* free handle table */
    GlobalFree16(hHT);
    MF_ReleaseMetaHeader16(hmf);
    return result;
}