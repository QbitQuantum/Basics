/*
 * @implemented
 *
 */
BOOL
WINAPI
GetCurrentPositionEx(HDC hdc,
                     LPPOINT lpPoint)
{
    PDC_ATTR Dc_Attr;

    if (!GdiGetHandleUserData((HGDIOBJ) hdc, GDI_OBJECT_TYPE_DC, (PVOID) &Dc_Attr)) return FALSE;

    if ( lpPoint )
    {
        if ( Dc_Attr->ulDirty_ & DIRTY_PTLCURRENT ) // have a hit!
        {
            lpPoint->x = Dc_Attr->ptfxCurrent.x;
            lpPoint->y = Dc_Attr->ptfxCurrent.y;
            DPtoLP ( hdc, lpPoint, 1);          // reconvert back.
            Dc_Attr->ptlCurrent.x = lpPoint->x; // save it
            Dc_Attr->ptlCurrent.y = lpPoint->y;
            Dc_Attr->ulDirty_ &= ~DIRTY_PTLCURRENT; // clear bit
        }
        else
        {
            lpPoint->x = Dc_Attr->ptlCurrent.x;
            lpPoint->y = Dc_Attr->ptlCurrent.y;
        }
    }
    else
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }
    return TRUE;
}