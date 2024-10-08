DWORD
main(
    int argc,
    char *argv[]
    )
{
    BOOL Success;
    int i;
    HPALETTE hPalette;
    LOGPALETTE *Palette;
    HANDLE hgo;
    CONSOLE_GRAPHICS_BUFFER_INFO cgbi;

    Palette = LocalAlloc(LMEM_FIXED,
                    sizeof(LOGPALETTE) + 256 * sizeof(PALETTEENTRY));

    Palette->palNumEntries = (WORD) 256;
    Palette->palVersion    = 0x300;

    /* Fill in the palette entries from the DIB color table and
     * create a logical color palette.
     */

    for (i = 0; i < 256; i++) {
        Palette->palPalEntry[i].peRed   = 255-i;
        Palette->palPalEntry[i].peGreen = 255-i;
        Palette->palPalEntry[i].peBlue  = 255-i;
        Palette->palPalEntry[i].peFlags = (BYTE)0;
    }

    hPalette = CreatePalette(Palette);
    if (hPalette==NULL) {
        printf("first CreatePalette failed\n");
        printf("last error is %x\n",GetLastError());
    }

#if 0
call
HANDLE
APIENTRY
CreateConsoleScreenBuffer(
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwFlags,  == CONSOLE_GRAPHICS_BUFFER
    PVOID lpScreenBufferData == pCONSOLE_GRAPHICS_BUFFER_INFO
    );
typedef struct _CONSOLE_GRAPHICS_BUFFER_INFO {
    DWORD dwBitMapInfoLength;
    LPBITMAPINFO lpBitMapInfo;
    DWORD dwUsage;
    HANDLE hMutex;
    PVOID lpBitMap;
} CONSOLE_GRAPHICS_BUFFER_INFO, *PCONSOLE_GRAPHICS_BUFFER_INFO;


#define CONSOLE_GRAPHICS_BUFFER  2
#endif
    hgo = CreateConsoleScreenBuffer(MAXIMUM_ALLOWED, 0, NULL,
            CONSOLE_GRAPHICS_BUFFER, &cgbi);
    if (hgo == NULL) {
        DbgPrint("CreateConsoleScreenBuffer failed\n");
        return FALSE;
    }
    Success = SetConsolePalette(hgo,
                                hPalette,
                                SYSPAL_NOSTATIC
                               );
    if (!Success) {
        printf("first SetConsolePalette failed\n");
    }
    printf("palette should be different\n");
    Sleep(5000);
    DeleteObject(hPalette);

    /* Fill in the palette entries from the DIB color table and
     * create a logical color palette.
     */

    for (i = 0; i < 16; i++) {
        memcpy(&Palette->palPalEntry[i],
               MyPalette,
               64
              );
    }

    hPalette = CreatePalette(Palette);
    if (hPalette==NULL) {
        printf("first CreatePalette failed\n");
    }

    Success = SetConsolePalette(hgo,
                                hPalette,
                                SYSPAL_STATIC
                               );
    if (!Success) {
        printf("second SetConsolePalette failed\n");
    }
    printf("palette should be different\n");
    Sleep(5000);
    DeleteObject(hPalette);

    printf( "TCURSOR: Exiting Test Program\n" );
    return TRUE;
}