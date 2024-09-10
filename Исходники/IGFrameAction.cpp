bool IGFrameActionAddLayer::Undo (list <int>& lLayerIndices, list <pair <int, bool>>& lSelectionIndices)
{
	lLayerIndices.remove (m_nLayerId);
	bool bWorkingLast = (m_pFrame->GetWorkingLayer() == m_pFrame->GetLayer (m_nLayerPos));
	m_pFrame->RemoveCalc (m_nLayerPos, NULL, false);
	if (bWorkingLast)
		m_pFrame->SetWorkingLayer (m_pFrame->GetNbLayers() - 1);
	return true;
}