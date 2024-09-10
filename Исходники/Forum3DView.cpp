FORUM3DVIEW_EXPORT BOOL __stdcall SCForumMdl3DDraw( HDC hDC, const RECT * r, LPCTSTR sFileName, LPCTSTR sWorkDir, int nDrawFlags, HANDLE hStopEvent )
{
	S3DBox			Box;
	SParallelView			View;
	CRotator		Rot;
	CRect			Region(r);

	TCHAR Path[MAXPATH];
	_tcscpy_s(Path, sFileName);
	PathRemoveFileSpec(Path);
	CThumbCashe cashe(Path);
	SThumbParam param;
	param.nWidth = WORD(r->right-r->left);
	param.nHeight = WORD(r->bottom-r->top);
	param.eType = ThumbProjection;
	if (cashe.Get(PathFindFileName(sFileName), param, hDC))
		return TRUE;
	
	if (_tcsicmp(PathFindExtension(sFileName),_T(".mp4"))==0)
	{
		return FALSE;
	}
	CForumViewGeometry fvg(nullptr,nullptr);
	fvg.m_bForThumbs = true;
	fvg.m_bDeleteInnerPlates = false;
	if(!fvg.LoadFromFile(sFileName, 0, 0, false))
		return FALSE;
	//fvg.ClearCashe();
	fvg.DrawOptionsChanged(nullptr, true); // Show only used nodes
	Rot.SetPredefinedView(ThumbProjection);
	fvg.Get3DBox(&Rot, &Box);
	View.GeometryZoomAll(&Region, 5, &Box);

	Graphics::TColor	cOld = TColor(0);
	HPEN				hPen, hPenOld;

	hPen = CreatePen(PS_SOLID, 0, cOld);
	hPenOld = HPEN(SelectObject(hDC, hPen));

	int cx = (Region.left + Region.right) / 2, cy = (Region.top + Region.bottom) / 2;
	size_t NumElements = fvg.ElementArray.size();
	for(size_t i = 0; i < NumElements /*&& !Terminated*/; i++)
	{
		//int Percent = (k) * 100.0 / nFiles + (i + 1) * 100.0 / (2 * nFiles * NumElements);

		if (::WaitForSingleObject(hStopEvent,0) == WAIT_OBJECT_0)
		{
			::SetEvent(hStopEvent);
			SelectObject(hDC, hPenOld);
			DeleteObject(hPen);
			return FALSE;
		}
		CViewElement		El = fvg.ElementArray[i];
		Graphics::TColor	c = El.Color;

		if(c != cOld)
		{
			SelectObject(hDC, hPenOld);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 0, c);
			hPenOld = HPEN(SelectObject(hDC, hPen));
		}

		int				NumPoints = El.NumVertexs();
		if (!El.bContoured)
			continue;
		NODE_NUM_TYPE pn0 = El.Points[0];
		S3dPoint		p1 = S3dPoint(fvg.VertexArray[pn0]);
		Rot.Rotate(p1.x, p1.y, p1.z);
		MoveToEx(hDC, TO_SCR_X(p1.x), TO_SCR_Y(p1.y), nullptr);
		for(int j = 1; j < NumPoints; j++)
		{
			NODE_NUM_TYPE	pn = El.Points[j];
			S3dPoint		p = S3dPoint(fvg.VertexArray[pn]);
			Rot.Rotate(p.x, p.y, p.z);
//			if(!fvg.WasDrawed(pn1, pn))
				LineTo(hDC, TO_SCR_X(p.x), TO_SCR_Y(p.y));
/*
			else
				MoveToEx(hDC, TO_SCR_X(p.x), TO_SCR_Y(p.y), NULL);
*/
		}

//		if(!fvg.WasDrawed(pn0, pn1))
			LineTo(hDC, TO_SCR_X(p1.x), TO_SCR_Y(p1.y));
	}

	SelectObject(hDC, hPenOld);
	DeleteObject(hPen);
	cashe.Put(PathFindFileName(sFileName), param, hDC);
	
	return TRUE;
}