void CVoronoi::Generate(int nWidth, int nHeight, byte* szData) {
	float fDistance, fTmp;
	auto end = m_List.end();
	for (int j=0; j<nHeight; ++j) {
		for (int i=0; i<nWidth; ++i) {
			fDistance = CVoronoi::s_fInfinite;
			auto ite = m_List.begin();
			for (; end!=ite; ++ite) {
				fTmp = DISTANCE((float)i, (float)j, (float)ite->x, (float)ite->y);
				if (fTmp < fDistance) {
					szData[i+nWidth*j] = ite->data;
					fDistance = fTmp;
				}
			}
		}
	}
}