void wxGxContentView::OnEndLabelEdit(wxListEvent& event)
{
    //event.Skip();
    if ( event.GetLabel().IsEmpty() )
    {
        event.Veto();
		return;
    }

	LPITEMDATA pItemData = (LPITEMDATA)event.GetData();
	if(pItemData == NULL)
	{
		event.Veto();
		return;
	}

    wxGxObject* pGxObject = m_pCatalog->GetRegisterObject(pItemData->nObjectID);
	IGxObjectEdit* pObjEdit =  dynamic_cast<IGxObjectEdit*>(pGxObject);
	if(pObjEdit == NULL)
	{
		event.Veto();
		return;
	}
	if(pObjEdit->Rename(event.GetLabel()))
	{
    	m_pCatalog->ObjectChanged(pGxObject->GetId());
	}
    else
    {
		event.Veto();
		wxMessageBox(_("Rename failed!"), _("Error"), wxICON_ERROR | wxOK );

        SORTDATA sortdata = { m_bSortAsc, m_currentSortCol };
        SortItems(GxObjectCVCompareFunction, (long)&sortdata);
        SetColumnImage(m_currentSortCol, m_bSortAsc ? 0 : 1);

		return;
    }
}