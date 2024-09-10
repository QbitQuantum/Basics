void ConjugateCell::Draw(wxPoint point)
{
  Cell::Draw(point);
  if (DrawThisCell(point) && InUpdateRegion())
  {
    Configuration *configuration = (*m_configuration);
    
    wxDC *dc = configuration->GetDC();
    SetPen();
    wxPoint in;
    in.x = point.x + Scale_Px(4);
    in.y = point.y;
    m_innerCell->DrawList(in);

    dc->DrawLine(point.x + Scale_Px(2),
                 point.y - m_center + Scale_Px(2),
                 point.x + m_width - Scale_Px(2) - 1,
                 point.y - m_center + Scale_Px(2)
      );
    //                point.y - m_center + m_height - Scale_Px(2));
    UnsetPen();
  }
}