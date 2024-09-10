/** 
* Dispalys the popup menu with the appropriate menu items enabled.
*/
void StageView::PopupMenu(CPoint* pt) {

	//Determine the type of object clicked on
	CListCtrl& list = GetListCtrl();


	ClientToScreen (pt);

	CMenu FloatingMenu;
	VERIFY(FloatingMenu.LoadMenu(IDR_ME_STAGELIST_POPUP));
	CMenu* pPopupMenu = FloatingMenu.GetSubMenu (0);
	ASSERT(pPopupMenu != NULL);

	POSITION pos = list.GetFirstSelectedItemPosition();
	int nItem = -1;
	if(pos)
		nItem = list.GetNextSelectedItem(pos);

	if(nItem <= 0) {
		pPopupMenu->EnableMenuItem(ID_STAGEPOPUP_RENAMESTAGE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pPopupMenu->EnableMenuItem(ID_STAGEPOPUP_DELETESTAGE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

		pPopupMenu->EnableMenuItem(ID_STAGEPOPUP_CUT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pPopupMenu->EnableMenuItem(ID_STAGEPOPUP_COPY, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	} else {
		MaterialDoc* material = materialDocManager->GetCurrentMaterialDoc();
		if(material->GetAttributeInt(nItem-1, "stagetype") != MaterialDoc::STAGE_TYPE_NORMAL) {
			pPopupMenu->EnableMenuItem(ID_STAGEPOPUP_RENAMESTAGE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		}
	}

	MaterialDoc* material = materialDocManager->GetCurrentMaterialDoc();
	if(material->FindStage(MaterialDoc::STAGE_TYPE_SPECIALMAP, "bumpmap") >= 0) {
		pPopupMenu->EnableMenuItem(ID_STAGEPOPUP_ADDBUMPMAP, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}
	if(material->FindStage(MaterialDoc::STAGE_TYPE_SPECIALMAP, "diffusemap") >= 0) {
		pPopupMenu->EnableMenuItem(ID_STAGEPOPUP_ADDDIFFUSEMAP, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}
	if(material->FindStage(MaterialDoc::STAGE_TYPE_SPECIALMAP, "specularmap") >= 0) {
		pPopupMenu->EnableMenuItem(ID_STAGEPOPUP_ADDSPECULAR, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	if(materialDocManager->IsCopyStage()) {
		pPopupMenu->EnableMenuItem(ID_STAGEPOPUP_PASTE, MF_BYCOMMAND | MF_ENABLED);
	} else {
		pPopupMenu->EnableMenuItem(ID_STAGEPOPUP_PASTE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	pPopupMenu->TrackPopupMenu (TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt->x, pt->y, &list);
}