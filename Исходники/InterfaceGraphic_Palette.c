__declspec( dllexport ) long InterfaceGraphic_RealizePalette ( HDC hdc, HPALETTE hPal, BOOL fBkg, BOOL fUseStatic ) {

    int i;
    long retVal = 0;

    if ( fUseStatic ) {

        if ( !s_sysUse )

            for ( i = 0; i < NB_STATIC_COLORS; ++i ) s_sysPal[ i ] = GetSysColor ( s_sysPalIdx[ i ] );

        SetSystemPaletteUse ( hdc, fBkg ? SYSPAL_STATIC : SYSPAL_NOSTATIC );

        if (  UnrealizeObject ( hPal ) && SelectPalette ( hdc, hPal, fBkg )  ) retVal = RealizePalette ( hdc );

        if ( fBkg ) {

            SetSysColors ( NB_STATIC_COLORS, s_sysPalIdx, s_sysPal );
            s_sysUse = FALSE;

        } else {

            SetSysColors ( NB_STATIC_COLORS, s_sysPalIdx, s_sysPalBW );
            s_sysUse = TRUE;

        }  // end else

        PostMessage ( HWND_BROADCAST, WM_SYSCOLORCHANGE, 0, 0 );

    } else {

        SelectPalette ( hdc, hPal, FALSE );
        retVal = RealizePalette ( hdc );

    }  // end else

    return retVal;
}  // end RealizePaletteNow