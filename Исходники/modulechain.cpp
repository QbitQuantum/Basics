int CDb3Base::WorkModuleChain(int firstTime)
{
	DBModuleName moduleName, *newModName;

	if (firstTime) {
		cb->pfnAddLogMessage(STATUS_MESSAGE, TranslateT("Processing module name chain"));
		modChainCount = 0;
		last_mod = 0;
		free(modChain);
		modChain = (ModChainEntry*)malloc(sizeof(ModChainEntry));
		phase = 0;
		ofsCurrent = m_dbHeader.ofsFirstModuleName;
	}

	switch (phase) {
	case 0:
		if (ofsCurrent == 0) {
			phase++;
			return ERROR_SUCCESS;
		}
		if (!SignatureValid(ofsCurrent, DBMODULENAME_SIGNATURE)) {
			cb->pfnAddLogMessage(STATUS_ERROR, TranslateT("Module chain corrupted, further entries ignored"));
			phase++;
			return ERROR_SUCCESS;
		}
		if (PeekSegment(ofsCurrent, &moduleName, offsetof(DBModuleName, name)) != ERROR_SUCCESS) {
			phase++;
			return ERROR_SUCCESS;
		}
		modChain = (ModChainEntry*)realloc(modChain, sizeof(ModChainEntry)*++modChainCount);

		modChain[modChainCount - 1].ofsOld = ofsCurrent;
		modChain[modChainCount - 1].size = offsetof(DBModuleName, name) + moduleName.cbName;
		modChain[modChainCount - 1].ofsNew = 0;

		if (moduleName.cbName)
			PeekSegment(ofsCurrent + offsetof(DBModuleName, name), &modChain[modChainCount - 1].name, moduleName.cbName);
		modChain[modChainCount - 1].name[moduleName.cbName] = 0;
		ofsCurrent = moduleName.ofsNext;
		break;
	case 1:
		ofsLast = 0;
		iCurrentModName = 0;
		m_dbHeader.ofsFirstModuleName = 0;
		phase++;
	case 2:
		if (iCurrentModName >= modChainCount) {
			DWORD dw = 0;
			if (ofsLast)	WriteSegment(ofsLast + offsetof(DBModuleName, ofsNext), &dw, sizeof(DWORD));
			return ERROR_NO_MORE_ITEMS;
		}
		if (modChain[iCurrentModName].ofsNew == 0) {
			newModName = (DBModuleName*)_alloca(modChain[iCurrentModName].size);
			if (ReadSegment(modChain[iCurrentModName].ofsOld, newModName, modChain[iCurrentModName].size) != ERROR_SUCCESS)
				return ERROR_NO_MORE_ITEMS;
			if ((modChain[iCurrentModName].ofsNew = WriteSegment(WSOFS_END, newModName, modChain[iCurrentModName].size)) == WS_ERROR)
				return ERROR_HANDLE_DISK_FULL;
			
			// check duplicated modulenames
			int i, n = 0;
			for (i = iCurrentModName + 1; i < modChainCount; i++)
				if (!strcmp(modChain[i].name, modChain[iCurrentModName].name)) {
					modChain[i].ofsNew = modChain[iCurrentModName].ofsNew;
					n++;
				}
			if (n) {
				TCHAR szModuleName[257];
				MultiByteToWideChar(CP_ACP, 0, modChain[iCurrentModName].name, -1, szModuleName, SIZEOF(szModuleName));
				TCHAR *pszModuleName = szModuleName;

				cb->pfnAddLogMessage(STATUS_WARNING, TranslateT("Module name '%s' is not unique: %d duplicates found"), pszModuleName, n);
			}

			if (iCurrentModName == 0)
				m_dbHeader.ofsFirstModuleName = modChain[iCurrentModName].ofsNew;
			else if (WriteSegment(ofsLast + offsetof(DBModuleName, ofsNext), &modChain[iCurrentModName].ofsNew, sizeof(DWORD)) == WS_ERROR)
				return ERROR_HANDLE_DISK_FULL;
			ofsLast = modChain[iCurrentModName].ofsNew;
		}
		iCurrentModName++;
		break;
	}
	return ERROR_SUCCESS;
}