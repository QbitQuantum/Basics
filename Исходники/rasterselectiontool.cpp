void RasterSelectionTool::setNewFreeDeformer()
{
	if (!m_freeDeformers.empty() || isSelectionEmpty())
		return;

	TImageP image = (TImageP)getImage(true);

	TToonzImageP ti = (TToonzImageP)image;
	TRasterImageP ri = (TRasterImageP)image;
	if (!ti && !ri)
		return;

	if (!isFloating())
		m_rasterSelection.makeFloating();
	m_freeDeformers.push_back(new RasterFreeDeformer(m_rasterSelection.getFloatingSelection()));
	std::vector<TStroke> strokes = m_rasterSelection.getOriginalStrokes();
	if (!strokes.empty()) {
		TVectorImage *vi = new TVectorImage();
		std::set<int> indices;
		//Devo deformare anche gli strokes della selezione!!!
		int i;
		for (i = 0; i < (int)strokes.size(); i++) {
			vi->addStroke(new TStroke(strokes[i]));
			indices.insert(i);
		}
		m_selectionFreeDeformer = new VectorFreeDeformer(vi, indices);
		m_selectionFreeDeformer->setPreserveThickness(true);
	}
}