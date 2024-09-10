HWND ProcessList::getWindowsByProcessName(string processName, string windowName, string className) {
	windowList = {};
	// NuLogger::getInstance()->log("-----------------------------------------------------");
	// NuLogger::getInstance()->log("getWindowsByProcessName");
	// NuLogger::getInstance()->log("-----------------------------------------------------");
	
	vector<DWORD> pidList = getPIDsofProcess(processName);
	for (vector<DWORD>::iterator it = pidList.begin(); it != pidList.end(); ++it) {
		addMainWindowByProcessIdToWindowList(*it);
	}

	vector<HWND> mainWindows = windowList;
	windowList = {};

	for (vector<HWND>::iterator itHWND = mainWindows.begin(); itHWND != mainWindows.end(); ++itHWND) {
		addChildWindowsByMainWindowToWindowList(*itHWND);
	}

	vector<HWND> childWindows = windowList;
	windowList = {};

	vector<HWND> allWindows = mainWindows;
	allWindows.insert(allWindows.end(), childWindows.begin(), childWindows.end());

	
	vector<HWND> filteredWindows = {};
	for (vector<HWND>::iterator cHWND = allWindows.begin(); cHWND != allWindows.end(); ++cHWND) {
		
		if (IsWindow(*cHWND) && IsWindowVisible(*cHWND)) {
			// NuLogger::getInstance()->log(" - Handle %i", *cHWND);
			
			CHAR windowNameBuf[255];
			GetWindowTextA(*cHWND, windowNameBuf, 255);
			// NuLogger::getInstance()->log("   |- Window: \"%s\"", windowNameBuf);

			CHAR classNameBuf[255];
			GetClassNameA(*cHWND, classNameBuf, 255);
			// NuLogger::getInstance()->log("   |- ClassName: \"%s\"", classNameBuf);
						
			if ((windowNameBuf == windowName || windowName == "") && 
				(classNameBuf == className || className == "")) {
				filteredWindows.push_back(*cHWND);
				// return *cHWND;
			}

		}
		else {
		//	NuLogger::getInstance()->log("\\ no window");
		}
		
	}
	
	// NuLogger::getInstance()->log("-----------------------------------------------------");
	
	if (filteredWindows.size() > 0) {
		return filteredWindows[0];
	}
	else {
		return NULL;
	}
	
}