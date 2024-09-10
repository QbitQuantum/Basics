//-----------------------------------------------------------------------------
// Name: UpdateCubeData()
// Desc: 
//-----------------------------------------------------------------------------
void UpdateSpiralData( HWND hWnd )
{
    char str[256];

    GetDlgItemTextA( hWnd, IDC_EDIT_SPIRAL_WIDTH, str, 256 );
    Settings->m_fBrush_Spiral_Width = (float)atof( str );

    GetDlgItemTextA( hWnd, IDC_EDIT_SPIRAL_HEIGHT, str, 256 );
    Settings->m_fBrush_Spiral_Height = (float)atof( str );

    GetDlgItemTextA( hWnd, IDC_EDIT_SPIRAL_NUMSTEPS, str, 256 );
    Settings->m_iBrush_Spiral_NumSteps = (int)atof( str );

    GetDlgItemTextA( hWnd, IDC_EDIT_SPIRAL_ADDTOFIRST, str, 256 );
    Settings->m_fBrush_Spiral_AddToFirst = (float)atof( str );

    GetDlgItemTextA( hWnd, IDC_EDIT_SPIRAL_DEGREES, str, 256 );
    Settings->m_fBrush_Spiral_Degrees = (float)atof( str );

    GetDlgItemTextA( hWnd, IDC_EDIT_SPIRAL_INNERRADIUS, str, 256 );
    Settings->m_fBrush_Spiral_InnerRadius = (float)atof( str );

    if( Settings->m_iBrush_Spiral_NumSteps <= 0 )
        Settings->m_iBrush_Spiral_NumSteps = 1;
}