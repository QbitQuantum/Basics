/******************************************************************
 *                        Setup                                   *
 ******************************************************************/
BOOL CALLBACK SetupMewDlgProc( HWND   hDlg,
			       UINT   uiMsg,
			       WPARAM wParam,
			       LPARAM lParam )
{
  BOOL fRet = TRUE;
  char *pt;
  char szFileName[MAX_PATH];
  OPENFILENAME of;

  switch ( uiMsg ){
  case WM_INITDIALOG:
    CheckRadioButton( hDlg, IDC_POP_APOP, IDC_POP_APOP, IDC_POP_APOP );
    ImmAssociateContext(GetDlgItem(hDlg, IDC_USERNAME), (HIMC)NULL);
    ImmAssociateContext(GetDlgItem(hDlg, IDC_MAILADDRESS), (HIMC)NULL);
    ImmAssociateContext(GetDlgItem(hDlg, IDC_SMTPSERVER), (HIMC)NULL);
    ImmAssociateContext(GetDlgItem(hDlg, IDC_POPSERVER), (HIMC)NULL);
    ImmAssociateContext(GetDlgItem(hDlg, IDC_POPUSER), (HIMC)NULL);
    SetDlgItemText(hDlg, IDC_CONFIGFILE, (LPCTSTR)lParam);
    ShowWindow( hDlg, SW_SHOW );
    UpdateWindow( hDlg );
    break;

  case WM_COMMAND:
    switch ( GET_WM_COMMAND_ID( wParam, lParam ) ){
    case IDC_FILESELECT:
	memset(szFileName, 0, sizeof(szFileName));
	memset(&of, 0, sizeof(of));
	of.lStructSize = sizeof(of);
	of.hwndOwner   = hDlg;
	of.lpstrFilter = "All Files(*.*)\0*.*\0";
	of.lpstrFile   = szFileName;
	of.nMaxFile    = MAX_PATH;
	of.Flags       = OFN_FILEMUSTEXIST|OFN_LONGNAMES|OFN_PATHMUSTEXIST;
	of.lpstrTitle  = "Select .emacs or .mew file.";
	if (GetOpenFileName(&of))
	    SetDlgItemText(hDlg, IDC_CONFIGFILE, szFileName);
	break;
    case IDOK:
      GetDlgItemText( hDlg, IDC_USERNAME, szUserFullName, sizeof(szUserFullName) );
      if ( ! strcmp( szUserFullName, "" ) ){
	BilErrorMessageBox( "User Name is empty.",
			    "User Name の欄が空白です" );
	break;
      }
      GetDlgItemText( hDlg, IDC_MAILADDRESS, szMailAddress, sizeof(szMailAddress) );
      if ( ! strcmp( szMailAddress, "" ) ){
	BilErrorMessageBox( "Mail Address is empty.",
			    "Mail Address の欄が空白です" );
	break;
      }
      pt = strchr( szMailAddress, '@' );
      if ( pt != NULL ){
	*pt = '\0';
	if ( *(pt+1) != '\0' ){
	  strcpy(szUserName,szMailAddress);
	  strcpy(szDomainName, pt+1 );
	  *pt = '@';
	} /* if ( *(pt+1) != '\0' ){ */
      } else {
	BilErrorMessageBox( "Invalid mail address.",
			    "メールアドレスが不正です" );
	SetDlgItemText( hDlg, IDC_MAILADDRESS, "" );
	fRet = FALSE;
	break;
      } /* if ( pt != NULL ){ */
      GetDlgItemText( hDlg, IDC_SMTPSERVER, szSmtpserver, sizeof(szSmtpserver) );
      if ( ! strcmp( szSmtpserver, "" ) ){
	BilErrorMessageBox( "SMTP Server is empty.",
			    "SMTP Server の欄が空白です" );
	break;
      }
      GetDlgItemText( hDlg, IDC_POPSERVER, szPopserver, sizeof(szPopserver) );
      if ( ! strcmp( szPopserver, "" ) ){
	BilErrorMessageBox( "POP3 Server is empty.",
			    "POP3 Server の欄が空白です" );
	break;
      }
      GetDlgItemText( hDlg, IDC_POPUSER, szPopUser, sizeof(szPopUser) );
      if ( ! strcmp( szPopUser, "" ) ){
	BilErrorMessageBox( "POP3 Username is empty.",
			    "POP3 Username の欄が空白です" );
	break;
      }
      if (IsDlgButtonChecked( hDlg, IDC_POP_APOP ) != BST_CHECKED){
	  fApopAuth = FALSE;
      }
      GetDlgItemText(hDlg, IDC_CONFIGFILE,
		     szConfFileName, sizeof(szConfFileName));
      EndDialog( hDlg, 0 );
      break;
    case IDCANCEL:
      fRet = FALSE;
      EndDialog( hDlg, -1 );
      break;
    }
  default:
    fRet = FALSE;
    break;
  } /* switch ( uiMsg ){ */
  
  return ( fRet );
}