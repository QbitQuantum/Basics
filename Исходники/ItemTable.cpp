void SelectByCriteria (SItemTableCtx &Ctx, const CString &sCriteria, TArray<CItemType *> *retList)
	{
	int i;

	//	Compute the criteria

	CItemCriteria Crit;
	if (!sCriteria.IsBlank())
		CItem::ParseCriteria(sCriteria, &Crit);
	else
		CItem::InitCriteriaAll(&Crit);

	//	Loop over all items that match and add them to
	//	a sorted table.

	retList->DeleteAll();
	for (i = 0; i < Ctx.pUniverse->GetItemTypeCount(); i++)
		{
		CItemType *pType = Ctx.pUniverse->GetItemType(i);
		CItem Item(pType, 1);

		if (!Item.MatchesCriteria(Crit))
			continue;

		retList->Insert(pType);
		}
	}