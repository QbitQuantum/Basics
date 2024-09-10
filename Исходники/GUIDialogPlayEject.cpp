bool CGUIDialogPlayEject::ShowAndGetInput(const CFileItem & item,
  unsigned int uiAutoCloseTime /* = 0 */)
{
  // Make sure we're actually dealing with a Disc Stub
  if (!item.IsDiscStub())
    return false;

  // Create the dialog
  CGUIDialogPlayEject * pDialog = (CGUIDialogPlayEject *)g_windowManager.
    GetWindow(WINDOW_DIALOG_PLAY_EJECT);
  if (!pDialog)
    return false;

  // Figure out Line 1 of the dialog
  CStdString strLine1;
  if (item.GetVideoInfoTag())
  {
    strLine1 = item.GetVideoInfoTag()->m_strTitle;
  }
  else
  {
    strLine1 = URIUtils::GetFileName(item.GetPath());
    URIUtils::RemoveExtension(strLine1);
  }

  // Figure out Line 2 of the dialog
  CStdString strLine2;
  CXBMCTinyXML discStubXML;
  if (discStubXML.LoadFile(item.GetPath()))
  {
    TiXmlElement * pRootElement = discStubXML.RootElement();
    if (!pRootElement || strcmpi(pRootElement->Value(), "discstub") != 0)
      CLog::Log(LOGERROR, "Error loading %s, no <discstub> node", item.GetPath().c_str());
    else
      XMLUtils::GetString(pRootElement, "message", strLine2);
  }

  // Setup dialog parameters
  pDialog->SetHeading(219);
  pDialog->SetLine(0, 429);
  pDialog->SetLine(1, strLine1);
  pDialog->SetLine(2, strLine2);
  pDialog->SetChoice(ID_BUTTON_PLAY - 10, 208);
  pDialog->SetChoice(ID_BUTTON_EJECT - 10, 13391);
  if (uiAutoCloseTime)
    pDialog->SetAutoClose(uiAutoCloseTime);

  // Display the dialog
  pDialog->DoModal();

  return pDialog->IsConfirmed();
}