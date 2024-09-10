//-----------------------------------------------------------------------------
// Purpose: 
// Input  : pView - 
//			nFlags - 
//			point - 
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool Marker3D::OnMouseMove2D(CMapView2D *pView, UINT nFlags, CPoint point)
{
	CMapDoc *pDoc = pView->GetDocument();
	if (!pDoc)
	{
		return false;
	}

	bool bCursorSet = false;
	unsigned int uConstraints = 0;
	if ((GetAsyncKeyState(VK_MENU) & 0x8000))
	{
		uConstraints |= Tool3D::constrainNosnap;
	}
					    
	//
	// Make sure the point is visible.
	//
	if (m_bLButtonDown)
	{
		pView->ToolScrollToPoint(point);
	}

	//
	// Convert to some odd coordinate space that the base tools code uses.
	//
  	CPoint ptHitTest = point;
	ptHitTest.x += pView->GetScrollPos(SB_HORZ);
	ptHitTest.y += pView->GetScrollPos(SB_VERT);

	//
	// Convert to world coords.
	//
	Vector vecWorld;
	pView->ClientToWorld(vecWorld, point);
	point.x = vecWorld[axHorz];
	point.y = vecWorld[axVert];

	//
	// Update status bar position display.
	//
	char szBuf[128];
	m_pDocument->Snap(vecWorld);
	sprintf(szBuf, " @%.0f, %.0f ", vecWorld[axHorz], vecWorld[axVert]);
	SetStatusText(SBI_COORDS, szBuf);

	//
	// If we are currently dragging the marker, update that operation based on
	// the current cursor position and keyboard state.
	//
	if (IsTranslating())
	{
		if (UpdateTranslation(point, uConstraints, CSize(0,0)))
		{
			pDoc->ToolUpdateViews(CMapView2D::updTool);
			pDoc->Update3DViews();
		}

		// Don't change the cursor while dragging - it should remain a cross.
		bCursorSet = true;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	}
	else if (!IsEmpty())
	{
		// Don't change the cursor while dragging - it should remain a cross.
		bCursorSet = true;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	}

	if (!bCursorSet)
	{
		SetCursor(s_hcurEntity);
	}

	return true;
}