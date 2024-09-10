void AtCell::Draw(wxPoint point, int fontsize)
{
  MathCell::Draw(point, fontsize);

  Configuration *configuration = Configuration::Get();
  double scale = configuration->GetScale();
  wxDC& dc = configuration->GetDC();
  if (DrawThisCell(point) && InUpdateRegion())
  {
    wxPoint bs, in;

    bs.x = point.x;
    bs.y = point.y;
    m_baseCell->DrawList(bs, fontsize);

    in.x = point.x + m_baseCell->GetFullWidth(scale) + SCALE_PX(4, scale);
    in.y = point.y + m_baseCell->GetMaxDrop() +
           + m_indexCell->GetMaxCenter() - SCALE_PX(7, scale);
    m_indexCell->DrawList(in, MAX(MC_MIN_SIZE, fontsize - 3));
    SetPen();
    dc.DrawLine(in.x - SCALE_PX(2, scale),
                bs.y - m_baseCell->GetMaxCenter(),
                in.x - SCALE_PX(2, scale),
                in.y);
    UnsetPen();
  }
}