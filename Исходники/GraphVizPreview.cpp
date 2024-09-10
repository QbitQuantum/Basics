void GraphVizPreview::draw()
{
    if (m_bmp_data.empty())
        return;

    HWND pImage = GetDlgItem(m_hDlg, ID_PICTURE);

    {
        HWND pEdit = GetDlgItem(m_hDlg, IDC_GVP_EDIT);
        if (m_b_err)
        {
            const int offset = 40;
            SetWindowPos(m_hDlg, NULL, 0, 0, 600, 400, SWP_NOMOVE);
            SetWindowPos(pEdit, NULL, 0, 0, 600 - offset, 400 - offset, SWP_NOMOVE);
            m_bmp_data.push_back('\0');
            SetWindowTextA(pEdit, &m_bmp_data[0]);
            ShowWindow(pEdit, SW_SHOWNORMAL);
            EnableWindow(pEdit, TRUE);

            ShowWindow(pImage, SW_HIDE);
            EnableWindow(pImage, FALSE);

            InvalidateRect(m_hDlg, NULL, TRUE);
            return;
        }
        else
        {
            SetWindowTextA(pEdit, "");
            ShowWindow(pEdit, SW_HIDE);
            EnableWindow(pEdit, FALSE);

            ShowWindow(pImage, SW_SHOWNORMAL);
            EnableWindow(pImage, TRUE);
        }
    }

    HBITMAP hBmp;
    {
        char *pBuffer = &*m_bmp_data.begin();
        tagBITMAPFILEHEADER bfh = *(tagBITMAPFILEHEADER*)pBuffer;
        tagBITMAPINFOHEADER bih = *(tagBITMAPINFOHEADER*)(pBuffer + sizeof(tagBITMAPFILEHEADER));
        RGBQUAD             rgb = *(RGBQUAD*)(pBuffer + sizeof(tagBITMAPFILEHEADER) + sizeof(tagBITMAPINFOHEADER));

        BITMAPINFO bi;
        bi.bmiColors[0] = rgb;
        bi.bmiHeader = bih;

        char* pPixels = (pBuffer + bfh.bfOffBits);
        char* ppvBits = nullptr;

        hBmp = CreateDIBSection(NULL, &bi, DIB_RGB_COLORS, (void**)&ppvBits, NULL, 0);
        SetDIBits(NULL, hBmp, 0, bih.biHeight, pPixels, &bi, DIB_RGB_COLORS);
    }

    BITMAP 			bitmap;
    GetObject(hBmp, sizeof(bitmap), &bitmap);
    // Resize
    RECT dlg_dimensions, output_dimensions;
    GetClientRect(m_hDlg, &dlg_dimensions);

    // Maximize the draw area to the available area.
    SetWindowPos(pImage, NULL, 0, 0, dlg_dimensions.right, dlg_dimensions.bottom, SWP_NOMOVE | SWP_NOACTIVATE);

    // We will have to scale the bitmap, this section applies the scaling factor
    output_dimensions = dlg_dimensions;
    output_dimensions.right -= 1;
    output_dimensions.bottom -= 1;

    m_original_output_dimensions.top = 0;
    m_original_output_dimensions.left = 0;
    m_original_output_dimensions.right = bitmap.bmWidth;
    m_original_output_dimensions.bottom = bitmap.bmHeight;
    if (m_zoom <= 0.0)
    {
        double width_ratio = double(output_dimensions.right) / bitmap.bmWidth;
        double height_ratio = double(output_dimensions.bottom) / bitmap.bmHeight;

        if (width_ratio < 1.0 || height_ratio < 1.0)
        {
            if (width_ratio < height_ratio)
            {
                output_dimensions.right = static_cast<LONG>(bitmap.bmWidth * width_ratio);
                output_dimensions.bottom = static_cast<LONG>(bitmap.bmHeight * width_ratio);
                m_zoom = width_ratio;
            }
            else
            {
                output_dimensions.right = static_cast<LONG>(bitmap.bmWidth * height_ratio);
                output_dimensions.bottom = static_cast<LONG>(bitmap.bmHeight * height_ratio);
                m_zoom = height_ratio;
            }
        }
        else
        {
            output_dimensions.right = bitmap.bmWidth;
            output_dimensions.bottom = bitmap.bmHeight;
            m_zoom = 1.0;
        }
    }
    else
    {
        m_output_dimensions.right = static_cast<LONG>(m_output_dimensions.left + m_zoom * bitmap.bmWidth);
        m_output_dimensions.bottom = static_cast<LONG>(m_output_dimensions.top + m_zoom * bitmap.bmHeight);
        output_dimensions = m_output_dimensions;
    }

    m_output_dimensions = output_dimensions;

    // Begin painting    
	PAINTSTRUCT 	ps;
	HDC 			hdc = BeginPaint(pImage, &ps);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HGDIOBJ oldBitmap = SelectObject(hdcMem, hBmp);

    // Draw dark grey everywhere
    HBRUSH bg_color = CreateSolidBrush(RGB(200,200,200));
    FillRect(hdc, &dlg_dimensions, bg_color);
    DeleteObject(bg_color);

    // Copy from bitmap to dialog rectangle, with scaling.
    StretchBlt(hdc, 
        output_dimensions.left, output_dimensions.top,
        static_cast<LONG>(bitmap.bmWidth * m_zoom),
        static_cast<LONG>(bitmap.bmHeight * m_zoom),
        hdcMem,
        0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	SelectObject(hdcMem, oldBitmap);

	DeleteDC(hdcMem);

	EndPaint(pImage, &ps);

	DeleteObject(hBmp);
	
}