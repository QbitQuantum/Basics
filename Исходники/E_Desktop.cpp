//잔상 이슈 해결 종속적
void E_Desktop::setAllNormalExcludeRemoveDirty(list<char*> exclude)
{
	char pname[255] = { 0, };
	for (list<E_Window*>::iterator itr = windowList.begin(); itr != windowList.end(); itr++)
	{
		char* subpname = NULL;
		//비주얼 스튜디오 제외
		if (!(*itr)->isAeroPossible()){
			GetWindowTextA((*itr)->getWindow(), pname, 255);
			for (list<char*>::iterator iter = exclude.begin(); iter != exclude.end(); iter++) {
				subpname = strstr(pname, (*iter));
				if (subpname != NULL)
					break;
			}
			TRACE_WIN32A("[setAllNormalExcludeRemoveDirty] %s", pname);

			if (subpname == NULL){	//Visual Studio 제외
				TRACE_WIN32A("[setAllNormalExcludeRemoveDirty] %s setNormal",pname );
				(*itr)->setNormal();

				//잔상 이슈 해결
				LONG_PTR tt = GetWindowLongPtr((*itr)->getWindow(), GWL_STYLE);
				if (tt & DS_3DLOOK)
				{
					//현재위치 저장
					RECT rect;
					GetWindowRect((*itr)->getWindow(), &rect);
					WINDOWPLACEMENT placement;
					GetWindowPlacement((*itr)->getWindow(), &placement);
					placement.rcNormalPosition = rect;
					placement.showCmd = SW_MINIMIZE;	//최소화로 예상하고 해결
					(*itr)->saveRect(placement);

					MoveWindow((*itr)->getWindow(), E_EnvironmentManager::getSingleton()->getWidth(), E_EnvironmentManager::getSingleton()->getHeight(), rect.right - rect.left, rect.bottom - rect.top, FALSE);
				}

				//break;
			}

		}
	}
}