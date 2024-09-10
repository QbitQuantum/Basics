/* CalcFilterXlat:
 * Given a palette, writes all indices  of the xlat.
 * Each index is the best fit for the given color at the original palette
 * color's lightness.  For a golden filter, you'd give gold as the color.
 */
void CalcFilterXlat(HPALETTE hPalette, xlat* pXlat, COLORREF crMix)
{
	int i;
	PALETTEENTRY pe; /* i want to be able to see it always in this function */

	if (!hPalette || !pXlat)
		return;

	for (i = 0; i < NUM_COLORS; i++)
	{
		BYTE byLightness;
		LONG l;
		GetPaletteEntries(hPalette, i, 1, &pe);

		byLightness = GetRGBLightness(&pe);

		l = ((LONG)GetRValue(crMix))*((LONG)byLightness)/256;

		pe.peRed = (BYTE)(l & 0xFF);

		l = ((LONG)GetGValue(crMix))*((LONG)byLightness)/256;
		
		pe.peGreen = (BYTE)(l & 0xFF);

		l = ((LONG)GetBValue(crMix))*((LONG)byLightness)/256;
		
		pe.peBlue = (BYTE)(l & 0xFF);

		pXlat->entry[i] = GetNearestPaletteIndex(hPalette, RGB(pe.peRed, pe.peGreen, pe.peBlue));
	}
}