// Все параметры могут быть NULL - вызов из GuiMacro
bool CConEmuCtrl::key_ShowTabsList(DWORD VkMod, bool TestOnly, const ConEmuHotKey* hk, CRealConsole* pRCon)
{
	// 120820 - не будем требовать наличия плагина для F12 в Far
	if (pRCon && pRCon->GetFarPID(false))
	{
		// Для Far Manager - не обрабатывать.
		// Если юзеру нужно ConEmu-шное меню для списка табов - есть vkShowTabsList2 и GuiMacro "Tabs(8)"
		return false;
	}
	else
	{
		if (TestOnly)
			return true;

		//HMENU hPopup = gpConEmu->CreateVConListPopupMenu(NULL, FALSE);

		RECT rcWnd = {};
		if (pRCon)
		{
			GetWindowRect(pRCon->GetView(), &rcWnd);
		}
		else
		{
			GetClientRect(ghWnd, &rcWnd);
			MapWindowPoints(ghWnd, NULL, (LPPOINT)&rcWnd, 2);
		}

		POINT pt = {(rcWnd.left+rcWnd.right)/2, (rcWnd.top+rcWnd.bottom)/2};

		ChooseTabFromMenu(FALSE, pt, TPM_CENTERALIGN|TPM_VCENTERALIGN);

		//int nTab = gpConEmu->trackPopupMenu(tmp_TabsList, hPopup, TPM_CENTERALIGN|TPM_VCENTERALIGN|TPM_RETURNCMD,
		//	x, y, 0, ghWnd, NULL);
		//if (nTab >= IDM_VCON_FIRST && nTab <= IDM_VCON_LAST)
		//{
		//	int nNewV = ((int)HIWORD(nTab))-1;
		//	int nNewR = ((int)LOWORD(nTab))-1;
		//	
		//	CVirtualConsole* pVCon = gpConEmu->GetVCon(nNewV);
		//	if (pVCon)
		//	{
		//		CRealConsole* pRCon = pVCon->RCon();
		//		if (pRCon)
		//		{
		//			pRCon->ActivateFarWindow(nNewR);
		//		}
		//		if (!gpConEmu->isActive(pVCon))
		//			gpConEmu->Activate(pVCon);
		//	}
		//}

		//CESERVER_REQ_GETALLTABS::TabInfo* pTabs = NULL;
		//int Count = (int)CConEmuCtrl::GetOpenedTabs(pTabs);
		//if ((Count < 1) || !pTabs)
		//{
		//	SafeFree(pTabs);
		//	return false;
		//}

		//WARNING("должна быть подобная функция для DropDown у тулбара");
		//HMENU hPopup = CreatePopupMenu();

		//int nLastConsole = 0;
		//for (int i = 0, k = 0; i < Count; i++, k++)
		//{
		//	if (nLastConsole != pTabs[i].ConsoleIdx)
		//	{
		//		AppendMenu(hPopup, MIF_SEPARATOR, 0, NULL);
		//		nLastConsole = pTabs[i].ConsoleIdx;
		//	}
		//	DWORD nFlags = 0
		//		| (pTabs[i].Disabled ? (MF_GRAYED|MF_DISABLED) : MF_ENABLED)
		//		| 
		//	pItems[k].Selected = (pOut->GetAllTabs.Tabs[i].ActiveConsole && pOut->GetAllTabs.Tabs[i].ActiveTab);
		//	pItems[k].Checked = pOut->GetAllTabs.Tabs[i].ActiveTab;
		//	pItems[k].Disabled = pOut->GetAllTabs.Tabs[i].Disabled;
		//	pItems[k].MsgText = pOut->GetAllTabs.Tabs[i].Title;
		//	pItems[k].UserData = i;
		//}
		//DestroyMenu(hPopup);
	}

	//int AllCount = Count + pTabs[Count-1].ConsoleIdx;
	//if (pItems)
	//{
	//}

	return true;
}