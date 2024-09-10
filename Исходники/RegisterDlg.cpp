afx_msg void CRegisterDlg::OnOK()
  {
      CString user,key,appname,buffer;
      BOOL bOK = TRUE;

      ((CEdit*)GetDlgItem(IDC_EDIT_USERNAME))->GetWindowText(user);
      ((CEdit*)GetDlgItem(IDC_EDIT_KEY))->GetWindowText(key);

      if(CArmadillo::InstallKeyCode(user,key))
          buffer.LoadString(IDS_TRIAL_KEY_INSTALLED);
      else
      {
          buffer.LoadString(IDS_TRIAL_KEY_INVALID);
          bOK = FALSE;
      }
      appname.LoadString(IDS_APP_NAME);
      MessageBox(buffer,appname,MB_OK | MB_ICONINFORMATION);

      if(bOK)
          CDialog::OnOK();
      else
      {
          CEdit *pUserName = (CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
          CEdit *pKey = (CEdit*)GetDlgItem(IDC_EDIT_KEY);
          ASSERT(pKey && pUserName);

          pUserName->SetWindowText("");
          pKey->SetWindowText("");

          pUserName->SetFocus();
      }
  }