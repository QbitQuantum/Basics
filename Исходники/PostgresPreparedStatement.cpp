wxString PostgresPreparedStatement::TranslateSQL(const wxString& strOriginalSQL)
{
  int nParameterIndex = 1;
  wxString strReturn = wxEmptyString;//strOriginalSQL;
  /*
  int nFound = strReturn.Replace(_("?"), wxString::Format(_("$%d"), nParameterIndex), false);
  while (nFound != 0)
  {
    nParameterIndex++;
    nFound = strReturn.Replace(_("?"), wxString::Format(_("$%d"), nParameterIndex), false);
  }
  */
  bool bInStringLiteral = false;
  size_t len = strOriginalSQL.length();
  for (size_t i = 0; i < len; i++)
  {
    wxChar character = strOriginalSQL[i];
    if ('\'' == character)
    {
      // Signify that we are inside a string literal inside the SQL
      bInStringLiteral = !bInStringLiteral;
      // Pass the character on to the return string
      strReturn += character;
    }
    else
    {
      if ('?' == character)
      {
        if (bInStringLiteral)
        {
          // Pass the character on to the return string
          strReturn += character;
        }
        else
        {
          // Replace the question mark with a prepared statement placeholder
          strReturn += wxString::Format(_("$%d"), nParameterIndex);
          nParameterIndex++;
        }
      }
      else
      {
        // Pass the character on to the return string
        strReturn += character;
      }
    }
  }

  return strReturn;
}