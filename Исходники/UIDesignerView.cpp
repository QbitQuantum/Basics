void CUIDesignerView::PasteUI(LPCTSTR xml)
{
	CDialogBuilder builder;
	CControlUI* pRoot=builder.Create(xml, (UINT)0, NULL, m_LayoutManager.GetManager());
	if(pRoot)
	{
		CControlUI* pParent = m_MultiTracker.GetFocused();
		if(pParent->GetInterface(_T("Container")) == NULL)
			pParent = pParent->GetParent();
		if(pParent == NULL)
			pParent = m_LayoutManager.GetForm();

		m_MultiTracker.RemoveAll();
		CContainerUI* pContainer = static_cast<CContainerUI*>(pParent->GetInterface(_T("Container")));
		CContainerUI* pRootContainer = static_cast<CContainerUI*>(pRoot->GetInterface(_T("Container")));
		ExtendedAttributes* pExtended = (ExtendedAttributes*)pContainer->GetTag();
		for(int i=0; i<pRootContainer->GetCount(); i++)
		{
			CControlUI* pControl = pRootContainer->GetItemAt(i);
			if(pControl->IsFloat())
			{
				SIZE sz = pControl->GetFixedXY();
				sz.cx += COPY_OFFSET_XY;
				sz.cy += COPY_OFFSET_XY;
				pControl->SetFixedXY(sz);
			}
			pContainer->Add(pControl);
			m_MultiTracker.Add(CreateTracker(pControl));
			InitUI(pControl, pExtended->nDepth + 1);
		}
		CArray<CControlUI*,CControlUI*> arrSelected;
		m_MultiTracker.GetSelected(arrSelected);
		m_UICommandHistory.Begin(arrSelected, actionAdd);
		m_UICommandHistory.End();

		pContainer->SetPos(pContainer->GetPos());

		pRootContainer->SetAutoDestroy(false);
		delete pRootContainer;
		this->GetDocument()->SetModifiedFlag();
	}
}