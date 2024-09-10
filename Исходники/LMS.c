BOOL DrawSpectrum(HDC hdc, RECT rect)
{
    static HBITMAP bitmap;
    static HDC hbdc;

    // Draw nice etched edge

    DrawEdge(hdc, &rect , EDGE_SUNKEN, BF_ADJUST | BF_RECT);

    // Calculate bitmap dimensions

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // Create DC

    if (hbdc == NULL)
    {
	hbdc = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(hbdc, bitmap);
	SelectObject(hbdc, GetStockObject(DC_PEN));
    }

    // Erase background

    RECT brct =
	{0, 0, width, height};
    FillRect(hbdc, &brct, GetStockObject(BLACK_BRUSH));

    // Dark green graticule

    SetDCPenColor(hbdc, RGB(0, 128, 0));

    // Draw graticule

    for (int i = 4; i < width; i += 5)
    {
	MoveToEx(hbdc, i, 0, NULL);
	LineTo(hbdc, i, height);
    }

    for (int i = 4; i < height; i += 5)
    {
	MoveToEx(hbdc, 0, i, NULL);
	LineTo(hbdc, width, i);
    }

    // Don't attempt the trace until there's a buffer

    if (spectrum.data == NULL)
    {
	// Copy the bitmap

	BitBlt(hdc, rect.left, rect.top, width, height,
	       hbdc, 0, 0, SRCCOPY);

	return TRUE;
    }

    // Move the origin

    SetViewportOrgEx(hbdc, 0, height - 1, NULL);

    // Green pen for spectrum trace

    SetDCPenColor(hbdc, RGB(0, 255, 0));

    static float max;

    if (max < 1.0)
	max = 1.0;

    // Calculate the scaling

    float yscale = (float)height / max;

    max = 0.0;

    // Draw the spectrum

    MoveToEx(hbdc, 0, 0, NULL);

    float xscale = (float)log(spectrum.length) / width;

    // Create trace

    int last = 1;
    for (int x = 0; x < width; x++)
    {
	float value = 0.0;

	int index = (int)round(pow(M_E, x * xscale));
	for (int i = last; i <= index; i++)
	{
	    // Don't show DC component

	    if (i > 0 && i < spectrum.length)
	    {
		if (value < spectrum.data[i])
		    value = spectrum.data[i];
	    }
	}

	// Update last index

	last = index + 1;

	if (max < value)
	    max = value;

	int y = -round(value * yscale);

	LineTo(hbdc, x, y);
    }

    // Move the origin back

    SetViewportOrgEx(hbdc, 0, 0, NULL);

    // Copy the bitmap

    BitBlt(hdc, rect.left, rect.top, width, height,
	   hbdc, 0, 0, SRCCOPY);

    return TRUE;
}