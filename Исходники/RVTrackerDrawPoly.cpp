BOOL CRVTrackerDrawPoly::OnRotate()
{
	// Get the brush
	CEditBrush *pBrush = &m_pView->DrawingBrush();

	// Make sure we've got at least three points specified
	if (pBrush->m_Points.GetSize() < 3)
		return FALSE;

	// The origin's point #1
	CVector vOrigin = pBrush->m_Points[0];
	// The original rotation direction's point #2
	CVector vBase = pBrush->m_Points[1];
	// The new rotation's point #3
	CVector vNew = pBrush->m_Points[2];

	// Get the base direction
	CVector vBaseDir = vBase - vOrigin;
	float fBaseMag = vBaseDir.Mag();
	// Don't allow duplicate points
	if (fBaseMag < 0.01f)
		return TRUE;
	vBaseDir *= 1.0f / fBaseMag;

	// Get the rotation direction
	CVector vNewDir = vNew - vOrigin;
	float fNewMag = vNewDir.Mag();
	// Don't allow duplicate points
	if (fNewMag < 0.01f)
		return TRUE;
	vNewDir *= 1.0f / fNewMag;

	// Get the rotation axis
	CVector vRotAxis = vNewDir.Cross(vBaseDir);

	// Get the sin of the angle from the cross product
	float fRotAngle = vRotAxis.Mag();

	// Don't bother if the angle's 0...
	if (fRotAngle == 0.0f)
		return TRUE;

	// Normalize the axis
	vRotAxis *= 1.0f / fRotAngle;

	// Get the actual angle
	fRotAngle = (float)asin(fRotAngle);

	// Handle obtuse angles..
	if (vBaseDir.Dot(vNewDir) < 0.0f)
		fRotAngle = MATH_PI - fRotAngle;

	LTMatrix mRotation;
	// Get the rotation matrix
	mRotation.SetupRot(vRotAxis, fRotAngle);

	// Set up an undo..
	CEditRegion *pRegion = m_pView->GetRegion();
	PreActionList actionList;
	for (uint32 nUndoLoop = 0; nUndoLoop < pRegion->m_Selections; ++nUndoLoop)
		actionList.AddTail(new CPreAction(ACTION_MODIFYNODE, pRegion->m_Selections[nUndoLoop]));
	m_pView->GetRegionDoc()->Modify(&actionList, TRUE);

	// If we're in geometry mode..
	if (m_pView->GetEditMode() == GEOMETRY_EDITMODE)
	{
		// Get the selected vertices
		CVertRefArray vertList;
		m_pView->GetSelectedVerts(vertList);
		// Rotate 'em
		for (uint32 nVertLoop = 0; nVertLoop < vertList.GetSize(); ++nVertLoop)
		{
			CVertRef vert = vertList[nVertLoop];
			if (!vert.IsValid())
				continue;
			vert() -= vOrigin;
			mRotation.Apply(vert());
			vert() += vOrigin;
		}
	}
	else
	{
		// Otherwise, rotate all the selected nodes
		for (uint32 nNodeLoop = 0; nNodeLoop < pRegion->m_Selections.GetSize( ); ++nNodeLoop)
		{
			pRegion->m_Selections[nNodeLoop]->Rotate(mRotation, vOrigin);
		}

		// Update the selection box since stuff rotated...
		m_pView->GetRegionDoc()->UpdateSelectionBox();
	}

	return TRUE;
}