void CGUIControllerWindow::DoProcess(unsigned int currentTime, CDirtyRegionList &dirtyregions)
{
  /*
   * Apply the faded focus texture to the current controller when unfocused
   */

  CGUIControl* control = nullptr; // The controller button
  bool bAlphaFaded = false; // True if the controller button has been focused and faded this frame

  if (m_controllerList && m_controllerList->GetFocusedController() >= 0)
  {
    control = GetFirstFocusableControl(CONTROL_CONTROLLER_BUTTONS_START + m_controllerList->GetFocusedController());
    if (control && !control->HasFocus())
    {
      if (control->GetControlType() == CGUIControl::GUICONTROL_BUTTON)
      {
        control->SetFocus(true);
        static_cast<CGUIButtonControl*>(control)->SetAlpha(0x80);
        bAlphaFaded = true;
      }
    }
  }

  CGUIDialog::DoProcess(currentTime, dirtyregions);

  if (control && bAlphaFaded)
  {
    control->SetFocus(false);
    if (control->GetControlType() == CGUIControl::GUICONTROL_BUTTON)
      static_cast<CGUIButtonControl*>(control)->SetAlpha(0xFF);
  }
}