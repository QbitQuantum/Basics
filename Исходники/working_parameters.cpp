static IXMLDOMElement *FindFirstElement(IXMLDOMElement *parent, LPCTSTR name, int length) {
  if (parent == NULL) {
    return NULL;
  }
  if (length == -1) {
    length = _tcslen(name);
  }
  CComPtr<IXMLDOMNode> child;
  parent->get_firstChild(&child);
  while (child != NULL) {
    CComQIPtr<IXMLDOMElement> e(child);
    if (e != NULL) {
      CComBSTR tagName;
      e->get_tagName(&tagName);
      if (tagName.Length() == length && wcsncmp(tagName, name, length) == 0) {
        return e.Detach();
      }
    }
    CComPtr<IXMLDOMNode> next;
    child->get_nextSibling(&next);
    child = next;
  }
  return NULL;
}