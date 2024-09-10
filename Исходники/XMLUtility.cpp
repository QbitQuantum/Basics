void PrettyPrint(const TCHAR* name, CComPtr<IXMLDOMDocument> pXMLDoc)
{
	// perform formatting XSLT transform to get indented XML output
	CComPtr<IXMLDOMDocument> pXSLDoc;
	BSTR outputXML = NULL;
	HRESULT hr = CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,  IID_IXMLDOMDocument, (void**)&pXSLDoc);
	if (SUCCEEDED(hr)) {
		// load indenting XSL doc 
		VARIANT_BOOL result;
		CComBSTR indentXSL(
			"<xsl:stylesheet version=\"1.0\""
			"      xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">"
			"   <xsl:output method=\"xml\"/>"
			"   <xsl:param name=\"indent-increment\" select=\"'\t'\" />"
			"   <xsl:template match=\"node()\">"
			"      <xsl:param name=\"indent\" select=\"'&#xA;'\"/>"
			"      <xsl:value-of select=\"$indent\"/>"
			"      <xsl:copy>"
			"        <xsl:copy-of select=\"@*\" />"
			"        <xsl:apply-templates>"
			"          <xsl:with-param name=\"indent\""
			"               select=\"concat($indent, $indent-increment)\"/>"
			"        </xsl:apply-templates>"
			"        <xsl:if test=\"node()\">"
			"          <xsl:value-of select=\"$indent\"/>"
			"        </xsl:if>"
			"      </xsl:copy>"
			"   </xsl:template>"
//			"   <xsl:template match=\"comment()|processing-instruction()\">"
//			"      <xsl:copy />"
//			"   </xsl:template>"
//			"   <!-- WARNING: this is dangerous. Handle with care -->"
//			"   <xsl:template match=\"text()[normalize-space(.)='']\"/>"
			"</xsl:stylesheet>"
			);
		hr = pXSLDoc->loadXML(indentXSL, &result);
		if (SUCCEEDED(hr)) {
			// perform transform
			hr = pXMLDoc->transformNode(pXSLDoc, &outputXML);
		}
	}

	// output transformed XML if previous sequence succeeded, else normal XMLDoc save
	if (SUCCEEDED(hr)) {
		MaxSDK::Util::TextFile::Writer out;
		//Need UTF8
		if (out.Open(name, false, CP_UTF8))
		{
			// hack the UTF-16 back to UTF-8 (there probably is a way to mod the stylesheet to do this)
			wchar_t* enc = wcsstr(outputXML, L"\"UTF-16\"");
			if (enc != NULL) memcpy(enc, L"\"utf-8\" ", 8 * sizeof(wchar_t));
			// convert BSTR to MBCS for output
			// write the XML

			out.Write(outputXML);
			out.Close();
		}
		SysFreeString(outputXML);
	}
	else
	{
		// for a360 support - allows binary diff syncing
		MaxSDK::Util::Path storageNamePath(name);
		storageNamePath.SaveBaseFile();

		// save the XML graph out to the export file
		pXMLDoc->save(CComVariant(name));
	}

	
}