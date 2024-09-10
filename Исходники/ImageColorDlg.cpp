LRESULT CImageColorDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

#if 0
	if (m_viewGroup)
	{
		if (!wcscmp(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"stroke") ||
			!wcscmp(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"fill"))
		{
			CComPtr<ILCSSStyleDeclaration> style;

			CComBSTR strokeStr;
			CComBSTR fillStr;

			if (m_viewGroup)
			{
				//style = ((CWebXMLDocument*)m_document.p)->m_defaultStyle;
				m_viewGroup->GetCurrentSelectionCSSStyle(&style);// = ((CWebXMLViewGroup*)m_viewGroup.p)->m_currentSelectionStyle;

				style->getPropertyValue(L"stroke", &strokeStr);
				//if (strokeStr.Length() == 0) strokeStr = L"";

				style->getPropertyValue(L"fill", &fillStr);
				//if (fillStr.Length() == 0) fillStr = L"";
			}

			{
				int state = dc.SaveDC();
				dc.ExcludeClipRect(&m_strokerc);
				dc.ExcludeClipRect(&m_fillrc);

				CRect rc2;

				rc2 = m_strokerc;
				rc2.InflateRect(1, 1);
				dc.Draw3dRect(&rc2, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

				rc2 = m_fillrc;
				rc2.InflateRect(1, 1);
				dc.Draw3dRect(&rc2, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

				dc.RestoreDC(state);
			}

			{
				if (gApp->m_strokeOrFill == 0)
				{
					int state = dc.SaveDC();
					dc.ExcludeClipRect(&m_strokerc);
					DrawFillPaint(dc, m_fillrc, fillStr);

					dc.RestoreDC(state);
					DrawStrokePaint(dc, m_strokerc, strokeStr);
				}
				else
				{
					int state = dc.SaveDC();
					dc.ExcludeClipRect(&m_fillrc);
					DrawStrokePaint(dc, m_strokerc, strokeStr);

					dc.RestoreDC(state);
					DrawFillPaint(dc, m_fillrc, fillStr);
				}
			}
		}
		else if (!wcscmp(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"stop-color") ||
					!wcscmp(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"solid-color"))
		{
			CComPtr<ILCSSStyleDeclaration> style;
			m_viewGroup->GetCurrentSelectionCSSStyle(&style);

			CComPtr<ILSVGColor> svgColor;
			style->getPropertyCSSValue(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, (ILCSSValue**)&svgColor);

			if (svgColor)
			{
				CLRGBColor rgbColor;
				svgColor->get_rgbColor(&rgbColor);

				double red = rgbColor.GetRed();
				double green = rgbColor.GetGreen();
				double blue = rgbColor.GetBlue();

				CRect rc = CRect(6, 6, 6+18+9, 6+18+9);

				dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
				rc.InflateRect(-1,-1);

				dc.FillSolidRect(&rc, RGB(red, green, blue));			

				if (!wcscmp(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"stop-color"))
				{
					// TODO: draw knob
				}
			}
		}
	}
#endif

	return 0;
}