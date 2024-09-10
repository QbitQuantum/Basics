void VDPositionControlW32::OnPaint() {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(mhwnd, &ps);

	if (!hdc)		// hrm... this is bad
		return;

	HGDIOBJ hOldFont = SelectObject(hdc, mFrameNumberFont);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, GetSysColor(COLOR_WINDOWTEXT));
	SetTextAlign(hdc, TA_TOP | TA_CENTER);

	char buf[64];
	RECT rClient;

	VDVERIFY(GetClientRect(mhwnd, &rClient));

	int trackRight = mTrack.right;

	HGDIOBJ hOldPen = SelectObject(hdc, GetStockObject(BLACK_PEN));

	// Determine digit spacing.
	int labelDigits = mRangeEnd > 0 ? (int)floor(log10((double)mRangeEnd)) + 1 : 1;
	int labelWidth = (labelDigits + 1) * mFrameNumberWidth;		// Add 1 digit for nice padding.
	sint64 framesPerLabel = 1;

	if (mRangeEnd > mRangeStart) {
		while(framesPerLabel * mPixelsPerFrame < labelWidth) {
			sint64 fpl2 = framesPerLabel + framesPerLabel;

			if (fpl2 * mPixelsPerFrame >= labelWidth) {
				framesPerLabel = fpl2;
				break;
			}

			sint64 fpl5 = framesPerLabel * 5;
			if (fpl5 * mPixelsPerFrame >= labelWidth) {
				framesPerLabel = fpl5;
				break;
			}

			framesPerLabel *= 10;
		}
	}

	sint64 frame = mRangeStart;
	bool bDrawLabels = ps.rcPaint.bottom >= mTrackArea.bottom;

	while(frame < mRangeEnd) {
		int x = FrameToPixel(frame);

		const RECT rTick = { x, mTickArea.top, x+1, mTickArea.bottom };
		FillRect(hdc, &rTick, mBrushes[kBrushTick]);

		if (x > trackRight - labelWidth)
			break;		// don't allow labels to encroach last label

		if (bDrawLabels) {
			sprintf(buf, "%I64d", frame);
			TextOut(hdc, x, mTrackArea.bottom, buf, strlen(buf));
		}

		frame += framesPerLabel;
	}

	const RECT rLastTick = { mTrack.right, mTrack.bottom, mTrack.right+1, mTrackArea.bottom };
	FillRect(hdc, &rLastTick, mBrushes[kBrushTick]);

	if (bDrawLabels) {
		sprintf(buf, "%I64d", mRangeEnd);
		TextOut(hdc, trackRight, mTrackArea.bottom, buf, strlen(buf));
	}

	// Fill the track.  We draw the track borders later so they're always on top.
	FillRect(hdc, &mTrack, mBrushes[kBrushTrack]);

	// Draw selection and ticks.
	if (mSelectionEnd >= mSelectionStart) {
		int selx1 = FrameToPixel(mSelectionStart);
		int selx2 = FrameToPixel(mSelectionEnd);

		RECT rSel={selx1, mTrack.top, selx2, mTrack.bottom};

		if (rSel.right == rSel.left)
			++rSel.right;

		FillRect(hdc, &rSel, mBrushes[kBrushSelection]);

		if (HPEN hNullPen = CreatePen(PS_NULL, 0, 0)) {
			if (HGDIOBJ hLastPen = SelectObject(hdc, hNullPen)) {
				if (HGDIOBJ hOldBrush = SelectObject(hdc, GetStockObject(BLACK_BRUSH))) {
					const int tickHeight = mTickArea.bottom - mTickArea.top;

					const POINT pts1[3]={
						{ selx1+1, mTickArea.top },
						{ selx1+1, mTickArea.bottom },
						{ selx1+1-tickHeight, mTickArea.top },
					};

					const POINT pts2[3]={
						{ selx2, mTickArea.top },
						{ selx2, mTickArea.bottom },
						{ selx2+tickHeight, mTickArea.top },
					};

					Polygon(hdc, pts1, 3);
					Polygon(hdc, pts2, 3);

					SelectObject(hdc, hOldBrush);
				}

				SelectObject(hdc, hLastPen);
			}
			DeleteObject(hNullPen);
		}
	}

	// Draw track border.
	const int xedge = GetSystemMetrics(SM_CXEDGE);
	const int yedge = GetSystemMetrics(SM_CYEDGE);
	RECT rEdge = mTrack;
	InflateRect(&rEdge, xedge, yedge);

	DrawEdge(hdc, &rEdge, EDGE_SUNKEN, BF_RECT);

	// Draw cursor.
	RECT rThumb = mThumbRect;

	DrawEdge(hdc, &rThumb, EDGE_RAISED, BF_SOFT|BF_RECT|BF_ADJUST);
	DrawEdge(hdc, &rThumb, EDGE_SUNKEN, BF_SOFT|BF_RECT|BF_ADJUST);

	// All done.
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldFont);
	EndPaint(mhwnd, &ps);
}