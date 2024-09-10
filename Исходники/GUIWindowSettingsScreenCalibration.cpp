void CGUIWindowSettingsScreenCalibration::NextControl()
{ // set the old control invisible and not focused, and choose the next control
  CGUIControl *pControl = GetControl(m_iControl);
  if (pControl)
  {
    pControl->SetVisible(false);
    pControl->SetFocus(false);
  }
  // switch to the next control
  m_iControl++;
  if (m_iControl > CONTROL_PIXEL_RATIO)
    m_iControl = CONTROL_TOP_LEFT;
  // enable the new control
  EnableControl(m_iControl);
}