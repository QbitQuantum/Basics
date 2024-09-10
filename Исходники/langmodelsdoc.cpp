// we use this as a hook to customize the language menu
void CLangModelsDoc::OnUpdateLangProperties(CCmdUI* pCmdUI)
{

	CWnd* pWnd = AfxGetMainWnd();
	//CMenu* pTopMenu = pWnd->GetMenu();

	// this is wierd but it seemed that we have to search for the menu
	// I know, it should be 3, but sometimes our commands ended up in the view menu
/*	CMenu* pMenu = NULL;
	for(int i=2; i < 5; i++)
	{
		CString s;
		pTopMenu->GetMenuString(i, s,  MF_BYPOSITION );
		if(s == "&Language")
		{
			pMenu = pTopMenu->GetSubMenu(i);
			break;
		}
	}
*/
	CMenu* pMenu = pCmdUI->m_pMenu;

	if(!pMenu)	// null when you make a choice in the menu?
		return;

	const int kSynthSeqIndex = 3;
	//const int kItemsAfterTransfer = 2;

	const CTypedPtrArray<CPtrArray, CLangModelsDoc*>& pLangDocs = getProject()->getLangDocs();

	// remove existing transfer menu items
	for(	int z=pMenu->GetMenuItemCount();
			z >= 0; z--)
	{
		int iCMD = pMenu->GetMenuItemID(z);
		// is this a transfer sequence item?
		if(iCMD >= kTransferCMDBase && iCMD <= (kTransferCMDBase+ pLangDocs.GetSize()-1))
			pMenu->DeleteMenu(z, MF_BYPOSITION );
	}
	// now we should have the menu as in the resource editor

	// stick in an item for each transfer process sequence
	// note that this is written with the assumption that there
	// is one transfer sequence for each other language in the
	// project
	int iItem = kSynthSeqIndex;	// which menu item
	int iCount = 0;	// index into the transfer sequences
	for(int iTrg=0; iTrg<pLangDocs.GetSize(); iTrg++)
	{
		if(pLangDocs[iTrg] != this)
		{
#ifndef hab17a1
				CString s("Transfer ");
				if ((m_pLang->m_wDisplayFlags & m_pLang->kLocateTransferWithTarget) > 0)
			  s += "From ";
			else
			  s += "To ";
#else // hab17a1
			CString s("Transfer To ");
#endif // hab17a1
			s += pLangDocs[iTrg]->getLang()->getName();
			s += " Sequence...";
			pMenu->InsertMenu(iItem,
				MF_ENABLED | MF_BYPOSITION | MF_STRING ,
				kTransferCMDBase + iCount, // cmd id
				s);
			iItem++; iCount++;
		}
	}
	pWnd->DrawMenuBar();
}