void CGUIDialogAddonSettings::DoProcess(unsigned int currentTime, CDirtyRegionList &dirtyregions)
{
  // update status of current section button
  bool alphaFaded = false;
  CGUIControl *control = GetFirstFocusableControl(CONTROL_START_SECTION + m_currentSection);
  if (control && !control->HasFocus())
  {
    if (control->GetControlType() == CGUIControl::GUICONTROL_BUTTON)
    {
      control->SetFocus(true);
      ((CGUIButtonControl *)control)->SetAlpha(0x80);
      alphaFaded = true;
    }
    else if (control->GetControlType() == CGUIControl::GUICONTROL_TOGGLEBUTTON)
    {
      control->SetFocus(true);
      ((CGUIButtonControl *)control)->SetSelected(true);
      alphaFaded = true;
    }
  }
  CGUIDialogBoxBase::DoProcess(currentTime, dirtyregions);
  if (alphaFaded && m_active) // dialog may close
  {
    control->SetFocus(false);
    if (control->GetControlType() == CGUIControl::GUICONTROL_BUTTON)
      ((CGUIButtonControl *)control)->SetAlpha(0xFF);
    else
      ((CGUIButtonControl *)control)->SetSelected(false);
  }
}