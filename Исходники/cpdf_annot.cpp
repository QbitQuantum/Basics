CFX_FloatRect CPDF_Annot::GetRect() const {
  if (!m_pAnnotDict)
    return CFX_FloatRect();

  CFX_FloatRect rect = m_pAnnotDict->GetRectBy("Rect");
  rect.Normalize();
  return rect;
}