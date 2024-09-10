/*
 * mark the selected line, if visible, in the style chosen by the
 * client app. This can be TM_SOLID, meaning an inversion of
 * the whole selected area or TM_FOCUS, meaning, inversion of the first
 * cell, and then a dotted focus rectangle for the rest.
 *
 * this function inverts either style, and so will turn the selection
 * both on and off.
 */
void
gtab_invertsel(HWND hwnd, lpTable ptab, HDC hdc_in)
{
	HDC hdc;
	int firstline, lastline;
	long startrow, lastrow, toprow, bottomrow;
	RECT rc;
	int lastcell;



	/* get the selection start and end rows ordered vertically */
	if (ptab->select.nrows == 0) {
	    return;
	} else if (ptab->select.nrows < 0) {
	    startrow = ptab->select.startrow + ptab->select.nrows + 1;
	    lastrow = ptab->select.startrow;
	} else {
	    startrow = ptab->select.startrow;
	    lastrow = ptab->select.startrow + ptab->select.nrows -1;
	}

	/* is selected area (or part of it) visible on screen ?  */
	firstline = gtab_rowtoline(hwnd, ptab, startrow);
	lastline = gtab_rowtoline(hwnd, ptab, lastrow);


	if (firstline < 0) {
	    toprow = gtab_linetorow(hwnd, ptab,
	    		ptab->hdr.fixedselectable ? 0: ptab->hdr.fixedrows);
	    if ((toprow >= startrow)  &&
		(toprow <= lastrow)) {
		    firstline = gtab_rowtoline(hwnd, ptab, toprow);
	    } else {
		return;
	    }
	} else {
	    toprow = 0;
	}


	if (lastline < 0) {
	    bottomrow = gtab_linetorow(hwnd, ptab, ptab->nlines-1);
	    if ((bottomrow <= lastrow) &&
		(bottomrow >=startrow)) {
		    lastline = gtab_rowtoline(hwnd, ptab, bottomrow);
	    } else {
		return;
	    }
	}


	rc.top = ptab->pdata[firstline].linepos.clipstart;
	rc.bottom = ptab->pdata[lastline].linepos.clipend;



	/* selection mode includes a flag TM_FOCUS indicating we should
	 * use a focus rect instead of the traditional inversion for
	 * selections in this table. This interferes with multiple backgrnd
	 * colours less.  However we still do inversion for fixedcols.
	 */

	lastcell = (int)(ptab->select.startcell + ptab->select.ncells - 1);


	/*
	 * invert the whole area for TM_SOLID or just the first
	 * cell for TM_FOCUS
	 */
	rc.left = ptab->pcellpos[ptab->select.startcell].clipstart;
	if (ptab->hdr.selectmode & TM_FOCUS) {
		rc.right = ptab->pcellpos[ptab->select.startcell].clipend;
	}else {
		rc.right = ptab->pcellpos[lastcell].clipend;
	}

	if (hdc_in == NULL) {
		hdc = GetDC(hwnd);
	} else {
		hdc = hdc_in;
	}

	InvertRect(hdc, &rc);

	/*
	 * draw focus rectangle around remaining cells on this line, if there
	 * are any
	 */
	if (ptab->hdr.selectmode & TM_FOCUS) {
		/*
		 * now this is a real fudge. if we are drawing TM_FOCUS
		 * selection, and the real top line is off the top of the
		 * window, then the top of the focus rect will be drawn at
		 * the top of our window. If we then scroll up one line,
		 * a new focus rect will be drawn, but the old top of focus
		 * rect line will still be there as junk on the
		 * screen. To fix this, we have 2 choices: we undo the selection
		 * before every scroll (too slow) or we set the focus rect a little
		 * bigger if the real top line is off-window, so that the top line
		 * is clipped (as it should be). This latter is what we do here
		 */
		if (toprow > startrow) {
		    rc.top--;
		}
		if (ptab->select.ncells > 1) {
			rc.left = ptab->pcellpos[ptab->select.startcell+1].clipstart;
			rc.right = ptab->pcellpos[lastcell].clipend;
			DrawFocusRect(hdc, &rc);
		}
	}

	if (hdc_in == NULL) {
		ReleaseDC(hwnd, hdc);
	}
}