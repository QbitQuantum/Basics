BOOL vmsMetalinkFile::ReadHashNode(IXMLDOMNode *pNode, vmsMetalinkFile_File_Hash *hash)
{
	USES_CONVERSION;

	IXMLDOMNamedNodeMapPtr spAttrs;
	pNode->get_attributes (&spAttrs);
	if (spAttrs == NULL)
		return FALSE;

	IXMLDOMNodePtr spType;
	spAttrs->getNamedItem (L"type", &spType);
	if (spType == NULL)
		return FALSE;

	COleVariant vt;
	spType->get_nodeValue (&vt);
	ASSERT (vt.vt == VT_BSTR);
	if (vt.vt == VT_BSTR)
		hash->strAlgorithm = W2A (vt.bstrVal);
	
	CComBSTR bstrText;
	pNode->get_text (&bstrText);
	if (bstrText.Length () == 0)
		return FALSE;

	hash->strChecksum = W2A (bstrText);

	return TRUE;
}