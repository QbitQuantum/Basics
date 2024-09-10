	void WinGDISimpleRenderObjectUtility::DrawCircle(f32 x, f32 y, f32 radius, D_Color clr, f32 lineWidth)
	{
		HDC hdc = m_poRenderer->GetOffscreenDC();  
		HPEN hpen = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, lineWidth, WinGDIMapping::MappingColor(clr))) ;

		MoveToEx(hdc, x + radius, y, NULL);
		AngleArc(hdc, x, y, radius, 0.f, 360.0f);

		DeleteObject(SelectObject(hdc, hpen));
	}