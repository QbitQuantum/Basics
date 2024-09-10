// Sets pdwCount to the number of tiles that we wish to show at this time.
// Sets pdwDefault to the index of the tile which should be used as the default.
// The default tile is the tile which will be shown in the zoomed view by default. If
// more than one provider specifies a default the last used cred prov gets to pick
// the default. If *pbAutoLogonWithDefault is TRUE, LogonUI will immediately call
// GetSerialization on the credential you've specified as the default and will submit
// that credential for authentication without showing any further UI.
HRESULT MultiotpProvider::GetCredentialCount(
    _Out_ DWORD *pdwCount,
    _Out_ DWORD *pdwDefault,
    _Out_ BOOL *pbAutoLogonWithDefault)
{
	if (DEVELOP_MODE) PrintLn("MultiotpProvider::GetCredentialCount");

    *pdwDefault = CREDENTIAL_PROVIDER_NO_DEFAULT;
    *pbAutoLogonWithDefault = FALSE;

    if (_fRecreateEnumeratedCredentials)
    {
        _fRecreateEnumeratedCredentials = false;
        _ReleaseEnumeratedCredentials();
        _CreateEnumeratedCredentials();
    }
	DWORD dwUserCount = 1;
	HRESULT hr;

	if (_pCredProviderUserArray != nullptr) {
		hr = _pCredProviderUserArray->GetCount(&dwUserCount);
		if (hr == 0) {
			if (DEVELOP_MODE) PrintLn("MultiotpProvider::UserArrayCount:(%d)", dwUserCount);
		}
		else {
			if (DEVELOP_MODE) PrintLn("MultiotpProvider::UserArray.GetCount Error");
			dwUserCount = 1;
		}
	}
	else {
		if (DEVELOP_MODE) PrintLn("MultiotpProvider::Unassigned UserArray");
		dwUserCount = 1;
	}

	if ((dwUserCount == 0) || (IsOS(OS_DOMAINMEMBER) == 1)) {
		dwUserCount += 1;//display additional empty tile
		if (DEVELOP_MODE) PrintLn("MultiotpProvider::Count +1 (empty tile)");
	}

	if (DEVELOP_MODE) PrintLn("MultiotpProvider::User count:(%d)", dwUserCount);

	if (IsRemoteSession()) {
		if (DEVELOP_MODE) PrintLn("MultiotpProvider::GetCredentialCount: RDP connection");

		*pdwCount = dwUserCount;//1
		
		//get RDP port from registry
		int RDPPort = 3389;//default RDPPort
//		HRESULT hr;

		RDPPort = readRegistryValueInteger(CONF_RDP_PORT, RDPPort);
		if (DEVELOP_MODE) PrintLn("MultiotpProvider::RDP connection on port: %d", RDPPort);
	}

	else {
		if (DEVELOP_MODE) PrintLn("MultiotpProvider::Local connection");
		//logfile << "Local connection\n";

		if (readRegistryValueInteger(CONF_RDP_ONLY, 0)) {
			if (DEVELOP_MODE) PrintLn("MultiotpProvider::Only RDP is OTP protected!!!");
			*pdwCount = 0;//no filtering no OTP tile
		}
		else {
			if (DEVELOP_MODE) PrintLn("MultiotpProvider::RDP and Local OTP protection");
			*pdwCount = dwUserCount;//show OTP tile
		}

		if (DEVELOP_MODE) {
			PrintLn("MultiotpProvider::OTP tile always visible");
			*pdwCount = dwUserCount;//development - don't force but allow OTP in all scenarios
		}
	}

    return S_OK;
}