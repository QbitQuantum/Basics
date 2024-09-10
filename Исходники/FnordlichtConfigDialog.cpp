ATMO_BOOL CFnordlichtConfigDialog::ExecuteCommand(HWND hControl,int wmId, int wmEvent) 
{
    switch(wmId) {
        case IDOK: {
           int numChannels;
           if(!this->GetEditInt(m_hEditNumChannels,numChannels)) {
               return ATMO_TRUE; 
           }
           if((numChannels < 1) || (numChannels>255)) {
               MessageBox(this->m_hDialog,"Number of channels out of range 1..255","Error",MB_ICONERROR | MB_OK);
               return ATMO_TRUE;
           }
           m_pConfig->setFnordlicht_Amount( numChannels );

           int comportSel = ComboBox_GetCurSel(getDlgItem(IDC_COMPORT));
           m_pConfig->setComport(comportSel + 1);

           EndDialog(this->m_hDialog, wmId);
           break;
        }

        case IDCANCEL: {
           EndDialog(this->m_hDialog, wmId);
           break;
        }

       default:
           return ATMO_FALSE;

    }

    return ATMO_TRUE;
}