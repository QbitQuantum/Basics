void CGUIButtonControl::ProcessText(unsigned int currentTime)
{
  CRect labelRenderRect = m_label.GetRenderRect();
  CRect label2RenderRect = m_label2.GetRenderRect();

  float renderWidth = GetWidth();
  bool changed = m_label.SetMaxRect(m_posX, m_posY, renderWidth, m_height);
  changed |= m_label.SetText(m_info.GetLabel(m_parentID));
  changed |= m_label.SetScrolling(HasFocus());
  changed |= m_label2.SetMaxRect(m_posX, m_posY, renderWidth, m_height);
  changed |= m_label2.SetText(m_info2.GetLabel(m_parentID));

  // text changed - images need resizing
  if (m_minWidth && (m_label.GetRenderRect() != labelRenderRect))
    SetInvalid();

  // auto-width - adjust hitrect
  if (m_minWidth && m_width != renderWidth)
  {
    CRect rect(m_posX, m_posY, renderWidth, m_height);
    SetHitRect(rect, m_hitColor);
  }

  // render the second label if it exists
  if (!m_info2.GetLabel(m_parentID).empty())
  {
    changed |= m_label2.SetAlign(XBFONT_RIGHT | (m_label.GetLabelInfo().align & XBFONT_CENTER_Y) | XBFONT_TRUNCATED);
    changed |= m_label2.SetScrolling(HasFocus());

    // If overlapping was corrected - compare render rects to determine
    // if they changed since last frame.
    if (CGUILabel::CheckAndCorrectOverlap(m_label, m_label2))
      changed |= (m_label.GetRenderRect()  != labelRenderRect ||
                  m_label2.GetRenderRect() != label2RenderRect);

    changed |= m_label2.SetColor(GetTextColor());
    changed |= m_label2.Process(currentTime);
  }
  changed |= m_label.SetColor(GetTextColor());
  changed |= m_label.Process(currentTime);
  if (changed)
    MarkDirtyRegion();
}