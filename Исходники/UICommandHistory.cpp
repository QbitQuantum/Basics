void CALLBACK CUICommandHistory::UIDelete(TiXmlNode* pNode)
{
	TiXmlElement* pElement = pNode->ToElement();
	CStringA strName = pElement->Attribute("myname");
	if(strName.IsEmpty())
		return;

	CUIDesignerView* pUIView = g_pMainFrame->GetActiveUIView();
	CPaintManagerUI* pManager = pUIView->GetPaintManager();
	CControlUI* pControl = pManager->FindControl(StringConvertor::Utf8ToWide(strName));
	if(pControl == NULL)
		return;
	CControlUI* pParent=pControl->GetParent();
	HTREEITEM hDelete=(HTREEITEM)(((ExtendedAttributes*)pControl->GetTag())->hItem);
	g_pClassView->RemoveUITreeItem(hDelete);
 	pUIView->DeleteUI(pControl);
	if(pParent)
		pParent->NeedUpdate();
}