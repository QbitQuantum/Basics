void wxGISMapView::AddLayer(wxGISLayer* pLayer)
{
	IDisplayTransformation* pDisplayTransformation = pGISScreenDisplay->GetDisplayTransformation();
	if(pDisplayTransformation->GetSpatialReference() == NULL)
	{
		OGRSpatialReference* pSpaRef = pLayer->GetSpatialReference();
		if(pSpaRef)
			pDisplayTransformation->SetSpatialReference(pSpaRef);
		else
		{
			OGREnvelope* pEnv = pLayer->GetEnvelope();
			if(pEnv)
			{
				if(pEnv->MaxX <= 180 && pEnv->MaxY <= 90 && pEnv->MinX >= -180 && pEnv->MinY >= -90)
				{
					OGRSpatialReference* pSpaRef = new OGRSpatialReference();
					pSpaRef->SetWellKnownGeogCS("WGS84");
					pDisplayTransformation->SetSpatialReference(pSpaRef);
				}
			}
		}
	}
	
	OGREnvelope* pEnv = pLayer->GetEnvelope();
	if(pEnv == NULL)
		return;
	OGRSpatialReference* pSpaRef = pLayer->GetSpatialReference();

	if(pSpaRef && pDisplayTransformation->GetSpatialReference())
	{
		if(!pDisplayTransformation->GetSpatialReference()->IsSame(pSpaRef))
		{
			OGRCoordinateTransformation *poCT = OGRCreateCoordinateTransformation( pSpaRef, pDisplayTransformation->GetSpatialReference() );
			poCT->Transform(1, &pEnv->MaxX, &pEnv->MaxY);
			poCT->Transform(1, &pEnv->MinX, &pEnv->MinY);
		}
	}

	if(!pDisplayTransformation->IsBoundsSet())
		pDisplayTransformation->SetBounds(*pEnv);
	else
	{
		OGREnvelope Bounds = pDisplayTransformation->GetBounds();
		Bounds.Merge(*pEnv);
		pDisplayTransformation->SetBounds(Bounds);
	}

	//caching
	if(pLayer->GetCached())
	{
		pLayer->SetCacheID(pGISScreenDisplay->AddCache());
	}
	else
	{
		if(m_Layers.size() > 0 && m_Layers[m_Layers.size() - 1]->GetCached())
			pLayer->SetCacheID(pGISScreenDisplay->AddCache());
		else
			pLayer->SetCacheID(pGISScreenDisplay->GetLastCacheID());
	}
	wxGISMap::AddLayer(pLayer);
}