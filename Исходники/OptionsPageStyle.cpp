void COptionsPageStyle::OnOK()
{
	if(!m_bCreated)
		return;

	StyleDetails display;
	StyleDetails current;
	m_defclass->Combine(NULL, current);
		
	display.FontName	= m_FontCombo.GetSelFontName();
	display.FontSize	= GetDlgItemInt(IDC_FONTSIZE_COMBO);
	display.ForeColor	= m_fore.SafeGetColor();
	display.BackColor	= m_back.SafeGetColor();
	display.Bold		= (m_bold.GetCheck() == BST_CHECKED);
	display.Italic		= (m_italic.GetCheck() == BST_CHECKED);
	display.Underline	= (m_underline.GetCheck() == BST_CHECKED);
	display.name		= _T("default");

	if(display != current)
	{
		// the new style is not the same as the current style:

		// work out what the differences are
		StyleDetails therealdefault( *m_defclass->Style );
		display.compareTo(therealdefault);

		if(display.values == 0)
		{
			// Not custom any more...
			m_defclass->Reset();
		}
		else
		{
			if(m_defclass->CustomStyle)
				*m_defclass->CustomStyle = display;
			else
				m_defclass->CustomStyle = new StyleDetails(display);
		}
	}
	
	// Clear all existing colour customisations
	EditorColours* ec = m_pSchemes->GetDefaultColours();
	ec->Clear();

	COLORREF c;
	c = m_cur.GetColor();
	
	if( CButton(GetDlgItem(IDC_STYLE_SELUSEFORE)).GetCheck() == BST_CHECKED )
		c = CLR_NONE;
	else
		c = m_selFore.GetColor();

	if(c != CLR_DEFAULT)
		ec->SetColour( EditorColours::ecSelFore, c);
	
	StoreIfSet(m_selBack, ec, EditorColours::ecSelBack);
	StoreIfSet(m_cur, ec, EditorColours::ecCaret);
	StoreIfSet(m_indentGuides, ec, EditorColours::ecIndentG);
	StoreIfSet(m_markAll, ec, EditorColours::ecMarkAll);
	StoreIfSet(m_smartHighlight, ec, EditorColours::ecSmartHL);
	StoreIfSet(m_templateField, ec, EditorColours::ecTemplateField);
}