void gfxPreviewWind::OnPaint() 
{
	if (!mlEdit.isMaterialListValid())
		return;
	
	if (m_matType == TS::Material::MatPalette || m_matType == TS::Material::MatTexture ||
		m_matType == TS::Material::MatNull) {
		RECT rect;
		if (GetUpdateRect(&rect)) {
			PAINTSTRUCT ps;
			BeginPaint(&ps);
			Refresh();
			EndPaint(&ps);
		} else {
			Refresh();
		}
	} else {
		// The material is an RGB, so we'll call on windows to display it, dithering in 256
		// color mode, or displaying real color in true-color modes...
		//
		CPaintDC dc(this); // device context for painting
		
		UInt8 red   = m_pMaterial->fParams.fRGB.fRed;
		UInt8 green = m_pMaterial->fParams.fRGB.fGreen;
		UInt8 blue  = m_pMaterial->fParams.fRGB.fBlue;
		
		COLORREF m_color = RGB(red, green, blue);

		CBrush brRGB( m_color );
		dc.FillRect( &dc.m_ps.rcPaint, &brRGB );
	}
}