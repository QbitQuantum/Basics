BOOL CEnterOptionsNameDlg::OnInitDialog() {
  __super::OnInitDialog();

  CComboBox *cb = getNameCombo();
  const StringArray names = Options::getExistingNames();
  for(size_t i = 0; i < names.size(); i++) {
    cb->AddString(names[i].cstr());
  }
  cb->SetFocus();
  if((cb->GetCount() == 0) || (m_name.GetLength() == 0)) {
    cb->SetCurSel(0);
  } else {
    cb->SetCurSel((int)names.getFirstIndex((LPCTSTR)m_name));
  }
  return false;
}