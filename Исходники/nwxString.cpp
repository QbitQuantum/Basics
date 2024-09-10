void nwxString::SetFileExtension(wxString *ps, const wxString &sExt)
{
  // STOP HERE
  wxChar dot('.');
  int nFs = ps->Find(wxChar('/'),true);
#ifdef __WXMSW__
  int nFb = ps->Find(wxChar('\\'),true);
#endif
  int nP  = ps->Find(dot,true);
  bool bUseDot =
    ( (nP != wxNOT_FOUND) // dot found
      && ((nFs == wxNOT_FOUND) || (nFs < nP)) // dot after '/'
#ifdef __WXMSW__
      && ((nFb == wxNOT_FOUND) || (nFb < nP)) // dot after '\'
#endif
    );
  if(bUseDot)
  {
    ps->Truncate(nP);
  }
  if( sExt.Len() && (sExt.GetChar(0) != dot) )
  {
    ps->Append(dot);
  }
  ps->Append(sExt);
}