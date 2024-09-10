wxString CSVQuote(const wxString& str)
{
  wxString rc;
  if (str.Length()) {
    wxString quoted = str;
    quoted.Replace(wxT("\""), wxT("\"\""));
    rc = wxT("\"");
    rc += quoted;
    rc += wxT("\"");
  }
  return rc;
}