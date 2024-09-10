void UICircle::Draw(CDC* ip_pdc)
  {

  HDC handle = ip_pdc->GetSafeHdc();
  CPen pen;
  if (m_is_selected)
    pen.CreatePen(PS_DASH, 1, m_circle_color);
  else
    pen.CreatePen(PS_SOLID, 1, m_circle_color);

  CBrush solid_brush;
  if (m_is_brush_defined && m_circle_brush != NULL_BRUSH)
    {
    solid_brush.CreateSolidBrush(m_circle_brush);
    ip_pdc->SelectObject(&solid_brush);
    }
  else
    {
    SelectObject(handle, GetStockObject(NULL_BRUSH));
    }

  ip_pdc->SelectObject(&pen);
  ip_pdc->SetDCPenColor(m_circle_color);

  double radius = mp_circle->GetRadius();

  double x_1 = mp_circle->GetFirstPoint().GetX() - radius;
  double y_1 = mp_circle->GetFirstPoint().GetY() + radius;

  double x_2 = mp_circle->GetFirstPoint().GetX() + radius;
  double y_2 = mp_circle->GetFirstPoint().GetY() - radius;

  ip_pdc->Ellipse((int)x_1, (int)y_1, (int)x_2, (int)y_2);
  }