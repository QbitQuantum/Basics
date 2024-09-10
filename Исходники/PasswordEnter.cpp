LRESULT CPasswordEnter::OnClickedOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	TCHAR szPassword[_MAX_PATH] = {0};
	GetDlgItemText(IDC_PASSWORD_OPEN, szPassword, _MAX_PATH); 
	CStdString sEnteredPassword(szPassword);

	TCHAR szModifyPassword[_MAX_PATH] = {0};
	GetDlgItemText(IDC_PASSWORD_MODIFY, szModifyPassword, _MAX_PATH); 
	m_ModifyPassword = szModifyPassword;

	TCHAR szRestrictionPassword[_MAX_PATH] = {0};
	GetDlgItemText(IDC_PASSWORD_RESTRICT, szRestrictionPassword, _MAX_PATH); 
	m_RestrictionPassword = szRestrictionPassword;

	if(m_enabledOpenPassword && sEnteredPassword.empty())
	{
		ShowMessage(NULL, _T("Please enter the open password to continue"), WsOK, WsProtect, WsErrorIcon, L"", d2h_password_verify, LOG_LOCATION);
		return 0;
	}

	if(m_enabledModifyPassword && m_ModifyPassword.empty())
	{
		ShowMessage(NULL, _T("Please enter the modify password to continue"), WsOK, WsProtect, WsErrorIcon, L"", d2h_password_verify, LOG_LOCATION);
		return 0;
	}

	if(m_enabledRestrictionPassword && m_RestrictionPassword.empty())
	{
		ShowMessage(NULL, _T("Please enter the restriction password to continue"), WsOK, WsProtect, WsErrorIcon, L"", d2h_password_verify, LOG_LOCATION);
		return 0;
	}

	if(m_bVerifyUsingMD4)
	{
		try
		{
			WSCRYPTLib::IWSPwdEncrypterPtr crypt;
			HRESULT hr = crypt.CreateInstance(_PROGID_WSCrypto_WProf);
			if(FAILED(hr))
				throw Workshare::ClassNotFoundException(_T(_PROGID_WSCrypto_WProf), _T("Failed to create an instance of the Workshare Encryption library. Please run the configuration assistant"));

			_bstr_t bstrPassword = sEnteredPassword.c_str();
			crypt->MD4Encrypt(&bstrPassword.GetBSTR());
			sEnteredPassword = bstrPassword;
		}
		catch (const Workshare::Exception&)
		{
			TCHAR szBuffer[80];
			::LoadString(_AtlBaseModule.m_hInstResource, MSG_ENCRYPT_FAILED, szBuffer, 80);
			ShowMessage(NULL, szBuffer, WsOK, WsProtect, WsErrorIcon, L"", d2h_password_verify, LOG_LOCATION);
		}
		catch(...)
		{
			TCHAR szBuffer[80];
			::LoadString(_AtlBaseModule.m_hInstResource, MSG_ENCRYPT_FAILED, szBuffer, 80);
			ShowMessage(NULL, szBuffer, WsOK, WsProtect, WsErrorIcon, L"", d2h_password_verify, LOG_LOCATION);
			unexpected();
		}
	}

	if(m_verifyCurrent && (sEnteredPassword != m_OpenPassword))
	{
		TCHAR szBuffer[80];
		::LoadString(_AtlBaseModule.m_hInstResource, MSG_PASSWORD_INCORRECT, szBuffer, 80);
		ShowMessage(NULL, szBuffer, WsOK, WsProtect, WsErrorIcon, L"", d2h_password_verify, LOG_LOCATION);
	}
	else
	{
		m_OpenPassword = szPassword;
		EndDialog(wID);
	}   
	return 0;
}