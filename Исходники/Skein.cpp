bool Skein::BoolFromXML(IXMLDOMNode* node, LPWSTR query, bool ifNon)
{
  CComBSTR text = StringFromXML(node,query);
  if (text.Length() > 0)
    return wcscmp(text.m_str,L"YES") == 0;
  return ifNon;
}