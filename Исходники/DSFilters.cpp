HRESULT CDSFilters::ParseInfoBuffer(TCHAR* pszBuffer)
{
	HRESULT hr = S_OK;

	rapidxml::xml_document<TCHAR> doc;

	try
	{
		doc.parse<0>(pszBuffer);
	}
	catch(rapidxml::parse_error& error)
	{
		CString strError(error.what());
		g_utility.Log(_T("RapidXml got parse error:%s"), strError);
		return FALSE;
	}

	rapidxml::xml_node<TCHAR>* node = doc.first_node();
	if (node)
		node = node->first_node(_T("filter"));
	for(; node!=NULL; node=node->next_sibling())
	{
		if (_tcsicmp(node->name(), _T("filter")) != 0)
		{
			continue;
		}

		DSFilterInfo* pInfo  = new DSFilterInfo();
		if (pInfo == NULL)
		{
			hr = E_OUTOFMEMORY;
			break;
		}

		rapidxml::xml_attribute<TCHAR>* attr = node->first_attribute();
		for(; attr!=NULL; attr=attr->next_attribute())
		{
			SetFilterInfo(pInfo, attr->name(), attr->value());
		}

		rapidxml::xml_node<TCHAR>* subnode = node->first_node();
		for (; subnode!=NULL; subnode=subnode->next_sibling())
		{
			SetFilterInfo(pInfo, subnode);
		}

		if (pInfo->filtertype == FT_SOURCE)
		{
			m_source.AddTail(pInfo);
		}
		else
		{
			m_transform.AddTail(pInfo);
		}
	}
	return hr;
}