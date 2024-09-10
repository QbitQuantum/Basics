STREAM_DATA* CPluginStream::findData(LPCTSTR id)
{
	int nodeIndex = -1;
	if(m_nodes.GetCount()) 
	{
		nodeIndex = m_nodes[m_nodes.GetCount() - 1];
	}
	for(int i=nodeIndex + 1; i < m_data.GetCount(); i++)
	{
		if(m_data[i].type == SDT_ENDNODE && *((LPDWORD) m_data[i].lpData) == nodeIndex) 
		{
			break;
		}
		if(!StrCmpI(m_data[i].id, id)) 
		{
			return &m_data[i];
		}
	}
	return NULL;
}