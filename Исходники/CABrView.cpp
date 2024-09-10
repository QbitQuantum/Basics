// Paint //////////////////////////////////////////////////////////////////1.00
//		WM_PAINTに応答。
//		無効化されたクライアント領域を取得し、
//		再描画している。
int ClassABrowserView::Paint()
{
	PAINTSTRUCT		ps;
	HDC				hDC = BeginPaint(hWnd, &ps);
										// DC取得
	// 表示位置の補正
	if (nLineView < 0) nLineView = 0;
	else if (nLineView > nLineViewMax) nLineView = nLineViewMax;

	// スクロールバーの情報設定
	si.fMask	= SIF_DISABLENOSCROLL | SIF_POS;
	si.nPos		= (int)(nLineView / dblScroll);
	SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
	// 画面の端ではスクロールバーを使用不可にする
	EnableScrollBar(hWnd, SB_VERT, ESB_ENABLE_BOTH);
	if (nLineView == 0)
		EnableScrollBar(hWnd, SB_VERT, ESB_DISABLE_UP);
	if (nLineView == nLineViewMax)
		EnableScrollBar(hWnd, SB_VERT, ESB_DISABLE_DOWN);

	PaintSub(hDC, ps.rcPaint.top / tm.tmHeight,
							ps.rcPaint.bottom / tm.tmHeight + 1, TRUE);

	EndPaint(hWnd, &ps);

	return 0;
}