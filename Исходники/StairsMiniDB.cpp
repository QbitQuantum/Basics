//-----------------------------------------------------------------------------
// Name: UpdateCubeData()
// Desc: 
//-----------------------------------------------------------------------------
void UpdateStairsData( HWND hWnd )
{
    char str[256];

    GetDlgItemTextA( hWnd, IDC_EDIT_STEP_DEPTH, str, 256 );
    Settings->m_fBrush_Stairs_Depth = (float)atof( str );

    GetDlgItemTextA( hWnd, IDC_EDIT_STEP_WIDTH, str, 256 );
    Settings->m_fBrush_Stairs_Width = (float)atof( str );

    GetDlgItemTextA( hWnd, IDC_EDIT_STEP_HEIGHT, str, 256 );
    Settings->m_fBrush_Stairs_Height = (float)atof( str );

    GetDlgItemTextA( hWnd, IDC_EDIT_STEP_NUMSTEPS, str, 256 );
    Settings->m_iBrush_Stairs_NumSteps = (int)atof( str );

    GetDlgItemTextA( hWnd, IDC_EDIT_STEP_ADDTOFIRST, str, 256 );
    Settings->m_fBrush_Stairs_AddToFirst = (float)atof( str );

    if( Settings->m_iBrush_Stairs_NumSteps <= 0 )
        Settings->m_iBrush_Stairs_NumSteps = 1;
}