void OgreNewtonDebugger::ShowDebugInformation()
{
	m_lru ++;
	for (dNewtonBody* body = m_world->GetFirstBody(); body; body = m_world->GetNextBody(body)) {
		BodyDebugDataMap::iterator item (m_cachemap.find(body));
		if (item == m_cachemap.end()) {
			std::pair<BodyDebugDataMap::iterator, bool> pair (m_cachemap.insert(std::make_pair (body, BodyDebugData())));
			item = pair.first;
			BodyDebugData& data = item->second;
			data.Init(this, body);
		}
		BodyDebugData& data = item->second;
		if (data.m_lru < (m_lru - 1)) {
			data.Cleanup(this);
			m_cachemap.erase (item);
		} else {
			data.m_lru = m_lru;

			Matrix4 matrix;
			body->GetMatrix (matrix[0]);
			matrix = matrix.transpose();
			data.m_node->setPosition (matrix.getTrans());
			data.m_node->setOrientation (matrix.extractQuaternion());
		}
	}
}