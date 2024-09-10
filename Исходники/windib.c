/* Called in response to WM_ACTIVATE messages
 */
void Win_Focus(int on)
{
    HDC hdc;

    /* Right now, the only thing we care about is palette manipulation */
    if(!sys_palette_p)
        return;

    hdc = GetDC(Win_Window);
    if(on)
    {
        PALETTEENTRY entries[NUM_COLORS];

        /* Save the current system palette */
        GetSystemPaletteEntries(hdc, 0, NUM_COLORS, entries);
        SetPaletteEntries(sys_palette, 0, NUM_COLORS, entries);

/* Set our palette as the logical palette */
#ifdef PRIVATE_CMAP
        /* This is more trouble than it's worth.  It fries system colors */
        SetSystemPaletteUse(hdc, SYSPAL_NOSTATIC);
#endif
        SelectPalette(hdc, our_palette, false);
        RealizePalette(hdc);
        InvalidateRect(Win_Window, NULL, 0);
    }
    else
    {
        /* Set the system palette and reset colors */
        SelectPalette(hdc, sys_palette, false);
        RealizePalette(hdc);
#ifdef PRIVATE_CMAP
        SetSystemPaletteUse(hdc, SYSPAL_STATIC);
#endif
    }
    ReleaseDC(hdc, Win_Window);
}