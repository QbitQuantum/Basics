//////////////////
// Get size information for a single entry (WINRECT). Returns size info in
// the SIZEINFO argument. For a group, calculate size info as aggregate of
// subentries.
//
void CWinMgr::OnGetSizeInfo(SIZEINFO& szi, WINRECT* wrc, CWnd* pWnd) {
	szi.szMin = SIZEZERO;				// default min size = zero
	szi.szMax = SIZEMAX;					// default max size = infinite
	szi.szDesired = wrc->GetRect().Size();	// default desired size = current 

	if (wrc->IsGroup()) {
		// For groups, calculate min, max, desired size as aggregate of children
		szi.szDesired = SIZEZERO;
		BOOL bRow = wrc->IsRowGroup();

		CWinGroupIterator it;
		for (it=wrc; it; it.Next()) {
			WINRECT* wrc2 = it;
			SIZEINFO szi2;
			OnGetSizeInfo(szi2, wrc2, pWnd);
			if (bRow) {
				szi.szMin.cx = max(szi.szMin.cx, szi2.szMin.cx);
				szi.szMin.cy += szi2.szMin.cy;
				szi.szMax.cx = min(szi.szMax.cx, szi2.szMax.cx);
				szi.szMax.cy = min(szi.szMax.cy + szi2.szMax.cy, _INFINITY);
				szi.szDesired.cx = max(szi.szDesired.cx, szi2.szDesired.cx);
				szi.szDesired.cy += szi2.szDesired.cy;

			} else {
				szi.szMin.cx += szi2.szMin.cx;
				szi.szMin.cy = max(szi.szMin.cy, szi2.szMin.cy);
				szi.szMax.cx = min(szi.szMax.cx + szi2.szMax.cx, _INFINITY);
				szi.szMax.cy = min(szi.szMax.cy, szi2.szMax.cy);
				szi.szDesired.cx += szi2.szDesired.cx;
				szi.szDesired.cy = max(szi.szDesired.cy, szi2.szDesired.cy);
			}
		}

		// Add margins. 
		int w2,h2;
		wrc->GetMargins(w2,h2);			// get margins
		w2<<=1; h2<<=1;					// double
		szi.szMin.cx += max(0,w2);		// negative margins ==> don't include in min
		szi.szMin.cy += max(0,h2);		// ditto
		szi.szDesired.cx += abs(w2);	// for desired size, use abs vallue
		szi.szDesired.cy += abs(h2);	// ditto

	} else {
		// not a group
		WINRECT* parent = wrc->Parent();
		ASSERT(parent);
		CRect& rcParent = parent->GetRect();
		BOOL bRow = parent->IsRowGroup();
		int hw, hwMin, hwTotal, pct;

		switch (wrc->Type()) {
		case WRCT_FIXED:
			hw = hwMin = wrc->GetParam();	 // ht/wid is parameter
			if (hw<0) {							 // if fixed val is negative:
				hw = -hw;						 // use absolute val for desired..
				hwMin = 0;						 // ..and zero for minimum
			}
			if (bRow) {
				szi.szMax.cy = szi.szDesired.cy = hw;
				szi.szMin.cy = hwMin;
			} else {
				szi.szMax.cx = szi.szDesired.cx = hw;
				szi.szMin.cx = hwMin;
			}
			break;

		case WRCT_PCT:
			pct = wrc->GetParam();
			ASSERT(0<pct && pct<100);
			hwTotal = bRow ? rcParent.Height() : rcParent.Width();
			hw = (hwTotal * pct) / 100;
			szi.szDesired = bRow ? CSize(rcParent.Width(), hw) :
				CSize(hw, rcParent.Height());
			break;

		case WRCT_TOFIT:
			if (wrc->HasToFitSize()) {
				szi.szDesired = wrc->GetToFitSize();
			}
			break;

		case WRCT_REST:
			break;

		default:
			ASSERT(FALSE);
		}

		// If the entry is a window, send message to get min/max/tofit size.
		// Only set tofit size if type is TOFIT.
		//
		if (wrc->IsWindow() && pWnd) {
			CWnd* pChild = pWnd->GetDlgItem(wrc->GetID());
			if (pChild) {
				if (!pChild->IsWindowVisible() && pWnd->IsWindowVisible()) {
					// parent visible but child not ==> tofit size is zero
					// important so hidden windows use no space
					szi.szDesired = SIZEZERO;
				} else {
					szi.szAvail = rcParent.Size();
					SendGetSizeInfo(szi, pWnd, wrc->GetID());
				}
			}
		}
		szi.szDesired = maxsize(minsize(szi.szDesired,szi.szMax), szi.szMin);
	}
}