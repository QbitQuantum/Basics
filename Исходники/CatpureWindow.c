static HPALETTE GetSystemPalette(HDC hdc)
{
   static HPALETTE hPal = 0;	// handle to a palette
   HANDLE hLogPal;				// handle to a logical palette
   LOGPALETTE *pLogPal;			// pointer to a logical palette
   int nColors;					// number of colors

   // Find out how many palette entries we want.
   nColors = PalEntriesOnDevice(hdc);   

   // Allocate room for the palette and lock it.
   hLogPal = GlobalAlloc(GHND, sizeof(LOGPALETTE) + nColors * sizeof(PALETTEENTRY));

   // if we didn't get a logical palette, return NULL
   if (!hLogPal) return NULL;

   // get a pointer to the logical palette
   pLogPal = (LPLOGPALETTE)GlobalLock(hLogPal);

   // set some important fields
   pLogPal->palVersion = PALVERSION;
   pLogPal->palNumEntries = nColors;

   //Copy the current system palette into our logical palette */
   GetSystemPaletteEntries(hdc, 0, nColors, (LPPALETTEENTRY)(pLogPal->palPalEntry));

   // Go ahead and create the palette.  Once it's created,
   hPal = CreatePalette(pLogPal);

   // clean up
   GlobalUnlock(hLogPal);
   GlobalFree(hLogPal);

   return hPal;
}