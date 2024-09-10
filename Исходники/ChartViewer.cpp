static HCURSOR getNoMoveVertCursor()
{
	if (0 == hNoMoveVertCursor)
	{
		hNoMoveVertCursor = CreateCursor(AfxGetApp()->m_hInstance, 15, 15, 32, 32, 
			noMoveVertCursorA, noMoveVertCursorB);
	}
	return hNoMoveVertCursor;
}