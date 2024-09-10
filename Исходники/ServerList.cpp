bool CServerList::SaveStaticServers()
{
	bool bResult = false;

	FILE* fpStaticServers = _tfsopen(thePrefs.GetMuleDirectory(EMULE_CONFIGDIR) + _T("staticservers.dat"), _T("wb"), _SH_DENYWR);
	if (fpStaticServers == NULL) {
		LogError(LOG_STATUSBAR, GetResString(IDS_ERROR_SSF));
		return bResult;
	}

	// write Unicode byte-order mark 0xFEFF
	if (fputwc(0xFEFF, fpStaticServers) != _TEOF)
	{
		bResult = true;
		POSITION pos = list.GetHeadPosition();
		while (pos)
		{
			const CServer* pServer = list.GetNext(pos);
			if (pServer->IsStaticMember())
			{
				if (_ftprintf(fpStaticServers, _T("%s:%i,%i,%s\r\n"), pServer->GetAddress(), pServer->GetPort(), pServer->GetPreference(), pServer->GetListName()) == EOF) {
					bResult = false;
					break;
				}
			}
		}
	}

	fclose(fpStaticServers);
	return bResult;
}