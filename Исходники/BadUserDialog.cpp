void BadUserItem::Paint(Graphics &g, ListArea *theListArea)
{
	int aColor = theListArea->GetTextColor();
	if(mSelected)
		aColor = theListArea->GetSelColor().GetForegroundColor(g,aColor);

	int aPaintCol = 0;
	bool drawSelection = mSelected;
	if(!mIsSimple)
	{
		aPaintCol = ((MultiListArea*)theListArea)->GetColumnPaintContext();
		if(aPaintCol!=-1)
			drawSelection = false;
	}
	
	
	if(drawSelection)
	{
		g.SetColor(theListArea->GetSelColor().GetBackgroundColor(g));
		g.FillRect(0,0,theListArea->GetPaintColumnWidth(),mFont->GetHeight());
		if(!mIsSimple)
			return;
	}
	if(aPaintCol<0 || aPaintCol>5)
		return;

	g.SetColor(aColor);
	g.SetFont(mFont);
	g.DrawString(mColStr[aPaintCol],0,0);
}