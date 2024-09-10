void CDialogVolumeAddNew::OnOK(wxCommandEvent &e)
{
  wxString sCopyFrom = m_pChoiceKit->GetStringSelection();
  m_sName = m_pText->GetValue();
  bool bError = true;
  {
    wxBusyCursor xxx;
    if(m_pVolumes->Create(sCopyFrom,m_sName))
    {
      bError = false;
      e.Skip();
    }
  }

  if(bError) // we want wxBusyCursor out of scope here
  {
    m_sName.Empty();
    mainApp::ShowError(m_pVolumes->GetLastError(),this);
  }
}