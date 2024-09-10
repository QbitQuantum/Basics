VOID CMimicsArcCtrl::DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape)
{
	INT  nPt;
	INT  nPts;
	INT  nMode;
	HPEN  hOldPen;
	HPEN  hBorderPen;
	POINT  ptRadial[2];
	double  fxRadial;
	double  fyRadial;
	HBRUSH  hOldBrush;
	HBRUSH  hInteriorBrush;
	HBITMAP  hInteriorBitmap;
	LOGBRUSH  sInteriorBrush;
	COLORREF  nOldColor[2];

	if ((hBorderPen = CreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_JOIN_MITER | m_nBorderStyle, m_nBorderSize, GetNearestColor(hDC, (!bShape) ? m_nBorderColor : VGA_COLOR_WHITE))))
	{
		if ((hInteriorBitmap = LoadBitmap(GetModuleInstance(), (m_nInteriorHatch == HT_SOLID || m_nInteriorHatch < 0) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHSOLID) : ((m_nInteriorHatch == HT_HORIZONTAL) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHHORIZONTAL) : ((m_nInteriorHatch == HT_VERTICAL) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHVERTICAL) : ((m_nInteriorHatch == HT_BDIAGONAL) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHDIAGONALDOWN) : ((m_nInteriorHatch == HT_FDIAGONAL) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHDIAGONALUP) : ((m_nInteriorHatch == HT_CROSS) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHCROSS) : ((m_nInteriorHatch == HT_DIAGCROSS) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHCROSSDIAGONAL) : ((m_nInteriorHatch == HT_LPOINTS) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHPOINTSLOW) : ((m_nInteriorHatch == HT_MPOINTS) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHPOINTSMEDIUM) : MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHPOINTSHIGH))))))))))))
		{
			sInteriorBrush.lbStyle = (m_nInteriorColor != (COLORREF)-1) ? ((m_nInteriorHatch > 0) ? BS_PATTERN : BS_SOLID) : BS_HOLLOW;
			sInteriorBrush.lbColor = (sInteriorBrush.lbStyle == BS_SOLID) ? GetNearestColor(hDC, (!bShape) ? m_nInteriorColor : VGA_COLOR_WHITE) : 0;
			sInteriorBrush.lbHatch = (sInteriorBrush.lbStyle == BS_PATTERN) ? (ULONG_PTR)hInteriorBitmap : (ULONG_PTR)NULL;
			if ((hInteriorBrush = CreateBrushIndirect(&sInteriorBrush)) != (HBRUSH)NULL)
			{
				if ((hOldPen = (HPEN)SelectObject(hDC, hBorderPen)) != (HPEN)NULL)
				{
					if ((hOldBrush = (HBRUSH)SelectObject(hDC, hInteriorBrush)))
					{
						for (nPt = 0, nPts = sizeof(ptRadial) / sizeof(POINT); nPt < nPts; nPt++)
						{
							fxRadial = (INT)((double)(pRect->left + pRect->right) / 2.0 + ((double)(pRect->right - pRect->left + pRect->bottom - pRect->top) / 2.0)*cos(2.0*M_PI - m_ptRadial[nPt]));
							fyRadial = (INT)((double)(pRect->top + pRect->bottom) / 2.0 + ((double)(pRect->right - pRect->left + pRect->bottom - pRect->top) / 2.0)*sin(2.0*M_PI - m_ptRadial[nPt]));
							ptRadial[nPt].x = (fxRadial >= 0.0) ? (INT)(fxRadial + 0.5) : (INT)(fxRadial - 0.5);
							ptRadial[nPt].y = (fyRadial >= 0.0) ? (INT)(fyRadial + 0.5) : (INT)(fyRadial - 0.5);
						}
						for (nMode = SetBkMode(hDC, OPAQUE), nOldColor[0] = SetBkColor(hDC, GetNearestColor(hDC, (!bShape) ? m_nInteriorColor : VGA_COLOR_WHITE)), nOldColor[1] = SetTextColor(hDC, GetNearestColor(hDC, (!bShape) ? m_nHatchColor : VGA_COLOR_WHITE)); m_nStyle & MIMICSARCCTRL_TYPE_ARC; )
						{
							Arc(hDC, pRect->left + m_nBorderSize / 2, pRect->top + m_nBorderSize / 2, pRect->right - m_nBorderSize / 2 - m_nBorderSize % 2, pRect->bottom - m_nBorderSize / 2 - m_nBorderSize % 2, ptRadial[0].x, ptRadial[0].y, ptRadial[1].x, ptRadial[1].y);
							break;
						}
						for (; m_nStyle & MIMICSARCCTRL_TYPE_PIE; )
						{
							Pie(hDC, pRect->left + m_nBorderSize / 2, pRect->top + m_nBorderSize / 2, pRect->right - m_nBorderSize / 2 - m_nBorderSize % 2, pRect->bottom - m_nBorderSize / 2 - m_nBorderSize % 2, ptRadial[0].x, ptRadial[0].y, ptRadial[1].x, ptRadial[1].y);
							break;
						}
						for (; m_nStyle & MIMICSARCCTRL_TYPE_CHORD; )
						{
							Chord(hDC, pRect->left + m_nBorderSize / 2, pRect->top + m_nBorderSize / 2, pRect->right - m_nBorderSize / 2 - m_nBorderSize % 2, pRect->bottom - m_nBorderSize / 2 - m_nBorderSize % 2, ptRadial[0].x, ptRadial[0].y, ptRadial[1].x, ptRadial[1].y);
							break;
						}
						SetBkMode(hDC, nMode);
						SetBkColor(hDC, nOldColor[0]);
						SetTextColor(hDC, nOldColor[1]);
						SelectObject(hDC, hOldBrush);
					}
					SelectObject(hDC, hOldPen);
				}
				DeleteObject(hInteriorBrush);
			}
			DeleteObject(hInteriorBitmap);
		}
		DeletePen(hBorderPen);
	}
}