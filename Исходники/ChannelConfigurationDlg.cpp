int CChannelConfigurationDlg::nDisplayProtocolSettings(int nChannelIndex)
{
    if ( m_eBusType == LIN )
    {
        BOOL bOverrite = m_ouFlexrayChannelConfig[nChannelIndex].m_ouLinParams.m_bOverWriteSettings;

        ((CButton*)GetDlgItem(IDC_CHECK_OVERWRITE_SETTINGS))->SetCheck(bOverrite);

        CComboBox* pomCombo = (CComboBox*)GetDlgItem(IDC_COMBO_LIN_PROTOCOL);
        pomCombo->EnableWindow(bOverrite);

        GetDlgItem(IDC_EDIT_LIN_BAUDRATE)->EnableWindow(bOverrite);

        m_nLinBaudRate = 19200;
        pomCombo->SetCurSel(0);
        for ( int i = 0 ; i < ( sizeof(sg_LINPROTOCOL_BAUD)/ sizeof(sg_LINPROTOCOL_BAUD[0])); i++ )
        {
            if ( m_ouFlexrayChannelConfig[nChannelIndex].m_ouLinParams.m_strProtocolVersion == sg_LINPROTOCOL_BAUD[i].m_strProtocol )
            {
                pomCombo->SetCurSel(i);
                if ( bOverrite == false )
                {
                    m_nLinBaudRate = sg_LINPROTOCOL_BAUD[i].m_nBaudRate;
                }
                else
                {
                    m_nLinBaudRate =  m_ouFlexrayChannelConfig[nChannelIndex].m_ouLinParams.m_nBaudRate;
                }

                break;
            }
        }
        ((CButton*)GetDlgItem(IDC_ENABLE_MASTER_MODE))->SetCheck(m_ouFlexrayChannelConfig[nChannelIndex].m_ouLinParams.m_bIsMasterMode);
        UpdateData(FALSE);
    }
    return 0;
}