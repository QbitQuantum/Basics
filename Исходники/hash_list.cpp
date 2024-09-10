void CHashedStringList::Delete(TCHAR * String)
{
	TCHAR * buff;
	if (!m_bCaseSense)
	{
		buff = _wcsdup(String);
		_wcslwr(buff);
	}
	else
		buff = String;
	UINT32 hash = SuperFastHash(buff, wcslen(buff))%m_Size;	//获得模数
	CMHashItem * hashitem = m_hashitem[hash].next;
	CMHashItem * parent = &m_hashitem[hash];
	while (hashitem && _wcsicmp(hashitem->String, buff))
	{
		parent = hashitem;
		hashitem = hashitem->next;
	}
	if (hashitem)	//找到了这一项
	{
		parent->next=hashitem->next;
		free(hashitem->String);
		free(hashitem->Value);
		free(hashitem);
	}
	if (!m_bCaseSense)
		free(buff);	
}