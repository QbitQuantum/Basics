	void CUnit::OnShowSelectedLine(){
		//畫圓圈
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC

		CPen penBlack;
		CPen penWhite;
		CPen* pOldPen;
		penBlack.CreatePen(PS_SOLID,1,RGB(0,0,0));
		penWhite.CreatePen(PS_SOLID,1,RGB(255,255,255));
		pOldPen = pDC->SelectObject(&penBlack);
		CRect rect;
		CPoint screenPoint(CConvert::GetScreenPointByMapPoint(mapPoint));
		rect.SetRect(	screenPoint.x-bmp->Width()/2-10,
						screenPoint.y-25,
						screenPoint.x+bmp->Width()/2+10,
						screenPoint.y+5);
		pDC->Arc(rect,rect.TopLeft(),rect.TopLeft());
		rect.MoveToY(rect.top+1);
		pDC->SelectObject(&penWhite);
		pDC->Arc(rect,rect.TopLeft(),rect.TopLeft());
		pDC->SelectObject(pOldPen);						//
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}