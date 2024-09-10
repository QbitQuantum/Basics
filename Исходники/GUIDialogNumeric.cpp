// \brief Show numeric keypad and verify user input against strToVerify.
// \param strToVerify Value to compare against user input.
// \param dlgHeading String shown on dialog title.
// \param bVerifyInput If set as true we verify the users input versus strToVerify.
// \return true if successful display and user input. false if unsucessful display, no user input, or canceled editing.
bool CGUIDialogNumeric::ShowAndVerifyInput(CStdString& strToVerify, const CStdString& dlgHeading, bool bVerifyInput)
{
  // Prompt user for password input
  CGUIDialogNumeric *pDialog = (CGUIDialogNumeric *)g_windowManager.GetWindow(WINDOW_DIALOG_NUMERIC);
  pDialog->SetHeading( dlgHeading );

  CStdString strInput = "";
  if (!bVerifyInput)
    strInput = strToVerify;
  pDialog->SetMode(INPUT_PASSWORD, (void *)&strInput);
  pDialog->DoModal();

  pDialog->GetOutput(&strInput);

  if (!pDialog->IsConfirmed() || pDialog->IsCanceled())
  {
    // user canceled out
    strToVerify ="";
    return false;
  }

  CStdString md5pword2;
  XBMC::XBMC_MD5 md5state;
  md5state.append(strInput);
  md5state.getDigest(md5pword2);

  if (!bVerifyInput)
  {
    strToVerify = md5pword2;
    strToVerify.ToLower();
    return true;
  }

  if (strToVerify.Equals(md5pword2))
    return true;  // entered correct password

  // incorrect password
  return false;
}