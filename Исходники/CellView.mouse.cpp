void CCellView::MouseDown(BPoint where)
{
	StPenState save(this);
	
	try
	{
		bool optional = IsOptionalClick(Window()->CurrentMessage());
		
		if (!IsFocus() && !fEntering)
			MakeFocus();

		ResetOffset(-1);
	
		BRect myRect, bounds(Bounds());
		cell myCell = cell(fFrozen.h ? 1 : fPosition.h, fFrozen.v ? 1 : fPosition.v);

		if (fFirstGraphic)
		{
			if (fFirstGraphic->HandleMouseDown(where))
				return;
			else if (fFirstGraphic->HasFocus())
				fFirstGraphic->MakeFocus(false);
		}
	
		if (fCellBounds.Contains(where))
		{
			if ((PointIsInSelection(where) &&
				!fEntering) &&
				(optional ||
				WaitMouseMoved(where, false)))
			{
				StartDrag(where, optional);
			}
			else if (optional)
				GridMenu(where);
			else
				SelectCell(where);
		}
		
		if (!fShowBorders)
			return;
		
		myRect = bounds;
		myRect.top = fBorderHeight;
		myRect.left = 0.0;
		myRect.right = fBorderWidth;
	
		if (myRect.Contains(where))
		{
			if (optional)
				BorderMenu(where);
			else
			{
				do
				{
					myCell.v++;
					GetCellRect(myCell, myRect);
				}
				while (myRect.top + 2.0 <= where.y);
		
				if (where.y >= myRect.top - 2.0 && where.y <= myRect.top + 2.0)
					ResizeRow(where, myCell.v - 1);
				else
					SelectRow(where, myCell.v - 1);
			}
			return;
		}
	
		myRect.Set(fBorderWidth, 0.0, bounds.right, fBorderHeight);
	
		if (myRect.Contains(where))
		{
			if (optional)
				BorderMenu(where);
			else
			{
				do
				{
					myCell.h++;
					GetCellRect(myCell, myRect);
				}
				while (myRect.left + 2.0 <= where.x);
		
				if (where.x >= myRect.left - 2.0 && where.x <= myRect.left + 2.0)
					ResizeCol(where, myCell.h - 1);
				else
					SelectCol(where, myCell.h - 1);
			}
			return;
		}
	
		myRect.Set(0.0, 0.0, fBorderWidth, fBorderHeight);
	
		if (myRect.Contains(where))
		{
			if (!fEntering)
				SetSelection(range(1, 1, kColCount, kRowCount));
			else
				beep();
		}
	}
	
	catch(CErr& e)
	{
		CATCHED;
		e.DoError();
		return;
	}
	
	catch(...)
	{
		CATCHED;
		ASSERT(FALSE);
	}
}