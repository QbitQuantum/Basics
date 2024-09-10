	bool empty()
	{
		if( m_ParentPath.size() )
		{
			char buf[2];
			size_t len = GetPrivateProfileStringA(m_ParentPath.c_str(), m_obj->m_name.c_str(), "", buf, sizeof(buf), m_pPath->c_str());
			return len == 0;
		}
		else if (m_obj && m_obj->m_name.size())
		{
			char buf[3];
			tstring app = m_obj->m_name;
			size_t len = GetPrivateProfileSectionA(app.c_str(), buf, sizeof(buf), m_pPath->c_str());
			return len == 0;
		}
		return true;
	}