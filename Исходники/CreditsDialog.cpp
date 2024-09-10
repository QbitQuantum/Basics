///////////////////////////////////////////////////////////////////////////////
// Paint: Draw the credits.
///////////////////////////////////////////////////////////////////////////////
void ScrollingTextComponent::Paint(Graphics &g)
{
	Component::Paint(g);

	// Draw the background.
	g.SetFont(GetDefaultFont());
	g.SetColor(0xFFFFFF);
	g.FillRect(2,2,Width()-4,Height()-4);

	// Draw the frame.
	g.ApplyColorSchemeColor(StandardColor_3DHilight);
	g.DrawRect(0,0,Width(),Height());
	g.DrawRect(1,1,Width()-1,Height()-1);
	g.ApplyColorSchemeColor(StandardColor_3DShadow);
	g.DrawRect(0, 0,Width()-1,Height()-1);

	// Draw the text.
	int nTop = mScrollTop;
	CreditsList::iterator Itr = mLines.begin();

	while (Itr != mLines.end())
	{
		CreditLineInfo& LineInfo = *Itr;
		int nStrHt = g.GetFont()->GetHeight();

		if (nTop < Height() / 3)
			g.SetColor(DimColor(LineInfo.GetColor(), nTop * 100 / (Height() / 3)));
		else if (Height() - nTop <= nStrHt)
			g.SetColor(0xFFFFFF);
		else if (nTop > (Height() * 2 / 3) - nStrHt)
			g.SetColor(DimColor(LineInfo.GetColor(), ((Height() - (nTop + nStrHt)) * 100 / (Height() / 3))));
		else
			g.SetColor(LineInfo.GetColor());

		if (g.GetColor() != 0xFFFFFF && nTop > 2 && nTop < Height() - nStrHt - 2)
		{
			int nStrWd = g.GetFont()->GetStringWidth(LineInfo.GetLine());
			g.DrawString(LineInfo.GetLine(), (Width() - nStrWd) / 2, nTop);
		}
		nTop += nStrHt;
		++Itr;
	}
	mTotalTextHeight = nTop - mScrollTop;
}