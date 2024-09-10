void FracCell::Draw(wxPoint point)
{
  if (DrawThisCell(point) && InUpdateRegion())
  {
    Cell::Draw(point);
    Configuration *configuration = (*m_configuration);
    
    wxDC *dc = configuration->GetDC();
    wxPoint num, denom;

    if (m_exponent && !m_isBrokenIntoLines)
    {
      num.x = point.x;
      num.y = point.y;
      denom.x = point.x + m_num->GetFullWidth() + m_expDivideWidth;
      denom.y = num.y;

      m_num->DrawList(num);
      m_denom->DrawList(denom);

      int fontsize1 = Scale_Px(m_fontSize);
      wxASSERT(fontsize1 > 0);
      dc->SetFont(wxFont(fontsize1, wxFONTFAMILY_MODERN,
                        wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false,
                        configuration->GetFontName(TS_VARIABLE)));
      dc->DrawText(wxT("/"),
                  point.x + m_num->GetFullWidth(),
                  point.y - m_num->GetMaxCenter() + MC_TEXT_PADDING);
    }
    else
    {
      num.x = point.x + m_horizontalGapLeft +
              (m_width - m_horizontalGapLeft - m_horizontalGapRight - m_num->GetFullWidth()) / 2;
      num.y = point.y - m_num->GetMaxHeight() + m_num->GetMaxCenter() -
              Scale_Px(2);
      m_num->DrawList(num);

      denom.x = point.x + m_horizontalGapLeft +
                (m_width - m_horizontalGapLeft - m_horizontalGapRight - m_denom->GetFullWidth()) / 2;
      denom.y = point.y + m_denom->GetMaxCenter() + Scale_Px(2);
      m_denom->DrawList(denom);
      SetPen(1.2);
      if (m_fracStyle != FC_CHOOSE)
        dc->DrawLine(point.x + m_horizontalGapLeft + (*m_configuration)->GetDefaultLineWidth() / 2,
                    point.y,
                    point.x + m_width - m_horizontalGapRight - (*m_configuration)->GetDefaultLineWidth() / 2,
                    point.y
        );
      UnsetPen();
    }
  }
}