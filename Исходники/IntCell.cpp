void IntCell::RecalculateWidths(CellParser& parser, int fontsize, bool all)
{
  double scale = parser.GetScale();

  m_signSize = SCALE_PX(50, scale);
  m_signWidth = SCALE_PX(18, scale);

  m_base->RecalculateWidths(parser, fontsize, true);
  m_var->RecalculateWidths(parser, fontsize, true);
  if (m_under == NULL)
    m_under = new TextCell;
  m_under->RecalculateWidths(parser, MAX(MC_MIN_SIZE, fontsize - 5), true);
  if (m_over == NULL)
    m_over = new TextCell;
  m_over->RecalculateWidths(parser, MAX(MC_MIN_SIZE, fontsize - 5), true);

  if (parser.CheckTeXFonts()) {
    wxDC& dc = parser.GetDC();
    int fontsize1 = (int) ((fontsize * scale * 1.5 + 0.5));
    dc.SetFont(wxFont(fontsize1, wxFONTFAMILY_MODERN,
                      false, false, false,
                      parser.GetTeXCMEX()));
    dc.GetTextExtent(wxT("\x5A"), &m_signWidth, &m_signSize);

#if defined __WXMSW__
    m_signWidth = m_signWidth / 2;
#endif
    m_signTop = m_signSize / 2;
    m_signSize = (85 * m_signSize) / 100;

    m_width = m_signWidth +
              MAX(m_over->GetFullWidth(scale) + m_signWidth, m_under->GetFullWidth(scale)) +
              m_base->GetFullWidth(scale) +
              m_var->GetFullWidth(scale) +
              SCALE_PX(4, scale);
  }
  else {
#if defined __WXMSW__
    wxDC& dc = parser.GetDC();
    int fontsize1 = (int) ((INTEGRAL_FONT_SIZE * scale + 0.5));
    dc.SetFont(wxFont(fontsize1, wxFONTFAMILY_MODERN,
                      false, false, false,
                      parser.GetSymbolFontName()));
    dc.GetTextExtent(wxT(INTEGRAL_TOP), &m_charWidth, &m_charHeight);

    m_width = m_signWidth +
              m_base->GetFullWidth(scale) +
              MAX(m_over->GetFullWidth(scale), m_under->GetFullWidth(scale)) +
              m_var->GetFullWidth(scale) +
              SCALE_PX(4, scale);
#else
    m_width = m_signWidth +
              m_base->GetFullWidth(scale) +
              MAX(m_over->GetFullWidth(scale), m_under->GetFullWidth(scale)) +
              m_var->GetFullWidth(scale) +
              SCALE_PX(4, scale);
#endif
  }


  MathCell::RecalculateWidths(parser, fontsize, all);
}