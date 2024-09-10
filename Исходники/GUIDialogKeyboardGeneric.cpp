bool CGUIDialogKeyboardGeneric::ShowAndGetInput(char_callback_t pCallback, const std::string &initialString, std::string &typedString, const std::string &heading, bool bHiddenInput)
{
  CGUIDialogKeyboardGeneric *pKeyboard = CServiceBroker::GetGUI()->GetWindowManager().GetWindow<CGUIDialogKeyboardGeneric>(WINDOW_DIALOG_KEYBOARD);

  if (!pKeyboard)
    return false;

  m_pCharCallback = pCallback;
  // setup keyboard
  pKeyboard->Initialize();
  pKeyboard->SetHeading(heading);
  pKeyboard->SetHiddenInput(bHiddenInput);
  pKeyboard->SetText(initialString);
  pKeyboard->Open();
  pKeyboard->Close();

  // If have text - update this.
  if (pKeyboard->IsConfirmed())
  {
    typedString = pKeyboard->GetText();
    return true;
  }
  else return false;
}