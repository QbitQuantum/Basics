LRESULT CObjectsPage::OnEditEnd(WPARAM nItem, LPARAM nSubItem)
{
	// Get item label
	CString label = m_List.GetItemText(nItem, 0);
	CString text = m_List.GetItemText(nItem, nSubItem);

	__int64 iValue = _atoi64(text);
	double fValue = atof(text);

	// Resume updating
	pausedUpdating = false;

	// Check for common labels
	if (pMyObject) {

		if (label == "X")
			pMyObject->info.x = fValue;
		else if (label == "Y")
			pMyObject->info.y = fValue;
		else if (label == "Width")
			pMyObject->info.w = fValue;
		else if (label == "Height")
			pMyObject->info.h = fValue;
		else if (label == "Angle")
			pMyObject->info.angle = fValue;
		else if (label == "Opacity") {
			pMyObject->info.pInfo->filter.a = fValue / 100.0f;
		}
		
		// Work out which object owned the edited line
		CRunObject* lineOwner = lineOwners[nItem];
		if (lineOwner)
			lineOwner->OnDebuggerValueChanged(label, text);

		// Update bounding box for non system objects
		if (pMyObject->pType != NULL)
			pRuntime->UpdateBoundingBox(pMyObject);
	}

	// Save scroll position
	int nScroll = m_List.GetScrollPos(SB_VERT);

	// Force full refresh by clearing old display
	objDebugDisplay.resize(0);
	RefreshInspection();

	// Restore scroll position
	m_List.SetSelectionMark(nItem);
	m_List.SetCurSel(nItem, TRUE);
	m_List.SetScrollPos(SB_VERT, nScroll, TRUE);

	return 0;
}