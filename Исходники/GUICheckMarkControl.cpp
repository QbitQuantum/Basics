void CGUICheckMarkControl::Render()
{
  m_label.SetText(m_strLabel);

  float textWidth = m_label.GetTextWidth();
  m_width = textWidth + 5 + m_imgCheckMark.GetWidth();
  m_height = m_imgCheckMark.GetHeight();

  float textPosX = m_posX;
  float checkMarkPosX = m_posX;

  if (m_label.GetLabelInfo().align & (XBFONT_RIGHT | XBFONT_CENTER_X))
    textPosX += m_imgCheckMark.GetWidth() + 5;
  else
    checkMarkPosX += textWidth + 5;

  m_label.SetMaxRect(textPosX, m_posY, textWidth, m_height);
  m_label.SetColor(GetTextColor());
  m_label.Render();

  if (m_bSelected)
  {
    m_imgCheckMark.SetPosition(checkMarkPosX, m_posY);
    m_imgCheckMark.Render();
  }
  else
  {
    m_imgCheckMarkNoFocus.SetPosition(checkMarkPosX, m_posY);
    m_imgCheckMarkNoFocus.Render();
  }
  CGUIControl::Render();
}