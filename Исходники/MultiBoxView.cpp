void MultiBoxView::Draw(BRect urect)
{
	UpdateProperties();

	BRect rect;
	int32 element;
	for (int32 i=0; i<numcols; i++) {
		for (int32 j=0; j<numrows; j++) {
//_sPrintf("i: %d, j: %d\n", i, j);
			element = GetElementAt(j, i);
			GetRectAt(element, &rect);
			if (urect.Intersects(rect))
			{
				DrawContentBox(element);
			}
		}
	}
	// clear bottom area of view
	rect = Bounds();
	rect.top = numrows * rowheight + 1;
	SetHighColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	FillRect(rect);
}