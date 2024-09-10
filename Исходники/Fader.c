HPALETTE CreateRoutine (HWND hwnd)
{
     HPALETTE hPalette ;
     
     lp.palVersion             = 0x0300 ;
     lp.palNumEntries          = 1 ;
     lp.palPalEntry[0].peRed   = 255 ;
     lp.palPalEntry[0].peGreen = 255 ;
     lp.palPalEntry[0].peBlue  = 255 ;
     lp.palPalEntry[0].peFlags = PC_RESERVED ;
   
     hPalette = CreatePalette (&lp) ;
     
     SetTimer (hwnd, ID_TIMER, 50, NULL) ;
     return hPalette ;
}