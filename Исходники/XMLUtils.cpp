void setNodeText(MSXML2::IXMLDOMNodePtr& node, const String& text) {
  _bstr_t nodeText(text.c_str());
  const HRESULT putTextRes = node->put_text(nodeText);
  if (FAILED(putTextRes)) {
    _com_raise_error(putTextRes);
  }
}