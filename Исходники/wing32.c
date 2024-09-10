/***********************************************************************
 *           WinGGetDIBPointer   (WING32.@)
 */
void * WINAPI WinGGetDIBPointer( HBITMAP hbmp, BITMAPINFO *bmi )
{
    DIBSECTION ds;

    if (GetObjectW( hbmp, sizeof(ds), &ds ) == sizeof(ds))
    {
        memcpy( &bmi->bmiHeader, &ds.dsBmih, sizeof(*bmi) );
        return ds.dsBm.bmBits;
    }
    return NULL;
}