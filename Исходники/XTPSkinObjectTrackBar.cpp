// dir = direction multiplier (drawing up or down)
// yTic = where (vertically) to draw the line of tics
void CXTPSkinObjectTrackBar::DrawTicsOneLine(CDC* pDC, int dir, int yTic)
{
	const RECT& rc = m_drawRect.rc;

	BOOL bVert = GetStyle() & TBS_VERT;
	CXTPSkinManagerClass* pClass = GetSkinClass();

	COLORREF clrTick = pClass->GetThemeColor(bVert ? TKP_TICSVERT : TKP_TICS, 1,  TMT_COLOR, GetColor(COLOR_BTNTEXT));

	DrawTic(pDC, rc.left, yTic, dir, clrTick);
	DrawTic(pDC, rc.left, yTic + (dir * 1), dir, clrTick);
	DrawTic(pDC, rc.right-1, yTic, dir, clrTick);
	DrawTic(pDC, rc.right-1, yTic+ (dir * 1), dir, clrTick);

	PDWORD pTics = (PDWORD)SendMessage(TBM_GETPTICS);
	int    iPos;
	int    i;

	int nTics = pTics ? (int)LocalSize((HANDLE)pTics) / sizeof(DWORD) : 0;


	// those inbetween
	if (m_nTickFreq && pTics)
	{
		for (i = 0; i < nTics; ++i)
		{
			if (((i + 1) % m_nTickFreq) == 0)
			{
				iPos = LogToPhys(pTics[i]);
				DrawTic(pDC, iPos, yTic, dir, clrTick);
			}
		}
	}

	int lSelStart = (int)SendMessage(TBM_GETSELSTART);
	int lSelEnd = (int)SendMessage(TBM_GETSELEND);
	int lLogMin = (int)SendMessage(TBM_GETRANGEMIN);

	// draw the selection range (triangles)

	if ((GetStyle() & TBS_ENABLESELRANGE) &&
		(lSelStart < lSelEnd) && (lSelEnd >= lLogMin))
	{

		pDC->SetBkColor(clrTick);

		iPos = LogToPhys(lSelStart);

		for (i = 0; i < TICKHEIGHT; i++)
			PatRect(pDC,iPos-i,yTic+(dir==1 ? i : -TICKHEIGHT),
					1,TICKHEIGHT-i, GetStyle() & TBS_VERT, GetColor(COLOR_BTNTEXT));

		iPos = LogToPhys(lSelEnd);

		for (i = 0; i < TICKHEIGHT; i++)
			PatRect(pDC,iPos+i,yTic+(dir==1 ? i : -TICKHEIGHT),
					1,TICKHEIGHT-i, GetStyle() & TBS_VERT, GetColor(COLOR_BTNTEXT));
	}
}