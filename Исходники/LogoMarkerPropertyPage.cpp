/////////////////////////////////////////////////////////////////////////////
// IPropertyPage
STDMETHODIMP CLogoMarkerPropertyPage::Show(UINT nCmdShow)
{
	USES_CONVERSION;

	// If we are showing the property page propulate it
	// from the Marker symbol object.
	if ((nCmdShow & (SW_SHOW|SW_SHOWDEFAULT)))
	{
		//colors
		IColorPtr ipColor;
		m_ipLogoMarker->get_ColorTop(&ipColor);
		ipColor->get_RGB(&m_colTop);
		::SendMessage(m_hRchTop, EM_SETBKGNDCOLOR, 0, 
															(LPARAM) m_colTop);

		m_ipLogoMarker->get_ColorRight(&ipColor);
		ipColor->get_RGB(&m_colRight);
		::SendMessage(m_hRchRight, EM_SETBKGNDCOLOR, 0, 
															(LPARAM) m_colRight);
	
		m_ipLogoMarker->get_ColorLeft(&ipColor);
		ipColor->get_RGB(&m_colLeft);
		::SendMessage(m_hRchLeft, EM_SETBKGNDCOLOR, 0, 
															(LPARAM) m_colLeft);
		
		m_ipLogoMarker->get_ColorBorder(&ipColor);
		ipColor->get_RGB(&m_colBorder);
		::SendMessage(m_hRchBorder, EM_SETBKGNDCOLOR, 0, 
															(LPARAM) m_colBorder);
		
		//angle, size and offsets
		char  sText[10];
		double dText;
		IMarkerSymbolPtr ipMSymbol(m_ipLogoMarker);
		ipMSymbol->get_Size(&dText);
		sprintf_s( sText, sizeof(sText), "%.2f\0", dText);
		::SendMessage(m_hSpnSize, UDM_SETPOS, 0, MAKELPARAM((int)(dText), 0));
		::SetWindowText(m_hEdtSize, A2T(sText));
		ipMSymbol->get_Angle(&dText);
		sprintf_s( sText, sizeof(sText), "%d\0", (int)dText);
		::SendMessage(m_hSpnAngle, UDM_SETPOS, 0, MAKELPARAM((int)(dText), 0));
		::SetWindowText(m_hEdtAngle, A2T(sText));
		ipMSymbol->get_XOffset(&dText);
		sprintf_s( sText, sizeof(sText), "%+.2f\0", dText);
		::SendMessage(m_hSpnXOffset, UDM_SETPOS, 0, MAKELPARAM((int)(dText), 0));
		::SetWindowText(m_hEdtXOffset, A2T(sText));
		ipMSymbol->get_YOffset(&dText);
		sprintf_s( sText, sizeof(sText), "%+.2f\0", dText);
		::SendMessage(m_hSpnYOffset, UDM_SETPOS, 0, MAKELPARAM((int)(dText), 0));
		::SetWindowText(m_hEdtYOffset, A2T(sText));

		m_bShown = true;
	}

	// Let the IPropertyPageImpl deal with displaying the page
	return IPropertyPageImpl<CLogoMarkerPropertyPage>::Show(nCmdShow);
}