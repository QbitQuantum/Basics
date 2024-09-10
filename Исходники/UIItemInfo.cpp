void CUIItemInfo::InitItem(CInventoryItem* pInvItem)
{
	m_pInvItem				= pInvItem;
	if(!m_pInvItem)			return;

	string256				str;
	if(UIName)
	{
		UIName->SetText		(pInvItem->Name());
	}
	if(UIWeight)
	{
		sprintf_s				(str, "%3.2f kg", pInvItem->Weight());
		UIWeight->SetText	(str);
	}
	if( UICost && IsGameTypeSingle() )
	{
		sprintf_s				(str, "%d %s", pInvItem->Cost(),*CStringTable().translate("ui_st_money_regional"));		// will be owerwritten in multiplayer
		UICost->SetText		(str);
	}

	if(UICondProgresBar)
	{
		float cond							= pInvItem->GetConditionToShow();
		UICondProgresBar->Show				(true);
		UICondProgresBar->SetProgressPos	( cond*100.0f+1.0f-EPS );
	}

	if(UIDesc)
	{
		UIDesc->Clear						();
		VERIFY								(0==UIDesc->GetSize());
		TryAddWpnInfo						(pInvItem->object().cNameSect());
		TryAddArtefactInfo					(pInvItem->object().cNameSect());
		if(m_desc_info.bShowDescrText)
		{
			CUIStatic* pItem					= xr_new<CUIStatic>();
			pItem->SetTextColor					(m_desc_info.uDescClr);
			pItem->SetFont						(m_desc_info.pDescFont);
			pItem->SetWidth						(UIDesc->GetDesiredChildWidth());
			pItem->SetTextComplexMode			(true);
			pItem->SetText						(*pInvItem->ItemDescription());
			pItem->AdjustHeightToText			();
			UIDesc->AddWindow					(pItem, true);
		}
		UIDesc->ScrollToBegin				();
	}
	if(UIItemImage)
	{
		// Загружаем картинку
		UIItemImage->SetShader				(InventoryUtilities::GetEquipmentIconsShader());

		int iGridWidth						= pInvItem->GetGridWidth();
		int iGridHeight						= pInvItem->GetGridHeight();
		int iXPos							= pInvItem->GetXPos();
		int iYPos							= pInvItem->GetYPos();

		UIItemImage->GetUIStaticItem().SetOriginalRect(	float(iXPos*INV_GRID_WIDTH), float(iYPos*INV_GRID_HEIGHT),
														float(iGridWidth*INV_GRID_WIDTH),	float(iGridHeight*INV_GRID_HEIGHT));
		UIItemImage->TextureOn				();
		UIItemImage->ClipperOn				();
		UIItemImage->SetStretchTexture		(true);
		Frect v_r							= {	0.0f, 
												0.0f, 
												float(iGridWidth*INV_GRID_WIDTH),	
												float(iGridHeight*INV_GRID_HEIGHT)};
		if(UI()->is_16_9_mode())
			v_r.x2 /= 1.328f;

		UIItemImage->GetUIStaticItem().SetRect	(v_r);
		UIItemImage->SetWidth					(_min(v_r.width(),	UIItemImageSize.x));
		UIItemImage->SetHeight					(_min(v_r.height(),	UIItemImageSize.y));
	}
}