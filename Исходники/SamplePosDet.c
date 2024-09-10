/*===========================================================================
===========================================================================*/
void SamplePosDet_Printf( CSamplePosDet *pMe, int nLine, int nCol, AEEFont fnt, uint32 dwFlags, 
                                const char *szFormat, ... )
{
   char              szBuf[64];
   va_list args;
   va_start( args, szFormat );

   (void)VSNPRINTF( szBuf, 64, szFormat, args );

   va_end( args );
   xDisplay( (AEEApplet *)pMe, nLine, nCol, fnt, dwFlags, szBuf );
}