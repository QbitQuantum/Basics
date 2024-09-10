void EyeXHost::HandleQuery(TX_CONSTHANDLE hAsyncData)
{
	std::lock_guard<std::mutex> lock(_mutex);

	// NOTE. This method will fail silently if, for example, the connection is lost before the snapshot has been committed, 
	// or if we run out of memory. This is by design, because there is nothing we can do to recover from these errors anyway.

	TX_HANDLE hQuery = TX_EMPTY_HANDLE;
	txGetAsyncDataContent(hAsyncData, &hQuery);

	const int bufferSize = 20;
	TX_CHAR stringBuffer[bufferSize];

	// read the query bounds from the query, that is, the area on the screen that the query concerns.
	// the query region is always rectangular.
	TX_HANDLE hBounds(TX_EMPTY_HANDLE);
	txGetQueryBounds(hQuery, &hBounds);
	TX_REAL pX, pY, pWidth, pHeight;
	txGetRectangularBoundsData(hBounds, &pX, &pY, &pWidth, &pHeight);
	txReleaseObject(&hBounds);
	Gdiplus::Rect queryBounds((INT)pX, (INT)pY, (INT)pWidth, (INT)pHeight);

	// create a new snapshot with the same window id and bounds as the query.
	TX_HANDLE hSnapshot(TX_EMPTY_HANDLE);
	txCreateSnapshotForQuery(hQuery, &hSnapshot);

	TX_CHAR windowIdString[bufferSize];
	sprintf_s(windowIdString, bufferSize, WINDOW_HANDLE_FORMAT, _hWnd);

	if (QueryIsForWindowId(hQuery, windowIdString))
	{
		// define options for our activatable regions: no, we don't want tentative focus events.
		TX_ACTIVATABLEPARAMS params;
		params.EnableTentativeFocus = TX_FALSE;

		// iterate through all regions and create interactors for those that overlap with the query bounds.
		for (auto region : _regions)
		{
			Gdiplus::Rect regionBounds((INT)region.bounds.left, (INT)region.bounds.top, 
				(INT)(region.bounds.right - region.bounds.left), (INT)(region.bounds.bottom - region.bounds.top));

			if (queryBounds.IntersectsWith(regionBounds))
			{
				TX_HANDLE hInteractor(TX_EMPTY_HANDLE);
				sprintf_s(stringBuffer, bufferSize, "%d", region.id);

				TX_RECT bounds;
				bounds.X = region.bounds.left; 
				bounds.Y = region.bounds.top;
				bounds.Width = region.bounds.right - region.bounds.left;
				bounds.Height = region.bounds.bottom - region.bounds.top;

				txCreateRectangularInteractor(hSnapshot, &hInteractor, stringBuffer, &bounds, TX_LITERAL_ROOTID, windowIdString);
				txCreateActivatableBehavior(hInteractor, &params);

				txReleaseObject(&hInteractor);
			}
		}
	}

	txCommitSnapshotAsync(hSnapshot, OnSnapshotCommitted, nullptr);
	txReleaseObject(&hSnapshot);
	txReleaseObject(&hQuery);
}