VOID
FASTCALL
Dib_BitBlt_SRCCOPY_S32_D32_EqSurf(PBLTDATA pBltData)
{
    ULONG cLines, cRows = pBltData->ulWidth;
    PBYTE pjDestBase = pBltData->siDst.pjBase;
    PBYTE pjSrcBase = pBltData->siSrc.pjBase;

    /* Loop all lines */
    cLines = pBltData->ulHeight;
    while (cLines--)
    {
        __movsd((PULONG)pjDestBase, (PULONG)pjSrcBase, cRows);
        pjDestBase += pBltData->siDst.cjAdvanceY;
        pjSrcBase += pBltData->siSrc.cjAdvanceY;
    }
}