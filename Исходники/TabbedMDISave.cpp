bool CSaveModifiedItemsDialog::FindUsedColumns(ITabbedMDIChildModifiedList* list, int columnUseCount[eColumn_Count])
{
	if(list == NULL)
	{
		return false;
	}

	bool success = true;

	long count = 0;
	list->get_Count(&count);
	for(long i=0; i<count; ++i)
	{
		CComPtr<ITabbedMDIChildModifiedItem> item;
		list->get_Item(i, &item);
		if(item)
		{
			if(m_showColumn[eColumn_Name])
			{
				CComBSTR displayName;
				item->get_DisplayName(&displayName);
				if(displayName.Length() > 0)
				{
					columnUseCount[eColumn_Name] += 1;
				}
			}
			if(m_showColumn[eColumn_Description])
			{
				CComBSTR description;
				item->get_Description(&description);
				if(description.Length() > 0)
				{
					columnUseCount[eColumn_Description] += 1;
				}
			}
			if(m_showColumn[eColumn_LastModified])
			{
				DATE lastModified = 0;
				item->get_LastModifiedUTC(&lastModified);
				if(lastModified != 0)
				{
					columnUseCount[eColumn_LastModified] += 1;
				}
			}

			CComPtr<ITabbedMDIChildModifiedList> subItems;
			item->get_SubItems(&subItems);
			if(subItems)
			{
				this->FindUsedColumns(subItems, columnUseCount);
			}
		}
	}

	return success;
}