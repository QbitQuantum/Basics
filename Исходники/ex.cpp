bool wxExEx::Move(
  const wxString& begin_address, 
  const wxString& end_address, 
  const wxString& destination)
{
  if (m_STC->GetReadOnly())
  {
    return false;
  }

  const int dest_line = ToLineNumber(destination);

  if (dest_line == 0)
  {
    return false;
  }

  if (!SetSelection(begin_address, end_address))
  {
    return false;
  }

  if (begin_address.StartsWith("'"))
  {
    if (begin_address.size() > 1)
    {
      MarkerDelete(begin_address.GetChar(1));
    }
  }

  if (end_address.StartsWith("'"))
  {
    if (end_address.size() > 1)
    {
      MarkerDelete(end_address.GetChar(1));
    }
  }

  m_STC->BeginUndoAction();

  m_STC->Cut();
  m_STC->GotoLine(dest_line - 1);
  m_STC->Paste();

  m_STC->EndUndoAction();
  
  const int lines = wxExGetNumberOfLines(m_STC->GetSelectedText());
  if (lines >= 2)
  {
    m_Frame->ShowExMessage(wxString::Format(_("%d lines moved"), lines));
  }

  return true;
}