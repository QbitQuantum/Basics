void CCellView::ResizeRow(BPoint where, int rowNr)
{
	float y, minY;
	BPoint newP, lastP;
	BRect bounds(Bounds()), r, b;
	BRegion rgn;
	ulong buttons, cnt;
	bool multi;
	int mRow = rowNr;
	CRunArray backup(fCellHeights);
	
	StPenState save(this);
	ClearAnts();
	
	rgn.Include(bounds);

	cnt = fSelection.bottom-fSelection.top+1;

	while (where.y > fCellHeights[rowNr+1]+2)
		rowNr++;

	multi = fSelection.top != fSelection.bottom
					&& rowNr >= fSelection.top
					&& rowNr <= fSelection.bottom;

	if (rowNr <= fFrozen.v)
	{
		y = fBorderHeight+fCellHeights[rowNr];
		minY = fBorderHeight+fCellHeights[multi?fSelection.top-1:rowNr-1];
	}
	else
	{
		y = fBorderHeight+fCellHeights[rowNr]+fCellHeights[fFrozen.v]-
			fCellHeights[fPosition.v-1];
		minY = fBorderHeight+fCellHeights[fFrozen.v]-fCellHeights[fPosition.v-1]+
			fCellHeights[multi?fSelection.top-1:rowNr-1];
	}
	
	r.left = 0;
	r.right = fBorderWidth-1;
	r.top = minY+1;
	if (multi)
		r.bottom = minY+fCellHeights[fSelection.bottom]-
			fCellHeights[fSelection.top-1]-1;
	else
		r.bottom = minY+fCellHeights[rowNr]-fCellHeights[rowNr-1]-1;

	b = bounds;
	b.top = r.bottom;
	
	lastP = where;
	newP = where;
	do
	{
		if (newP.y != lastP.y)
		{
			float dy;
			int k = rowNr;
			
			dy = newP.y - lastP.y;

			if (lastP.y + dy < bounds.top + fBorderHeight)
				dy = std::min(lastP.y - bounds.top - fBorderHeight, (float)0);
			if (lastP.y + dy > bounds.bottom)
				dy = std::max(bounds.bottom - lastP.y, (float)0);
			
			if (multi && y + dy < minY)
				dy = minY - y;

			if (multi)
			{
				float h, t;
				
				h = y + dy - minY;
				if (h > 0)
					h = Round(h/(rowNr-fSelection.top+1));
				
				t = fCellHeights[fSelection.bottom];				
				fCellHeights.SetValue(fSelection.top, fSelection.bottom, h);
				dy = fCellHeights[fSelection.bottom] - t;
			}
			else if (y + dy < minY)
			{
				int t = k;
				
				fCellHeights.SetValue(rowNr, 0);

				while (k > 1 && backup[k - 1] + fBorderHeight >= y + dy)
					k--;

				ASSERT(k<rowNr);

				if (k <= mRow)
					while (mRow > k)
						fCellHeights.SetValue(mRow--, 0);
				else
				{
					t = mRow;
					for (; mRow < k; mRow++)
						fCellHeights.SetValue(mRow, backup[mRow] - backup[mRow - 1]);
				}

				float kh = y + dy - fBorderHeight;
				kh -= backup[k - 1];
				fCellHeights.SetValue(k, std::max(kh, (float)0));

				mRow = k;
				k = t;
			}
			else
			{
				k = mRow;
				for (; mRow < rowNr; mRow++)
					fCellHeights.SetValue(mRow, backup[mRow] - backup[mRow - 1]);

				fCellHeights.SetValue(rowNr, y + dy - minY);
			}
					
			if (dy != 0)
			{
				y += dy;
				lastP.y += dy;

				if (dy < 0)
					b.top += dy;
				
				StPenState save(this);
				StClipCells clip(this);
				ScrollRect(b, 0, dy);
				Window()->UpdateIfNeeded();
				
				if (dy > 0)
					b.top += dy;

				if (multi)
				{
					int v = fSelection.top;
					do
					{
						TouchLine(v);
						DrawBorderCell(v++, false);
					}
					while (v <= fSelection.bottom && bounds.top + fCellHeights[v] + fBorderHeight < bounds.bottom);
				}
				else
				{
					TouchLine(mRow);
					DrawBorderCell(mRow, false);
				}
				
				for (; k < rowNr; k++)
				{
					TouchLine(k);
					DrawBorderCell(k, false);
				}
			}
			
			if (dy < 0)
			{
				float Y;
				int v;
				
				Y = bounds.bottom + dy - fBorderHeight;
				v = fSelection.bottom;
				do v++;
				while (fCellHeights[v] < Y)
					;

				StPenState save(this);
				
				while (v <= kRowCount && bounds.top + fCellHeights[v] + fBorderHeight < bounds.bottom)
				{
					TouchLine(v);
					DrawBorderCell(v++, false);
				}
			}
			
			if (dy)
			{
				DrawAllLines();
				if (fFirstGraphic)
					fFirstGraphic->HandleUpdate(bounds);
			}
		}
		GetMouse(&newP, &buttons);
	}
	while (buttons);
	
	if (!(backup == fCellHeights))
	{
		CRunArray temp(fCellHeights);
		fCellHeights = backup;
		
		((CCellWindow*)Window())->RegisterCommand(new CResizeCommand(this, temp, true));
		((CCellWindow*)Window())->SetDirty(true);
	}
} /* ResizeRow */