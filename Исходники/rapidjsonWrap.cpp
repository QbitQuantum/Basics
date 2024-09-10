rapidjson::Value* rapidJsonWrap::selectObject(const std::string &strPath)
{
	//m_pVal = NULL;
	//m_iValCurIndex = -1;
	//m_pArrayVal = NULL;
	assert(!strPath.empty());
	if(strPath.empty()) return NULL;
	SStringArrayType vec = stringUtil::split(strPath.c_str(), ":");
	if (vec.size() == 1)
	{
		if(m_pVal)
		{
			m_pVal = findValue(vec[0]);
		}
		else
		{
			rapidjson::Document::MemberIterator iter = m_doc.FindMember(vec[0].c_str());
			if(iter == m_doc.MemberEnd()) return NULL;
			m_pVal = &iter->value;
		}
		return m_pVal;
	}
	return selectObject(vec);
}