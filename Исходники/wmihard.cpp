void get_wmi_init()
{
	static bool isinit = false;
	if (isinit)
	{
		return;
	}
	isinit = true;
	HRESULT hres =  CoInitializeSecurity(
						NULL,
						-1,                          // COM authentication
						NULL,                        // Authentication services
						NULL,                        // Reserved
						RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
						RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
						NULL,                        // Authentication info
						EOAC_NONE,                   // Additional capabilities
						NULL                         // Reserved
					);

	if (FAILED(hres))
	{
		_com_issue_error(hres);
	}
}