void CCompositeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CChildFrame* pFrame = DYNAMIC_DOWNCAST( CChildFrame, GetParentFrame() );
	if( !pFrame || !pFrame->IsWindowVisible() )
		return;

	if( !GetDVController() )
		return;

	// update the comparison doc detail sand frame
	CString csTitleBarText;
	CString csComparisonDoc = GetDVController()->GetComparisonDocController().GetComparisonDocumentTitle();
	if (pFrame && !csComparisonDoc.IsEmpty())
	{
		// do not keep setting the title text to the same stuff as it forces the tabctrl to relayout and repaint
		CString existingText;
		pFrame->GetWindowText(existingText);
		if (existingText != csComparisonDoc)
		{
			pFrame->GetDocument()->SetTitle(csComparisonDoc);

			if (csComparisonDoc.GetLength()>40)
			{
				csComparisonDoc = csComparisonDoc.Left(32);
				csComparisonDoc.TrimRight(L" ");
				csComparisonDoc += L"...";
			}
  			pFrame->SetWindowText(csComparisonDoc);
		}
	}
	else
	{
		// do not keep setting the title text to the same stuff as it forces the tabctrl to relayout and repaint
		CString existingText;
		pFrame->GetWindowText(existingText);
		if (existingText!= GetApplicationTitle())
			pFrame->SetWindowText(GetApplicationTitle());
	}
	
	try
	{
		if (GetDocObject())
			GetDocObject()->Repaint();
	}
	catch (...)
	{
		_ASSERTE(!_T("Catch ... How did we get here?"));
	}
	
	UpdateWindow();
}