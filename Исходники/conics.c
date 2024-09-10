/***************************************************************************
 * DoSetArcDirection - Win32 to Win16 Metafile Converter Entry Point
 **************************************************************************/
BOOL WINAPI DoSetArcDirection(PLOCALDC pLocalDC, INT iArcDirection)
{
        pLocalDC->iArcDirection = iArcDirection ;

        return(SetArcDirection(pLocalDC->hdcHelper, iArcDirection) != 0);
}