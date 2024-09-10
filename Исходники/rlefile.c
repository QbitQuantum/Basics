BOOL RleFile_Draw(RLEFILE *prle, HDC hdc, int iFrame, int x, int y)
{
    BOOL f;

    if (prle == NULL || prle->pMovie == NULL)
        return FALSE;

    if (prle->hpal)
    {
        SelectPalette(hdc, prle->hpal, FALSE);
        RealizePalette(hdc);
    }

    if (f = RleFile_Seek(prle, iFrame))
    {
        if (prle->cbFrame > 0)
        {
            StretchDIBits(hdc,
                    x, y, prle->Width, prle->Height,
                    0, 0, prle->Width, prle->Height,
                    prle->pFrame, (LPBITMAPINFO)&prle->bi,
                    DIB_RGB_COLORS, SRCCOPY);
        }
    }

    return f;
}