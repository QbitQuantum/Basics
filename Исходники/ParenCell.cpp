void ParenCell::Draw(CellParser& parser, wxPoint point, int fontsize)
{
  if (DrawThisCell(parser, point))
  {
    double scale = parser.GetScale();
    wxDC& dc = parser.GetDC();
    wxPoint in(point);

    if (parser.CheckTeXFonts())
    {
      in.x = point.x + m_signWidth;
      SetForeground(parser);
      int fontsize1 = (int) ((m_parenFontSize * scale + 0.5));
      dc.SetFont(wxFont(fontsize1, wxFONTFAMILY_MODERN,
			wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false,
                        m_bigParenType < 1 ?
			parser.GetTeXCMRI() :
			parser.GetTeXCMEX()));
      if (m_bigParenType < 2)
      {
        dc.DrawText(m_bigParenType == 0 ? wxT("(") :
                                          wxT(PAREN_OPEN),
                    point.x,
                    point.y - m_center + SCALE_PX(MC_TEXT_PADDING, scale) -
                    (m_bigParenType > 0 ? m_signTop : 0));
        dc.DrawText(m_bigParenType == 0 ? wxT(")") :
                                          wxT(PAREN_CLOSE),
                    point.x + m_signWidth + m_innerCell->GetFullWidth(scale),
                    point.y - m_center + SCALE_PX(MC_TEXT_PADDING, scale) -
                    (m_bigParenType > 0 ? m_signTop : 0));
      }
      else {
        int top = point.y - m_center - m_signTop;
        int bottom = point.y + m_height - m_center - m_signTop - m_signSize / 2;
        dc.DrawText(wxT(PAREN_OPEN_TOP),
                    point.x,
                    top);
        dc.DrawText(wxT(PAREN_CLOSE_TOP),
                    point.x + m_signWidth + m_innerCell->GetFullWidth(scale),
                    top);
        dc.DrawText(wxT(PAREN_OPEN_BOTTOM),
                    point.x,
                    bottom);
        dc.DrawText(wxT(PAREN_CLOSE_BOTTOM),
                    point.x + m_signWidth + m_innerCell->GetFullWidth(scale),
                    bottom);
        top = top + m_signSize / 2;

        wxASSERT_MSG(m_signSize>=10,_("Font issue: The Parenthesis sign is too small!"));
        if(m_signSize <= 10)
          m_signSize = 10;

        if (top <= bottom)
        {
          while (top < bottom)
          {
            dc.DrawText(wxT(PAREN_OPEN_EXTEND),
                          point.x,
                          top-1);
            dc.DrawText(wxT(PAREN_CLOSE_EXTEND),
                          point.x + m_width - m_signWidth,
                          top-1);
            top += m_signSize / 10;
          }
        }
      }
    }
    else
    {
#if defined __WXMSW__
      in.x += m_charWidth;
      int fontsize1 = (int) ((PAREN_FONT_SIZE * scale + 0.5));
      SetForeground(parser);
      if (m_height < (3*m_charHeight)/2)
      {
        fontsize1 = (int) ((fontsize * scale + 0.5));
        dc.SetFont(wxFont(fontsize1, wxFONTFAMILY_MODERN,
                          wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL,
                          false,
                          parser.GetFontName()));
        dc.DrawText(wxT("("),
                    point.x + m_charWidth - m_charWidth1,
                    point.y - m_charHeight1 / 2);
        dc.DrawText(wxT(")"),
                    point.x + m_width - m_charWidth,
                    point.y - m_charHeight1 / 2);
      }
      else
      {
        dc.SetFont(wxFont(fontsize1, wxFONTFAMILY_MODERN,
                          wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL,
                          false,
                          parser.GetSymbolFontName(),
			  wxFONTENCODING_CP1250));
        dc.DrawText(PAREN_LEFT_TOP,
                    point.x,
                    point.y - m_center);
        dc.DrawText(PAREN_LEFT_BOTTOM,
                    point.x,
                    point.y + m_height - m_center - m_charHeight);
        dc.DrawText(PAREN_RIGHT_TOP,
                    point.x + m_width - m_charWidth,
                    point.y - m_center);
        dc.DrawText(PAREN_RIGHT_BOTTOM,
                    point.x + m_width - m_charWidth,
                    point.y + m_height - m_center - m_charHeight);
        int top, bottom;
        top = point.y - m_center + m_charHeight/2;
        bottom = point.y + m_height - m_center - (4*m_charHeight)/3;

        wxASSERT_MSG(m_charHeight>=2,_("Font issue: The char height is too small! Installing http://www.math.union.edu/~dpvc/jsmath/download/jsMath-fonts.html and checking \"Use JSmath fonts\" in the configuration dialogue should be a workaround."));
        if(m_charHeight <= 2)
          m_charHeight = 2;

        if (top <= bottom)
        {
          while (top < bottom)
          {
            dc.DrawText(PAREN_LEFT_EXTEND,
			point.x,
			top);
            dc.DrawText(PAREN_RIGHT_EXTEND,
			point.x + m_width - m_charWidth,
			top);
            top += (2*m_charHeight)/3;
          }
          dc.DrawText(PAREN_LEFT_EXTEND,
		      point.x,
		      point.y + m_height - m_center - (3*m_charHeight)/2);
          dc.DrawText(PAREN_RIGHT_EXTEND,
		      point.x + m_width - m_charWidth,
		      point.y + m_height - m_center - (3*m_charHeight)/2);
        }
      }
#else
      in.x = point.x + SCALE_PX(6, scale);
      SetPen(parser);
      // left
      dc.DrawLine(point.x + SCALE_PX(5, scale),
                  point.y - m_innerCell->GetMaxCenter() + SCALE_PX(1, scale),
                  point.x + SCALE_PX(2, scale),
                  point.y - m_innerCell->GetMaxCenter() + SCALE_PX(7, scale));
      dc.DrawLine(point.x + SCALE_PX(2, scale),
                  point.y - m_innerCell->GetMaxCenter() + SCALE_PX(7, scale),
                  point.x + SCALE_PX(2, scale),
                  point.y + m_innerCell->GetMaxDrop() - SCALE_PX(7, scale));
      dc.DrawLine(point.x + SCALE_PX(2, scale),
                  point.y + m_innerCell->GetMaxDrop() - SCALE_PX(7, scale),
                  point.x + SCALE_PX(5, scale),
                  point.y + m_innerCell->GetMaxDrop() - SCALE_PX(1, scale));
      // right
      dc.DrawLine(point.x + m_width - SCALE_PX(5, scale) - 1,
                  point.y - m_innerCell->GetMaxCenter() + SCALE_PX(1, scale),
                  point.x + m_width - SCALE_PX(2, scale) - 1,
                  point.y - m_innerCell->GetMaxCenter() + SCALE_PX(7, scale));
      dc.DrawLine(point.x + m_width - SCALE_PX(2, scale) - 1,
                  point.y - m_innerCell->GetMaxCenter() + SCALE_PX(7, scale),
                  point.x + m_width - SCALE_PX(2, scale) - 1,
                  point.y + m_innerCell->GetMaxDrop() - SCALE_PX(7, scale));
      dc.DrawLine(point.x + m_width - SCALE_PX(2, scale) - 1,
                  point.y + m_innerCell->GetMaxDrop() - SCALE_PX(7, scale),
                  point.x + m_width - SCALE_PX(5, scale) - 1,
                  point.y + m_innerCell->GetMaxDrop() - SCALE_PX(1, scale));
      UnsetPen(parser);
#endif
    }
    m_innerCell->DrawList(parser, in, fontsize);
  }
  MathCell::Draw(parser, point, fontsize);
}