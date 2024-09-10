BOOL CPageMesTemplates::SaveSettings()
{
	UpdateData();

	WriteOptionInt(IDS_OFSMESSENGER,IDS_SEND_MESSAGE_TEMPLATE_AUTO,m_ShowAuto);

	CComPtr<IXMLDOMDocument>	pMTDoc	=	NULL;
	pMTDoc.CoCreateInstance(CLSID_DOMDocument40,NULL,CLSCTX_INPROC_SERVER);

	if(pMTDoc)
	{
		USES_CONVERSION;

		CComBSTR	bsRootXML	=	L"<message_templates/>";

		VARIANT_BOOL	varLoad	=	VARIANT_FALSE;
		pMTDoc->loadXML(bsRootXML,&varLoad);

		//-------------------------------------------------------------------------------------
		CComPtr<IXMLDOMNode>	pRoot;

		pMTDoc->selectSingleNode(L"message_templates",&pRoot);

		for(int Index = 0; Index<m_TemplateList.GetItemCount();Index++)
		{
			CComPtr<IXMLDOMNode>	pItem;
			insertSingleNode(pRoot,CComBSTR(L"mt"),NULL,NULL,&pItem);

			
			insertSingleNode(pItem,CComBSTR(L"name"),NULL,T2BSTR(m_TemplateList.GetItemText(Index,0)));
			insertSingleNode(pItem,CComBSTR(L"text"),NULL,T2BSTR(m_TemplateList.GetItemText(Index,1)));
		}

		//-------------------------------------------------------------------------------------

		CString strSection;
		strSection.Format(_T("%s\\%s\\%d"),GetString(IDS_INFO),m_UserRole,m_UserId);

		CComBSTR bsOutXML;
		pMTDoc->get_xml(&bsOutXML);

		//-------------------------------------------------------------------------------------

		CString strMessageTemplateXML = W2CT(bsOutXML);
			
		SetRegFileText(strSection,GetString(IDS_MESSAGE_TEMPLATES_REG),strMessageTemplateXML);
	}

	return CMcSettingsPage::SaveSettings();
}