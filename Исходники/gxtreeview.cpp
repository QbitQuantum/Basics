void wxGxTreeView::OnEndLabelEdit(wxTreeEvent& event)
{
    if ( event.GetLabel().IsEmpty() )
    {        
        event.Veto();
		return;
    }

	wxTreeItemId item = event.GetItem();
	if(!item.IsOk())
	{
		event.Veto();
		return;
	}
	wxGxTreeItemData* pData = (wxGxTreeItemData*)GetItemData(event.GetItem());
	if(pData == NULL)
	{
		event.Veto();
		return;
	}
    
    wxGxObject* pGxObject = m_pCatalog->GetRegisterObject(pData->m_nObjectID);
	IGxObjectEdit* pObjEdit =  dynamic_cast<IGxObjectEdit*>(pGxObject);
	if(pObjEdit == NULL)
	{
		event.Veto();
		return;
	}

	if(!pObjEdit->Rename(event.GetLabel()))
	{
		event.Veto();
		wxMessageBox(_("Rename error!"), _("Error"), wxICON_ERROR | wxOK );
		return;
	}

	m_pCatalog->ObjectChanged(pGxObject->GetId());
}