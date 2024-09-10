HBITMAP
APIENTRY
NtGdiCreateBitmap(
    IN INT nWidth,
    IN INT nHeight,
    IN UINT cPlanes,
    IN UINT cBitsPixel,
    IN OPTIONAL LPBYTE pUnsafeBits)
{
    HBITMAP hbmp;
    ULONG cRealBpp, cjWidthBytes, iFormat;
    ULONGLONG cjSize;
    PSURFACE psurf;

    /* Calculate bitmap format and real bits per pixel. */
    iFormat = BitmapFormat(cBitsPixel * cPlanes, BI_RGB);
    cRealBpp = gajBitsPerFormat[iFormat];

    /* Calculate width and image size in bytes */
    cjWidthBytes = WIDTH_BYTES_ALIGN16(nWidth, cRealBpp);
    cjSize = (ULONGLONG)cjWidthBytes * nHeight;

    /* Check parameters (possible overflow of cjSize!) */
    if ((iFormat == 0) || (nWidth <= 0) || (nWidth >= 0x8000000) || (nHeight <= 0) ||
        (cBitsPixel > 32) || (cPlanes > 32) || (cjSize >= 0x100000000ULL))
    {
        DPRINT1("Invalid bitmap format! Width=%d, Height=%d, Bpp=%u, Planes=%u\n",
                nWidth, nHeight, cBitsPixel, cPlanes);
        EngSetLastError(ERROR_INVALID_PARAMETER);
        return NULL;
    }

    /* Allocate the surface (but don't set the bits) */
    psurf = SURFACE_AllocSurface(STYPE_BITMAP,
                                 nWidth,
                                 nHeight,
                                 iFormat,
                                 0,
                                 0,
                                 NULL);
    if (!psurf)
    {
        DPRINT1("SURFACE_AllocSurface failed.\n");
        return NULL;
    }

    /* Mark as API and DDB bitmap */
    psurf->flags |= (API_BITMAP | DDB_SURFACE);

    /* Check if we have bits to set */
    if (pUnsafeBits)
    {
        /* Protect with SEH and copy the bits */
        _SEH2_TRY
        {
            ProbeForRead(pUnsafeBits, (SIZE_T)cjSize, 1);
            UnsafeSetBitmapBits(psurf, 0, pUnsafeBits);
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            GDIOBJ_vDeleteObject(&psurf->BaseObject);
            _SEH2_YIELD(return NULL;)
        }
        _SEH2_END
    }
    else
    {