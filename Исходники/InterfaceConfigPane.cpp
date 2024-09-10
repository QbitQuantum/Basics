void InterfaceConfigPane::OnThemeSelected(wxCommandEvent& event)
{
  SConfig::GetInstance().theme_name = WxStrToStr(m_theme_choice->GetStringSelection());

  wxCommandEvent theme_event{DOLPHIN_EVT_RELOAD_THEME_BITMAPS};
  theme_event.SetEventObject(this);
  ProcessEvent(theme_event);
}