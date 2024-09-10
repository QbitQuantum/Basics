void CDialogPromptNewerFile::SetupURL(const wxFileName &fn)
{
  const wxString sDir = fn.GetPath();
  m_sDirURL.Alloc(sDir.Len() + 8);
  m_sDirURL = "file:///";
  m_sDirURL.Append(sDir);
}