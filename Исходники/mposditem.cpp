	void setTextureCount(int textures) {
		if (_Expand(m_vPositions, 2*N*textures)) {
			m_vCoords.resize(m_vPositions.size());
			if (m_hasColor)
				m_vColors.resize(m_vPositions.size()/2);
		}
	}