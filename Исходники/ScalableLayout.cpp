CContainerUI * CScalableLayout::CreateLayout( CScalableNode::Ptr pNode,int nLevel )
{
	CContainerUI *pLayout = pNode->IsHor ?
		static_cast<CContainerUI*>(new CHorizontalLayoutUI) : 
		static_cast<CContainerUI*>(new CVerticalLayoutUI);

	pLayout->SetBkColor(pNode->BkColor);

	for (CScalableNode::Iter i = pNode->ChildBegin();
		i != pNode->ChildEnd();
		i++)
	{
		bool bLeaf = true;
		for (CScalableNode::Iter j = (*i)->ChildBegin();
			j != (*i)->ChildEnd();
			j++)
		{
			if ((*j)->Level == nLevel)
			{
				bLeaf = false;
				break;
			}
		}
		if (bLeaf)
		{
			CContainerUI *pItemContainer = new CContainerUI;
			CButtonUI *pItem = new CButtonUI;
			pItem->SetName((*i)->Name);
			pItem->SetBkColor((*i)->BkColor);

			pItem->SetShowHtml();
			pItem->SetTextStyle(DT_CENTER|DT_VCENTER);
			
			CDuiString sText;
			if ((*i)->Text.IsEmpty())
			{
				sText.Format(_T("{p}{c #FFCCCCCC}%s{/c}{/p}"),
					(LPCTSTR)(*i)->Description);
			}
			else
			{
				sText.Format(_T("{p}%s{n}{c #FFCCCCCC}%s{/c}{/p}"),
					(LPCTSTR)(*i)->Text,(LPCTSTR)(*i)->Description);
			}
			pItem->SetText(sText);
			
			pItemContainer->Add(pItem);

			pLayout->Add(pItemContainer);
		}
		else
		{
			pLayout->Add(CreateLayout(*i,nLevel));
		}
	}


	if (!pNode->Description.IsEmpty())
	{
		CVerticalLayoutUI *pWrapper = new CVerticalLayoutUI;
		pWrapper->Add(pLayout);

		pLayout->SetInset(CDuiRect(5,5,5,0));

		CLabelUI *pDescription = new CLabelUI;
		pDescription->SetFixedHeight(20);
		pDescription->SetTextStyle(DT_CENTER);
		pDescription->SetBkColor(pNode->BkColor);

		pDescription->SetText(pNode->Description);
		pWrapper->Add(pDescription);

		return pWrapper;
	}

	return pLayout;
}