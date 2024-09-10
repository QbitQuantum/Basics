//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
	CDXUTComboBox* pComboBox = NULL;
	CDXUTComboBox* pAABBLevelComboBox = NULL;
    switch( nControlID )
    {
    case IDC_TOGGLEFULLSCREEN:
        DXUTToggleFullScreen(); break;
    case IDC_TOGGLEWARP:
        DXUTToggleWARP(); break;
    case IDC_TOGGLEREF:
        DXUTToggleREF(); break;
    case IDC_CHANGEDEVICE:
        g_SettingsDlg.SetActive( !g_SettingsDlg.IsActive() ); break;  
	case IDC_SCENERASTERIZER_MODE:
		    //CDXUTComboBox* pComboBox = NULL;
            pComboBox = ( CDXUTComboBox* )pControl;
            g_eSceneRasterizerMode = ( UINT )PtrToInt( pComboBox->GetSelectedData() );
            break;
	case IDC_AABBSUBLEVEL:
        pAABBLevelComboBox = ( CDXUTComboBox* )pControl;
        g_CurrentAABBLevel = ( UINT )PtrToInt( pAABBLevelComboBox->GetSelectedData() );
        break;
    }
}