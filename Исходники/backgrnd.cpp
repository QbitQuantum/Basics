Layer* OpBackground::CreateBackgroundLayer()
{
	Layer* pNewLayer = new Layer;
	if (pNewLayer != NULL)
	{
		String_256 LayerName(_R(IDS_BACKGROUNDLAYERNAME));

		pNewLayer->SetVisible(TRUE); 
		pNewLayer->SetLocked(TRUE); 
		pNewLayer->SetPrintable(FALSE); 
		pNewLayer->SetBackground(TRUE); 
		pNewLayer->SetOutline(FALSE);
		pNewLayer->SetGuide(FALSE);
		pNewLayer->SetPageBackground(TRUE);		// This is the special page background layer flag
		pNewLayer->SetLayerID(LayerName); 

/*		// Ensure we are always rendered at maximum quality so that turning WYSIWYG
		// down does not remove the page background!
		Quality Qual;
		Qual.SetQuality(QUALITY_MAX);
		QualityAttribute QualAttr(Qual);
		NodeAttribute* pNodeAttr = QualAttr.MakeNode();
		pNodeAttr->AttachNode(pNewLayer, FIRSTCHILD); */
	}

	return pNewLayer;
}