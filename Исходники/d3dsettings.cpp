//-----------------------------------------------------------------------------
// Name: BackBufferFormatChanged
// Desc: Respond to a change of selected back buffer format by rebuilding
//       the depth/stencil format list, multisample type list, and vertex
//       processing type list.
//-----------------------------------------------------------------------------
void CD3DSettingsDialog::BackBufferFormatChanged( void )
{
    D3DDeviceInfo* pDeviceInfo = (D3DDeviceInfo*)ComboBoxSelected( IDC_DEVICE_COMBO );
    D3DFORMAT adapterFormat = (D3DFORMAT)PtrToUlong( ComboBoxSelected( IDC_ADAPTERFORMAT_COMBO ) );
    D3DFORMAT backBufferFormat = (D3DFORMAT)PtrToUlong( ComboBoxSelected( IDC_BACKBUFFERFORMAT_COMBO ) );
    if( pDeviceInfo == NULL )
        return;

    for( UINT idc = 0; idc < pDeviceInfo->pDeviceComboList->Count(); idc++ )
    {
        D3DDeviceCombo* pDeviceCombo = (D3DDeviceCombo*)pDeviceInfo->pDeviceComboList->GetPtr(idc);
        if (pDeviceCombo->IsWindowed == m_d3dSettings.IsWindowed &&
            pDeviceCombo->AdapterFormat == adapterFormat &&
            pDeviceCombo->BackBufferFormat == backBufferFormat)
        {
            if( m_d3dSettings.IsWindowed )
                m_d3dSettings.pWindowed_DeviceCombo = pDeviceCombo;
            else
                m_d3dSettings.pFullscreen_DeviceCombo = pDeviceCombo;

            ComboBoxClear( IDC_DEPTHSTENCILBUFFERFORMAT_COMBO );
            if( m_pEnumeration->AppUsesDepthBuffer )
            {
                for( UINT ifmt = 0; ifmt < pDeviceCombo->pDepthStencilFormatList->Count(); ifmt++ )
                {
                    D3DFORMAT fmt = *(D3DFORMAT*)pDeviceCombo->pDepthStencilFormatList->GetPtr(ifmt);
                    ComboBoxAdd( IDC_DEPTHSTENCILBUFFERFORMAT_COMBO, (void*)fmt, 
                        D3DUtil_D3DFormatToString(fmt) );
                    if( fmt == m_d3dSettings.DepthStencilBufferFormat() )
                        ComboBoxSelect( IDC_DEPTHSTENCILBUFFERFORMAT_COMBO, (void*)fmt );
                }
                if (!ComboBoxSomethingSelected( IDC_DEPTHSTENCILBUFFERFORMAT_COMBO ) && 
                    ComboBoxCount( IDC_DEPTHSTENCILBUFFERFORMAT_COMBO ) > 0)
                {
                    ComboBoxSelectIndex( IDC_DEPTHSTENCILBUFFERFORMAT_COMBO, 0 );
                }
            }
            else
            {
                EnableWindow( GetDlgItem( m_hDlg, IDC_DEPTHSTENCILBUFFERFORMAT_COMBO ), false );
                ComboBoxAdd( IDC_DEPTHSTENCILBUFFERFORMAT_COMBO, NULL, TEXT("(not used)") );
                ComboBoxSelectIndex( IDC_DEPTHSTENCILBUFFERFORMAT_COMBO, 0 );
            }

            ComboBoxClear( IDC_VERTEXPROCESSING_COMBO );
            for( UINT ivpt = 0; ivpt < pDeviceCombo->pVertexProcessingTypeList->Count(); ivpt++ )
            {
                VertexProcessingType vpt = *(VertexProcessingType*)pDeviceCombo->pVertexProcessingTypeList->GetPtr(ivpt);
                ComboBoxAdd( IDC_VERTEXPROCESSING_COMBO, (void*)vpt, VertexProcessingTypeToString(vpt) );
                if( vpt == m_d3dSettings.GetVertexProcessingType() )
                    ComboBoxSelect( IDC_VERTEXPROCESSING_COMBO, (void*)vpt );
            }
            if (!ComboBoxSomethingSelected( IDC_VERTEXPROCESSING_COMBO ) && 
                ComboBoxCount( IDC_VERTEXPROCESSING_COMBO ) > 0)
            {
                ComboBoxSelectIndex( IDC_VERTEXPROCESSING_COMBO, 0 );
            }

            ComboBoxClear( IDC_PRESENTINTERVAL_COMBO );
            for( UINT ipi = 0; ipi < pDeviceCombo->pPresentIntervalList->Count(); ipi++ )
            {
                UINT pi = *(UINT*)pDeviceCombo->pPresentIntervalList->GetPtr(ipi);
                ComboBoxAdd( IDC_PRESENTINTERVAL_COMBO, UlongToPtr( pi ), PresentIntervalToString(pi) );
                if( pi == m_d3dSettings.PresentInterval() )
                    ComboBoxSelect( IDC_PRESENTINTERVAL_COMBO, UlongToPtr( pi ) );
            }
            if (!ComboBoxSomethingSelected( IDC_PRESENTINTERVAL_COMBO ) && 
                ComboBoxCount( IDC_PRESENTINTERVAL_COMBO ) > 0)
            {
                ComboBoxSelectIndex( IDC_PRESENTINTERVAL_COMBO, 0 );
            }

            break;
        }
    }
}