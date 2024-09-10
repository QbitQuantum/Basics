void ChatMessageCollection::SetItemList(LPCWSTR ItemList)
{
	try {
		m_itemList.clear();

		WCHAR * list = _wcsdup(ItemList);
		WCHAR *next_token = NULL;
		WCHAR * pItem = wcstok_s(list, L", ", &next_token);
		while(pItem) {
			long lID = _wtol(pItem);
			if(lID > 0) {
				m_itemList.push_back(lID);
			}
			pItem = wcstok_s(NULL, L", ", &next_token);
		}
	free(list);
	} catch(...) {
	}
}