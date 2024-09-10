void SqrtCell::Draw(wxPoint point, int fontsize)
{
  MathCell::Draw(point, fontsize);
  CellParser *parser = CellParser::Get();

  if (DrawThisCell(point) && InUpdateRegion())
  {
    wxDC& dc = parser->GetDC();
    double scale = parser->GetScale();

    wxPoint in(point);

    if (parser->CheckTeXFonts())
    {
      SetPen();

      in.x += m_signWidth;
      double scale = parser->GetScale();

      int fontsize1 = (int)(SIGN_FONT_SCALE*scale*fontsize*m_signFontScale + 0.5);

      dc.SetFont(wxFont(fontsize1, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, parser->GetTeXCMEX()));
      SetForeground();
      if (m_signType < 4) {
        dc.DrawText(
            m_signType == 1 ? wxT("p") :
              m_signType == 2 ? wxT("q") :
                m_signType == 3 ? wxT("r") : wxT("s"),
          point.x,
          point.y - m_innerCell->GetMaxCenter() - m_signTop);
      }
      else {
        int yBottom = point.y + m_innerCell->GetMaxDrop() - 3.2*m_signTop;
        int yTop = point.y - m_innerCell->GetMaxCenter() - m_signTop;
        int dy = m_signSize / 10;
        wxASSERT_MSG((yTop != 0) || (yBottom != 0),_("Font issue? The contents of a sqrt() has the size 0."));
        wxASSERT_MSG(dy>0,_("Font issue: The sqrt() sign has the size 0! Installing http://www.math.union.edu/~dpvc/jsmath/download/jsMath-fonts.html and checking \"Use JSmath fonts\" in the configuration dialogue should be a workaround."));
        if(dy <= 0)
          dy = 1;
        dc.DrawText(wxT("t"),
            point.x,
            yBottom);
        dc.DrawText(wxT("v"),
            point.x,
            yTop);
        while (yTop < yBottom) {
          yTop += dy;
          dc.DrawText(wxT("u"),
                      point.x,
                      yTop);
        }
      }

      dc.DrawLine(point.x + m_signWidth,
                  point.y - m_innerCell->GetMaxCenter(),
                  point.x + m_signWidth + m_innerCell->GetFullWidth(scale),
                  point.y - m_innerCell->GetMaxCenter());

      UnsetPen();
    }
    else
    {
      in.x += SCALE_PX(10, scale) + SCALE_PX(1, scale) + 1;

      SetPen();
      dc.DrawLine(point.x,
                  point.y,
                  point.x + SCALE_PX(3, scale),
                  point.y - SCALE_PX(1, scale));
      dc.DrawLine(point.x + SCALE_PX(3, scale),
                  point.y - SCALE_PX(1, scale),
                  point.x + SCALE_PX(7, scale),
                  point.y + m_height - m_center - SCALE_PX(4, scale));
      dc.DrawLine(point.x + SCALE_PX(3, scale) + 1,
                  point.y - SCALE_PX(1, scale),
                  point.x + SCALE_PX(7, scale) + 1,
                  point.y + m_height - m_center - SCALE_PX(4, scale));
      dc.DrawLine(point.x + SCALE_PX(7, scale) + 1,
                  point.y + m_height - m_center - SCALE_PX(4, scale),
                  point.x + SCALE_PX(10, scale),
                  point.y - m_center + SCALE_PX(2, scale));
      dc.DrawLine(point.x + SCALE_PX(10, scale),
                  point.y - m_center + SCALE_PX(2, scale),
                  point.x + m_width - SCALE_PX(1, scale),
                  point.y - m_center + SCALE_PX(2, scale));
      dc.DrawLine(point.x + m_width - SCALE_PX(1, scale),
                  point.y - m_center + SCALE_PX(2, scale),
                  point.x + m_width - SCALE_PX(1, scale),
                  point.y - m_center + SCALE_PX(6, scale));
      UnsetPen();
    }

    m_innerCell->DrawList(in, fontsize);
  }
}