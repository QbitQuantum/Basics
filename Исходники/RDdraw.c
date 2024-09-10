void DrawBar(DRAWSTRUCT *ds,HDC hdc,RECT *ptrBarRect,
             int DataValue,int MaxValue,BOOL Selected)
{
    RECT rc;
    HBRUSH oldbrush,barbrush;
    HPEN oldpen;
    COLORREF oldbkcolor;
	int cx;

	CopyRect(&rc,ptrBarRect);

    if(Selected)
    {
        FillRect (hdc, &rc, ds->HighBrush);
        oldpen = SelectObject (hdc, ds->g_unseltextpen);
    }
    else
    {
        FillRect (hdc, &rc, ds->BackBrush);
        oldpen = SelectObject (hdc, ds->g_seltextpen);
    }

    rc.top+=5;
    rc.left+=5;
    rc.bottom-=5;
    rc.right-=5;

	if(rc.right<=rc.left)
		return;

	cx=rc.right-rc.left;

	oldbrush = SelectObject (hdc, ds->barbgbrush);
	SelectObject (hdc, ds->buttonpen);

	Rectangle (hdc, rc.left - 1, rc.top - 1, 
		rc.right + 2, rc.bottom + 2);

	SelectObject (hdc, ds->shadowpen);
	MoveToEx (hdc, rc.left, rc.bottom, NULL);
	LineTo (hdc, rc.left, rc.top);
	LineTo (hdc, rc.right, rc.top);

	SelectObject (hdc, ds->hilightpen);
	LineTo (hdc, rc.right, rc.bottom);
	LineTo (hdc, rc.left, rc.bottom);
														
	if (MaxValue != 0) 
	{
		if (DataValue > MaxValue) 
		{
			barbrush = ds->spcbarbrush;
			rc.right = rc.left + cx;
		}
		else 
		{
			barbrush = ds->stdbarbrush;
			rc.right = rc.left + 
				(int)(((float)DataValue / 
				(float)MaxValue)
				* (float)cx);
		}
	}
	else 
		rc.right = rc.left;

	rc.top++;
	rc.left++;

	if (rc.right > rc.left) 
	{
		oldbkcolor=SetBkColor (hdc, ds->barcolor);
		FillRect (hdc, &rc, barbrush); 

		rc.top--;
		rc.left--;

		// hilight pen already selected 
		MoveToEx (hdc, rc.right, rc.top, NULL);
		LineTo (hdc, rc.left, rc.top);
		LineTo (hdc, rc.left,rc.bottom);

		SelectObject (hdc, ds->shadowpen);
		LineTo (hdc, rc.right, rc.bottom);
		LineTo (hdc, rc.right, rc.top);
		SetBkColor(hdc,oldbkcolor);
	}

	SelectObject (hdc, oldbrush);
	SelectObject (hdc, oldpen);
}