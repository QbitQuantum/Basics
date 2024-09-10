void CSkinUnitODL::DrawImage(Gdiplus::Graphics& gcDrawer, Gdiplus::GraphicsPath& gcPath, Gdiplus::PointF& ptOffset, Gdiplus::REAL fScale)
{
	if (m_imgSkin)
	{
		if (m_nWrapMode>=4)
		{
			//居中模式
			Gdiplus::RectF rtArea;
			gcPath.GetBounds(&rtArea);
			Gdiplus::GraphicsPath gcDrawPath;
			//图片中间X：(width-imagewidth )/2 + left;
			//Y: (height - imageheight)/2 +top;

			Gdiplus::REAL fX0 = (rtArea.Width - m_fSkinWidth-m_nGroutX) /2.0f + rtArea.X;
			Gdiplus::REAL fY0 = (rtArea.Height - m_fSkinHeight-m_nGroutY) /2.0f + rtArea.Y;
			Gdiplus::REAL fX1 = m_fSkinWidth + m_nGroutX+ fX0;
			Gdiplus::REAL fY1 = m_fSkinHeight +m_nGroutY+ fY0;
			std::vector<Gdiplus::PointF> arrPt;
			arrPt.emplace_back(fX0, fY0);
			arrPt.emplace_back(fX1, fY0);
			arrPt.emplace_back(fX1, fY1);
			arrPt.emplace_back(fX0, fY1);
			Gdiplus::Matrix mx;
			Gdiplus::PointF ptCenter=Gdiplus::PointF((fX1+fX0)/2.0f, (fY1+fY0)/2.0f);
			mx.RotateAt(m_fRotate, ptCenter);
			mx.TransformPoints(arrPt.data(), arrPt.size());
			gcDrawPath.AddPolygon(arrPt.data(),arrPt.size());
			//如果图片的path大于当前区域Path，则居中操作在区域内
			{
				BRepBuilderAPI_MakePolygon ply1;
				for (auto& ptPos:arrPt)
				{
					ply1.Add(gp_Pnt(ptPos.X, 0.0f, ptPos.Y));
				}
				ply1.Close();
				TopoDS_Face face1 = BRepBuilderAPI_MakeFace(ply1.Wire()).Face();
				std::vector<Gdiplus::PointF> arrPic;
				arrPic.resize(gcDrawPath.GetPointCount());
				gcPath.GetPathPoints(arrPic.data(), arrPic.size());

				BRepBuilderAPI_MakePolygon ply2;
				for (auto& ptPos:arrPic)
				{
					ply2.Add(gp_Pnt(ptPos.X, 0.0f, ptPos.Y));
				}
				ply2.Close();
				TopoDS_Face face2 = BRepBuilderAPI_MakeFace(ply2.Wire()).Face();

				BRepAlgoAPI_Common bc(face1, face2);
				auto face = bc.Shape();
				TopExp_Explorer expWire(face, TopAbs_WIRE);
				std::vector<Gdiplus::PointF> arrDraw;
				for ( BRepTools_WireExplorer expVertex(TopoDS::Wire(expWire.Current())); expVertex.More(); expVertex.Next() )
				{
					auto pnt = BRep_Tool::Pnt(expVertex.CurrentVertex());
					arrDraw.emplace_back(static_cast<Gdiplus::REAL>(pnt.X()), static_cast<Gdiplus::REAL>(pnt.Z()));
				}
				gcDrawPath.Reset();
				gcDrawPath.AddPolygon(arrDraw.data(), arrDraw.size());
			}

			Gdiplus::WrapMode wmMode=(Gdiplus::WrapMode)m_nWrapMode;
			if (std::fabs(m_fRotate)<0.001f)
			{
				Gdiplus::TextureBrush brush(m_imgSkin, wmMode);
				mx.Translate(fX0, fY0);
				brush.SetTransform(&mx);
				gcDrawer.FillPath(&brush, &gcDrawPath);
			}
			else
			{
				Gdiplus::TextureBrush brush(m_imgSkin, wmMode);
				mx.Translate(fX0, fY0);
				brush.SetTransform(&mx);
				gcDrawer.FillPath(&brush, &gcDrawPath);
			}
		}
		else
		{
			//铺满模式
			Gdiplus::WrapMode wmMode=(Gdiplus::WrapMode)m_nWrapMode;
			if (std::fabs(m_fRotate)<0.001f)
			{
				Gdiplus::TextureBrush brush(m_imgSkin, wmMode);
				brush.TranslateTransform(ptOffset.X, ptOffset.Y);
				gcDrawer.FillPath(&brush, &gcPath);
			}
			else
			{
				Gdiplus::TextureBrush brush(m_imgSkin, wmMode);
				brush.TranslateTransform(ptOffset.X, ptOffset.Y);
				brush.RotateTransform(m_fRotate);
				gcDrawer.FillPath(&brush, &gcPath);
			}
		}
		
	}
}