void CEditFeatureTool::MouseMoveEvent (UINT nFlags, CPoint point)
{
	
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return ;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return ;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return ;
	}

	if(m_nStatus == On_None)
	{
		pMapCtrl->SetCursor(cursorModifyShape);
		return;
	}



	//如果现在图形是空的，则进入选择状态
	if(pEdit->m_modifyGeometrys.empty() 
		&& m_nStatus!=On_SelectMoreShape
		&&  m_nStatus!=On_MoveMoreShape)
	{
		m_nStatus = On_None ;   
		return ;
	}

	//如果有选择图形的情况
	if(m_nStatus == On_Selection || m_nStatus == On_Vertex || m_nStatus == On_Line||m_nStatus == On_Inside)
	{
		if(pEdit->m_modifyGeometrys.empty())
		{
			return ;
		}
		double dblTol;
		long ltol =(double)m_dTolerance;

		pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(ltol,dblTol);

		GEOMETRY::geom::Coordinate pt;
		pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,pt.x,pt.y);

		GEOMETRY::geom::Coordinate coord;

		GEOMETRY::geom::Coordinate outpt;
		double  distance;
		long lpart,lverindex;
		//鼠标是否在节点上
		for(size_t i=0;i<pEdit->m_modifyGeometrys.size();i++)
		{
			coord.x = pt.x;
			coord.y = pt.y;
			if(pEdit->m_modifyGeometrys[i]->SnapVertex(&coord,dblTol,&outpt,&distance,&lpart,&lverindex))
			{
				
				m_nStatus =On_Vertex;
				pMapCtrl->SetCursor(cursorOnVertix);

				m_curPart =lpart;
				m_curVertexIndex =lverindex;

				m_curVertex =outpt;
				return;
			}

			//是否在线上
			if(pEdit->m_modifyGeometrys[i]->SnapEdgePoint(&coord,dblTol,&outpt,&distance,&lpart,&lverindex))
			{
				m_nStatus=On_Line;
				
				pMapCtrl->SetCursor(cursorOnLine);

				m_insertPt.x =outpt.x;
				m_insertPt.y =outpt.y;

				m_curPart =lpart;
				m_curVertexIndex =lverindex;
				return;
			}
			//如果是多边形，则判断是否在图形内
			long type =pEdit->m_modifyGeometrys[i]->getGeometryTypeId();

			if(type==GEOS_POLYGON || type==GEOS_MULTIPOLYGON)
			{
				Geometry *pPoint =(Geometry*)GeometryFactory::getDefaultInstance()->createPoint(Coordinate(pt.x,pt.y));

				m_bContain =false;

				if(pEdit->m_modifyGeometrys[i]->contains(pPoint))
				{
					m_bContain =true;

				}


				if(m_bContain)
				{
					m_nStatus=On_Inside;
					pMapCtrl->SetCursor(cursorSizeAll);
					delete pPoint;
					return;
				}

				delete pPoint;
			}

		}
		//如果鼠标不在节点上或者线上，则重新把状态设为On_Selection
		m_nStatus=On_Selection;
		
		pMapCtrl->SetCursor(cursorModifyShape);
	}
	else if(m_nStatus ==On_VertexMove )
	{
		pMapCtrl->SetCursor(cursorOnVertix);

		//移动当前节点
		GEOMETRY::geom::Coordinate pt;
		pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,pt.x,pt.y);

		GEOMETRY::geom::Coordinate outPt;
		//捕捉
		pEdit->Snap(pt,outPt);


		GEOMETRY::geom::Geometry *pGeometry =pEdit->m_modifyGeometrys[0];

		long ltype =pGeometry->getGeometryTypeId();

		switch(ltype)
		{
		case GEOS_POINT:
		case GEOS_LINESTRING:

			pGeometry->ReplacePoint(m_curVertexIndex,outPt);
			break;

		case GEOS_MULTIPOINT:
		case GEOS_MULTILINESTRING:
			{
				//找到编辑的哪一部分的图形
				GEOMETRY::geom::Geometry *pMoveGeometry =const_cast<Geometry*>(((GeometryCollection*)pGeometry)->getGeometryN(m_curPart));
				if(pMoveGeometry!=NULL)
				{
					pMoveGeometry->ReplacePoint(m_curVertexIndex,outPt);
				}
				break;
			}
		case GEOS_POLYGON:
			{
				//找到编辑的哪一部分的图形
				GEOMETRY::geom::Geometry *pMoveGeometry =((GEOMETRY::geom::Polygon *)pGeometry)->GetGeometry(m_curPart);
				if(pMoveGeometry!=NULL)
				{
					pMoveGeometry->ReplacePoint(m_curVertexIndex,outPt);
				}
			}
			break;

		default:
			break;
		}


		pMapCtrl->UpdateControl(drawEdit);

	}
	//shape移动
	else if(m_nStatus == On_ShapeMove)
	{
		pMapCtrl->SetCursor(cursorSizeAll);

		if(m_lastmovePt!=point)
		{

			double dx ,dy;
			pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x-m_lastmovePt.x,dx);

			pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_lastmovePt.y-point.y,dy);
			
			GEOMETRY::geom::Geometry *pGeometry =pEdit->m_modifyGeometrys[0];

			pGeometry->Move(dx,dy);

			pMapCtrl->UpdateControl(drawEdit);
			m_lastmovePt =point;

			m_bMoved =true;
		}



	}
	//选中了多个图形
	else if(m_nStatus == On_SelectMoreShape)
	{
		
		GEOMETRY::geom::Coordinate pt;
		pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,pt.x,pt.y);

		GEOMETRY::geom::Geometry *pPoint =(GEOMETRY::geom::Geometry*)
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(pt);

		m_bContain =false;
		for(size_t i=0;i<pEdit->m_modifyGeometrys.size();i++)
		{
			//点是否在要素之内
			if(pEdit->m_modifyGeometrys[i]->contains(pPoint))
			{
				m_bContain =true;
				break;
			}


		}

		if(m_bContain)
		{
			pMapCtrl->SetCursor(cursorSizeAll);
		}
		else
		{
			pMapCtrl->SetCursor(cursorModifyShape);
		}


	}
	//移动多个图形
	else if(m_nStatus == On_MoveMoreShape)
	{
		pMapCtrl->SetCursor(cursorSizeAll);

		if(m_lastmovePt!=point)
		{

			double dx=0 ,dy=0;
			pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x-m_lastmovePt.x,dx);

			pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(m_lastmovePt.y-point.y,dy);
			for(size_t i=0;i<pEdit->m_modifyGeometrys.size();i++)
			{
				//对每个图形进行移动
				pEdit->m_modifyGeometrys[i]->Move(dx,dy);
			}

			DrawMovedGeometrys();

			m_lastmovePt =point;

			m_bMoved =true;
		}

	}

}