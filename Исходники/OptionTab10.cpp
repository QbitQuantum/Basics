BOOL COptionTab10::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
  EnableToolTips(true);     // TOOL TIPS

  /* hide password */
  CString st;
  GetDlgItemText(IDC_prox,st);
  if (st.Find('@')>=0) {
    m_ctl_pwdhide.SetCheck(1);
    OnPwdhide();
  } else {
    m_ctl_pwdhide.SetCheck(0);
    OnPwdhide();
  }

  if (LANG_T(-1)) {    // Patcher en français
    SetDlgItemTextCP(this, IDC_proxyconfigure,LANG(LANG_I47b)); // "Configurer"
    SetDlgItemTextCP(this, IDC_ftpprox,LANG(LANG_I47c));
    SetDlgItemTextCP(this, IDC_PWDHIDE,LANG_HIDEPWD);  /* Hide password */
  }  

  // mode modif à la volée
  if (modify==1) {
    GetDlgItem(IDC_prox           ) ->ModifyStyle(0,WS_DISABLED);
    GetDlgItem(IDC_portprox       ) ->ModifyStyle(0,WS_DISABLED);
    GetDlgItem(IDC_proxyconfigure ) ->ModifyStyle(0,WS_DISABLED);
    GetDlgItem(IDC_proxtitle      ) ->ModifyStyle(0,WS_DISABLED);
    GetDlgItem(IDC_ftpprox        ) ->ModifyStyle(0,WS_DISABLED);
  } else {
    GetDlgItem(IDC_prox           ) ->ModifyStyle(WS_DISABLED,0);
    GetDlgItem(IDC_portprox       ) ->ModifyStyle(WS_DISABLED,0);
    GetDlgItem(IDC_proxyconfigure ) ->ModifyStyle(WS_DISABLED,0);
    GetDlgItem(IDC_proxtitle      ) ->ModifyStyle(WS_DISABLED,0);
    GetDlgItem(IDC_ftpprox        ) ->ModifyStyle(WS_DISABLED,0);
  }

  CString str;
  GetDlgItemText(IDC_prox,str);
  m_ctl_prox.ResetContent();
  m_ctl_prox.AddString("");

  HKEY phkResult;
  if (RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",0,KEY_READ,&phkResult)==ERROR_SUCCESS) {
    DWORD type=0;
    DWORD datasize=1000;
    char data[1024];
    data[0]='\0';
    if (RegQueryValueEx(phkResult,"ProxyServer",0,&type,(unsigned char*)&data,&datasize)==ERROR_SUCCESS) {
      if (datasize) {
        char* a=strchr(data,':');
        if (a)
          *a='\0';
        m_ctl_prox.AddString(data);
      }
    }
    RegCloseKey(phkResult);
  }
  SetDlgItemTextCP(this, IDC_prox,str);

  // Do not search for a proxy everytime
  CWinApp* pApp = AfxGetApp();
  if (pApp->GetProfileInt("Interface","FirstProxySearch",0) != 1) {
    pApp->WriteProfileInt("Interface","FirstProxySearch",1);
    
    // Launch proxy name search
    int i=0;
    WSAAsyncGetHostByName(this->m_hWnd,wm_ProxySearch+i,(ProxyDetectName[i]="proxy")   ,this->ProxyDetectBuff[i],sizeof(this->ProxyDetectBuff[i])); i++;
    WSAAsyncGetHostByName(this->m_hWnd,wm_ProxySearch+i,(ProxyDetectName[i]="www")     ,this->ProxyDetectBuff[i],sizeof(this->ProxyDetectBuff[i])); i++;
    WSAAsyncGetHostByName(this->m_hWnd,wm_ProxySearch+i,(ProxyDetectName[i]="ns")      ,this->ProxyDetectBuff[i],sizeof(this->ProxyDetectBuff[i])); i++;
    WSAAsyncGetHostByName(this->m_hWnd,wm_ProxySearch+i,(ProxyDetectName[i]="web")     ,this->ProxyDetectBuff[i],sizeof(this->ProxyDetectBuff[i])); i++;
    WSAAsyncGetHostByName(this->m_hWnd,wm_ProxySearch+i,(ProxyDetectName[i]="ntserv")  ,this->ProxyDetectBuff[i],sizeof(this->ProxyDetectBuff[i])); i++;
    WSAAsyncGetHostByName(this->m_hWnd,wm_ProxySearch+i,(ProxyDetectName[i]="gate")    ,this->ProxyDetectBuff[i],sizeof(this->ProxyDetectBuff[i])); i++;
    WSAAsyncGetHostByName(this->m_hWnd,wm_ProxySearch+i,(ProxyDetectName[i]="gateway") ,this->ProxyDetectBuff[i],sizeof(this->ProxyDetectBuff[i])); i++;
    WSAAsyncGetHostByName(this->m_hWnd,wm_ProxySearch+i,(ProxyDetectName[i]="firewall"),this->ProxyDetectBuff[i],sizeof(this->ProxyDetectBuff[i])); i++;
    WSAAsyncGetHostByName(this->m_hWnd,wm_ProxySearch+i,(ProxyDetectName[i]="cache")   ,this->ProxyDetectBuff[i],sizeof(this->ProxyDetectBuff[i])); i++;
    
  }
  
  return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}