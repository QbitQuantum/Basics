AUTHSSP_API void vncEditSecurity(HWND hwnd, HINSTANCE hInstance) {
	if (CheckAclUI()) {
		g_hInst = hInstance;
		// Convert ISecurityInformation implementation into property pages
		vncSecurityInfo* psi = 
			new vncSecurityInfo(L"UltraVNC Server", L"UltraVNC Server");
		psi->AddRef();
		
			HPROPSHEETPAGE hpsp[1];
			hpsp[0] = CreateSecurityPage(psi);
			psi->Release(); // does "delete this"!

			// Wrap the property page in a modal dialog by calling PropertySheet
			PROPSHEETHEADER psh;
			ZeroMemory(&psh, sizeof psh);
			psh.dwSize		= sizeof psh;
			psh.hwndParent	= hwnd;
			psh.pszCaption	= _T("UltraVNC Security Editor");
			psh.nPages		= sizeof hpsp / sizeof *hpsp;
			psh.phpage		= hpsp;
			
			PropertySheet(&psh);
			
	} else {
		MessageBox(NULL, _T("aclui.dll (function EditSecurity()) not available\n")
			_T("with this Operatingsystem/Servicepack.\n")
			_T("Use ACL import/export utility instead."),
			//sz_ID_WINVNC_ERROR,
			_T("Error"),
			MB_OK | MB_ICONEXCLAMATION);
	}
}