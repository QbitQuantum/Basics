void CActionFeatureInfo::LButtonUpEvent(UINT nFlags, CPoint point)
{

	

	GEOMETRY::geom::Envelope envelop;
	DIS_RECT rect;
	rect.left =point.x -3;
	rect.right =point.x+3;
	rect.top =point.y -3;
	rect.bottom =point.y+3;

	m_pMap->GetDisplay()->GetDisplayTransformation().TransformToGeo(rect,&envelop);
	//构造一个用于查询的多边形

	Geodatabase::CSpatialQuery queryfilter;


	//构造一个空间查询条件
	GEOMETRY::geom::Geometry *pGeometry =GeometryFactory::getDefaultInstance()->toGeometry(&envelop);
	queryfilter.SetGeometry(pGeometry);
	queryfilter.SetSpatialRel(Geodatabase::SpatialRelIntersects);


	Carto::CLayerArray &layers =m_pMap->GetLayers();

	Carto::ILayerPtr pLayer;
	long FeatureLayernum=0;
	for(int i=0;i<layers.GetSize();i++)
	{
		pLayer =layers.GetAt(i);
		if(!pLayer->GetVisible())
		{
			continue;
		}
		if(pLayer->GetLayerType()!=Carto::FeatureLayer)
		{
			continue;
		}

		pLayer->Select(&queryfilter,Carto::SELECT_REPLACE);

		FeatureLayernum++;


	}

	if(FeatureLayernum==0)
	{
		return;
	}
	m_pMapCtrl->UpdateContent(otDrawGeoSelection);

    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if( NULL != m_dlg )
	{
		if( !IsWindow( m_dlg->m_hWnd ) )
		{
			m_dlg->Create( );			
		}
		m_dlg->SetMap(m_pMap);
		m_dlg->Refresh();
		m_dlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_dlg = new CDlgFeatureInfo;
		if( NULL == m_dlg )
			return;
		m_dlg->Create( );
		m_dlg->SetMap(m_pMap);
		m_dlg->Refresh();

	}
}