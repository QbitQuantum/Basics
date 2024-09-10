// Print (or preview) a single page
void CHexEditView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT(print_offset_.cx >= 0 && print_offset_.cy >= 0);
	pDC->SetMapMode(print_map_mode_);
	int u_scale = pDC->GetDeviceCaps(LOGPIXELSX); // units scaling (pixels/inch)
	if (theApp.print_units_ == CHexEditApp::PRN_CM)
		u_scale = int(u_scale/2.54);

	CRect rct;                              // Encloses all incl. header/footer - ie nothing is printed outside this box
	CRect margin_rct;                       // Smaller box based on margins - does not include header/footer
	CString ss;                             // String to display at top of page

	// Work out text height of the (printer) font
	pDC->SelectObject(print_font_);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int text_height = tm.tmHeight + tm.tmExternalLeading;

	// Work out size of the page
	int vert_res = pDC->GetDeviceCaps(VERTRES);
	int horz_res = pDC->GetDeviceCaps(HORZRES);
	if (vert_res < horz_res/5)                // May be lines of text not pixels (Eg Text Only driver)
		vert_res *= text_height;              // xxx should be device units not logical

	// Work out where the margins are
	margin_rct.top = LONG(theApp.top_margin_*u_scale);
	margin_rct.left = LONG(theApp.left_margin_*u_scale);
	margin_rct.bottom = vert_res - LONG(theApp.bottom_margin_*u_scale);
	margin_rct.right  = horz_res - LONG(theApp.right_margin_*u_scale);
	pDC->DPtoLP(&margin_rct);

	// Work out where to print the header and footer
	rct.top = LONG(theApp.header_edge_*u_scale);
	rct.left = LONG(theApp.left_margin_*u_scale);
	rct.bottom = vert_res - LONG(theApp.footer_edge_*u_scale);
	rct.right  = horz_res - LONG(theApp.right_margin_*u_scale);

	// Note we can't use ConvertFromDP here as this is for printer not screen
	pDC->DPtoLP(&rct);

	pDC->SetBkMode(TRANSPARENT);
	if (theApp.print_watermark_)
	{
		// Work out angle of diagonal from bottom left to top right
		ASSERT(rct.Height() != 0 && rct.Width() != 0);  // else we get divide by zero error
		double diag = (int)sqrt((double)(rct.Height()*rct.Height()) + rct.Width()*rct.Width());
		double angle = asin(rct.Height()/diag);

		// Create a large font at the angle of the diagonal
		int fangle = int(angle * 1800 / 3.141592 /*M_PI*/);   // convert diag angle to tenth of degrees from X-axis
		CFont fontWatermark;
		fontWatermark.CreateFont(rct.Height()/10, 0, fangle, fangle, FW_BOLD, 0, 0, 0,
								 ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
								 DEFAULT_PITCH | FF_SWISS, _T("Arial"));
		CFont * pSaved = pDC->SelectObject(&fontWatermark);

		// Create the text
		CString str = create_header(theApp.watermark_, pInfo->m_nCurPage);

		// Get length of text then work out how far from the bottom page of the corner should the text start
		double d = (diag - pDC->GetTextExtent(str).cx)/2;  // distance along diag of start of text
		int x = int(d * cos(angle));
		int y = int(d * sin(angle));

		pDC->SetTextColor(RGB(208, 208, 208));          // light grey
		pDC->SetTextAlign(TA_BASELINE);
		pDC->TextOut(x, rct.Height() - y, str);

		pDC->SetTextAlign(TA_TOP);
		(void)pDC->SelectObject(pSaved);
		fontWatermark.DeleteObject();
	}

	pDC->SetTextColor(RGB(0,0,0));          // Display headers/footers in black

	int left, mid=1, right;
	if (theApp.even_reverse_ && pInfo->m_nCurPage%2 == 0)
		left = 2, right = 0;
	else
		left = 0, right = 2;

	if (rct.top - text_height > margin_rct.top)  // Note y values are always -ve down in printer map mode
	{
		// Get normal header unless using diff header for 1st page and its the first page
		CString strHeader;
		if (theApp.diff_first_header_ && pInfo->m_nCurPage == 1)
			strHeader = theApp.first_header_;
		else
			strHeader = theApp.header_;

		// Print the 3 parts of the header
		AfxExtractSubString(ss, strHeader, left, '|');
		pDC->DrawText(create_header(ss, pInfo->m_nCurPage), &rct, DT_LEFT | DT_TOP | DT_NOPREFIX | DT_SINGLELINE);

		AfxExtractSubString(ss, strHeader, mid, '|');
		pDC->DrawText(create_header(ss, pInfo->m_nCurPage), &rct, DT_CENTER | DT_TOP | DT_NOPREFIX | DT_SINGLELINE);

		AfxExtractSubString(ss, strHeader, right, '|');
		pDC->DrawText(create_header(ss, pInfo->m_nCurPage), &rct, DT_RIGHT | DT_TOP | DT_NOPREFIX | DT_SINGLELINE);
	}

	if (rct.bottom + text_height < margin_rct.bottom)  // Note y values are -ve down
	{
		// Get normal footer unless using diff footer for 1st page and it's the first page
		CString strFooter;
		if (theApp.diff_first_footer_ && pInfo->m_nCurPage == 1)
			strFooter = theApp.first_footer_;
		else
			strFooter = theApp.footer_;

		// Print the 3 parts of the footer
		AfxExtractSubString(ss, strFooter, left, '|');
		pDC->DrawText(create_header(ss, pInfo->m_nCurPage), &rct, DT_LEFT | DT_BOTTOM | DT_NOPREFIX | DT_SINGLELINE);

		AfxExtractSubString(ss, strFooter, mid, '|');
		pDC->DrawText(create_header(ss, pInfo->m_nCurPage), &rct, DT_CENTER | DT_BOTTOM | DT_NOPREFIX | DT_SINGLELINE);

		AfxExtractSubString(ss, strFooter, right, '|');
		pDC->DrawText(create_header(ss, pInfo->m_nCurPage), &rct, DT_RIGHT | DT_BOTTOM | DT_NOPREFIX | DT_SINGLELINE);
	}

	if (theApp.print_hdr_)
	{
		// Print column headings
		rct = margin_rct + CSize(print_offset_.cx, 0);
		pDC->DrawText("Address", &rct, DT_LEFT | DT_TOP | DT_NOPREFIX | DT_SINGLELINE);
		for (int ii = 0; ii < rowsize_; ++ii)
		{
			char buf[10];
			if (!display_.hex_addr)            // Probably showing dec addresses and/or line numbers so show dec hdr
				sprintf(buf, "%2d", ii%100);
			else if (theApp.hex_ucase_)
				sprintf(buf, "%02X", ii%0x100);
			else
				sprintf(buf, "%02x", ii%0x100);
			if (!display_.vert_display && display_.hex_area)
				pDC->TextOut(rct.left + hex_pos(ii, print_text_width_), rct.top, buf, 2);
			if (display_.vert_display || display_.char_area)
				pDC->TextOut(rct.left + char_pos(ii, print_text_width_, print_text_width_w_), rct.top, buf+1, 1);
		}
	}

	// Draw margins in print preview
	if (pInfo != NULL && pInfo->m_bPreview && pDC->m_hAttribDC != NULL)
	{
		CPen pen(PS_DOT, 0, RGB(0,0,0));
		CPen* ppen = pDC->SelectObject(&pen);
		pDC->MoveTo(-30000, margin_rct.top);
		pDC->LineTo(30000, margin_rct.top);
		pDC->MoveTo(margin_rct.left, -30000);
		pDC->LineTo(margin_rct.left, 30000);
		pDC->MoveTo(-30000, margin_rct.bottom);
		pDC->LineTo(30000, margin_rct.bottom);
		pDC->MoveTo(margin_rct.right, -30000);
		pDC->LineTo(margin_rct.right, 30000);
		pDC->SelectObject(ppen);
	}

	if (theApp.print_box_)
	{
		// Work out width of total printed text
		CSize size;

		rct = margin_rct + CSize(print_offset_.cx, 0);

		if (display_.char_area)
			size.cx = char_pos(rowsize_, print_text_width_, print_text_width_w_);
		else
			size.cx = hex_pos(rowsize_, print_text_width_);
		size.cy = 0;

		// Draw a box around it
		CPen pen(PS_SOLID, 0, RGB(0,0,0));
		CPen* ppen = pDC->SelectObject(&pen);
		pDC->MoveTo(rct.left - print_text_width_, rct.top);
		pDC->LineTo(rct.left + size.cx + print_text_width_, rct.top);
		pDC->LineTo(rct.left + size.cx + print_text_width_, rct.bottom);
		pDC->LineTo(rct.left - print_text_width_, rct.bottom);
		pDC->LineTo(rct.left - print_text_width_, rct.top);

#if 0
		// Draw line between address and hex areas
		size.cx = hex_pos(0, print_text_width_);
		size.cy = 0;
		pDC->MoveTo(rct.left + size.cx - print_text_width_, rct.top);
		pDC->LineTo(rct.left + size.cx - print_text_width_, rct.bottom);

		// Draw line between areas
		if (display_.hex_area && display_.char_area)
		{
			size.cx = hex_pos(rowsize_, print_text_width_);
			size.cy = 0;
			pDC->MoveTo(rct.left + size.cx - print_text_width_/2, rct.top);
			pDC->LineTo(rct.left + size.cx - print_text_width_/2, rct.bottom);
		}
#endif
		pDC->SelectObject(ppen);
	}

	// Do this last so pen changes etc do not affect header, footer etc drawing
	CScrView::OnPrint(pDC, pInfo);          // Calls OnDraw to print rest of page
}