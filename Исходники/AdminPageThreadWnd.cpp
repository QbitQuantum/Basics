CString CAdminPageThreadWnd::GetSender()
{
  CComBSTR bstrSender;
  if (FAILED(m_spEvent->get_SubjectName(&bstrSender)))
    return CString();
  return CString(bstrSender.m_str,bstrSender.Length());
}