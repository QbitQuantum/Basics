LSTATUS SetRegValue(HKEY rootKey, std::wstring wsSubKey, std::wstring wsData) {
	HKEY key;
	LSTATUS retValue = RegOpenKeyEx(rootKey, _T(""), 0, KEY_WRITE | KEY_READ, &key);
	if (retValue != ERROR_SUCCESS) {
		std::cout << "打开注册表失败" << std::endl;
		return retValue;
	}

	//依次创建wsSubKey路径中的子键
	std::vector<std::wstring> subKeyVec;
	int newPos = 0;
	int oldPos = 0;
	while (true) {
		newPos = wsSubKey.find(_T("\\"), oldPos);
		if (newPos != std::string::npos) {
			subKeyVec.push_back(wsSubKey.substr(oldPos, newPos - oldPos));
			oldPos = newPos + 1;
		}
		else {
			break;
		}
	}
	if (subKeyVec.size() == 0) {
		return ERROR_INVALID_FUNCTION;
	}

	HKEY fatherKey = key;
	HKEY subKey = 0;
	for (size_t i = 0; i < subKeyVec.size(); ++i) {
		DWORD dw;
		RegCreateKeyEx(fatherKey,
			subKeyVec[i].c_str(),
			NULL,
			NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_WRITE | KEY_READ, NULL,
			&subKey,
			&dw);
		RegCloseKey(fatherKey);
		fatherKey = subKey;
	}

	retValue = RegSetValue(subKey, _T(""), REG_SZ, wsData.c_str(), wsData.length());
	RegCloseKey(subKey);

	return retValue;
}