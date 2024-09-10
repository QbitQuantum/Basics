void CLab08View::OnDraw(CDC* _pDC)
{
	CLab08Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	CRect size;
	_pDC->GetWindow()->GetClientRect(&size);

	// Супер костыли
	CMemDC dc(*_pDC, _pDC->GetWindow());
	CDC * pDC = &dc.GetDC();
	// Крутая штука, почему я раньше её не юзал

	// Чистим фон
	CBrush bgBrush(_pDC->GetBkColor());
	pDC->FillRect(size, &bgBrush);

	if (size.Width() < 150 || size.Height() < 150 ) {
		LONG x = size.left + (size.right - size.left) / 2;
		LONG y = size.top + (size.bottom - size.top) / 2;
		HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		pDC->DrawIcon(x - 16, y - 16, m_hIcon);
		return;
	}

	auto & props = pDoc->properties;
	auto & funcs = pDoc->properties.functions;

	// Начало координат в пикселях. Может не попадать в область видимости
	LONG center_x = t_dim_to_pixel_x(size, 0.0);
	LONG center_y = t_dim_to_pixel_y(size, 0.0);

	pDC->SetBkMode(TRANSPARENT);

	// Рисуем вспомогательную сетку
	CPen penGird(PS_DOT, 1, COLORREF(0x7f7f7f));
	pDC->SelectObject(&penGird);
	pDC->SetTextColor(COLORREF(0x7f7f7f));
	double gird_lx = ceil(t_pixel_to_dim_x(size, size.left) / props.x_grid) * props.x_grid;
	double gird_rx = floor(t_pixel_to_dim_x(size, size.right) / props.x_grid) * props.x_grid;
	for(double i = gird_lx; i <= gird_rx; i += props.x_grid) {
		LONG ix = t_dim_to_pixel_x(size, i);
		if ( ix != center_x && size.left + 1 < ix && ix < size.right - 1) {
			pDC->MoveTo(ix, size.bottom - 5); pDC->LineTo(ix, size.top + 5);
		}
	}
	double gird_ly = ceil(t_pixel_to_dim_y(size, size.bottom) / props.y_grid) * props.y_grid;
	double gird_ry = floor(t_pixel_to_dim_y(size, size.top) / props.y_grid) * props.y_grid;
	for(double i = gird_ly; i <= gird_ry; i += props.y_grid) {
		LONG iy = t_dim_to_pixel_y(size, i);
		if ( iy != center_y && size.top + 1 < iy && iy < size.bottom - 1) {
			pDC->MoveTo(size.left + 5, iy); pDC->LineTo(size.right - 5, iy);
		}
	}

	// Рисуем оси, если это имеет смысл
	CPen penAxis(PS_SOLID, 2, COLORREF(0x000000));
	pDC->SelectObject(&penAxis);
	pDC->SetTextColor(0);
	if ( size.left <= center_x && center_x <= size.right ) {
		pDC->MoveTo(center_x, size.bottom - 5); pDC->LineTo(center_x, size.top + 5);
		// стрелочка
		pDC->MoveTo(center_x - 5, size.top + 10);
		pDC->LineTo(center_x, size.top + 5);
		pDC->LineTo(center_x + 5, size.top + 10);
		// Буковка
		pDC->TextOut(center_x + 5, size.top + 10, _T("Y"));
	}
	if ( size.top <= center_y && center_y <= size.bottom ) {
		pDC->MoveTo(size.left + 5, center_y); pDC->LineTo(size.right - 5, center_y);
		// стрелочка
		pDC->MoveTo(size.right - 10, center_y - 5);
		pDC->LineTo(size.right - 5, center_y);
		pDC->LineTo(size.right - 10, center_y + 5);
		// Буковка
		pDC->TextOut(size.right - 15, center_y + 5, _T("X"));
	}
	if ( size.left <= center_x && center_x <= size.right && 
		size.top <= center_y && center_y <= size.bottom ) {
		pDC->TextOut(center_x + 1, center_y + 1, _T("(0;0)"));
	}

	// координаты в углах
	{
		CString tmp;

		tmp.Format(_T("(%g;%g)"), gird_lx, gird_ly);
		drawPoint(pDC, size, t_dim_to_pixel_x(size, gird_lx),
			t_dim_to_pixel_y(size, gird_ly), tmp);
		tmp.Format(_T("(%g;%g)"), gird_lx, gird_ry);
		drawPoint(pDC, size, t_dim_to_pixel_x(size, gird_lx),
			t_dim_to_pixel_y(size, gird_ry), tmp);
		tmp.Format(_T("(%g;%g)"), gird_rx, gird_ly);
		drawPoint(pDC, size, t_dim_to_pixel_x(size, gird_rx),
			t_dim_to_pixel_y(size, gird_ly), tmp);
		tmp.Format(_T("(%g;%g)"), gird_rx, gird_ry);
		drawPoint(pDC, size, t_dim_to_pixel_x(size, gird_rx),
			t_dim_to_pixel_y(size, gird_ry), tmp);
	}

	// Рисование графиков
	for(int ii = 0; ii < funcs.size(); ++ii) {
		CPen penFunc(PS_SOLID, 1, funcs[ii].second);
		pDC->SelectObject(&penFunc);
		for(int pixel_x = size.left; pixel_x < size.right; pixel_x += props.accuracy) {
			//Sleep(1); // TEST ONLY
			double dim_x = t_pixel_to_dim_x(size, pixel_x);
			double dim_y = funcs[ii].first.f(dim_x);
			int pixel_y = t_dim_to_pixel_y(size, dim_y);
			if (pixel_x == size.left) pDC->MoveTo(pixel_x, pixel_y);
			else pDC->LineTo(pixel_x, pixel_y);
		}
	}
}