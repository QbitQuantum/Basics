void RestorePalette(HDC hdc, HPALETTE hOldPal)
{
    SelectPalette(hdc, hOldPal, TRUE);
}