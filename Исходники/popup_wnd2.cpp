void PopupWnd2::updateLayered(BYTE opacity)
{
	if (!m_hwnd) return;

	if (SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, GetWindowLongPtr(m_hwnd, GWL_EXSTYLE) | WS_EX_LAYERED)) {
		RECT rc; GetWindowRect(m_hwnd, &rc);
		POINT ptDst = { rc.left, rc.top };
		POINT ptSrc = { 0, 0 };

		BLENDFUNCTION blend;
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = opacity; // m_options->UseTransparency ? opacity : 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		UpdateLayeredWindow(m_hwnd, NULL, &ptDst, &m_sz,
			m_bmpAnimate ? m_bmpAnimate->getDC() : m_bmp->getDC(),
			&ptSrc, 0xffffffff, &blend, ULW_ALPHA);

		UpdateWindow(m_hwnd);
	}
}