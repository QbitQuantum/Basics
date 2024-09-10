void sipXezPhoneApp::OnProcessStatusMessage(wxCommandEvent& event)
{
   wxWindow* pLogWindow = wxWindow::FindWindowById(IDR_STATUS_BOX, GetTopWindow());
   if (pLogWindow)
   {
      ((wxTextCtrl*)pLogWindow)->SetValue(mStatusMessage);
   }
    return;
}