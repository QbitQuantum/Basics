void CreateToolbars()
{
	if (Glb_toolbarArray.GetCount() > 0)
		return;

	IAcadMenuGroup *mnuGrp = NULL;
	if (!getAcadMenuGroup(&mnuGrp))
		return ;

	IAcadToolbars  *tlbrs = NULL;
	HRESULT hr = S_OK;
	hr = mnuGrp->get_Toolbars(&tlbrs);
	mnuGrp->Release();

	// 得到arx所在路径
	TCHAR lpPath[MAX_PATH] = {0};
	GetModuleFileName(GetModuleHandle("DistToolBar.arx"), lpPath, MAX_PATH);
	PathRemoveFileSpec(lpPath);
	PathAddBackslash(lpPath);

	CString strXmlFile = lpPath;
	strXmlFile += "toolbar.xml";

	// 得到icon路径
	PathAppend(lpPath, "icon");
	PathAddBackslash(lpPath);

	MSXML2::IXMLDOMDocumentPtr lpDocument;
	hr = lpDocument.CreateInstance(__uuidof(DOMDocument));

	if ( FAILED(hr) ) 
		_com_raise_error(hr);

	VARIANT_BOOL isSuccessful;

	// 装载XML字符串
	if (!lpDocument->load(_variant_t(strXmlFile)))
	{
		OutputDebugString("LoadXML failed!");

		return;
	}

	MSXML2::IXMLDOMElementPtr lpDocElement = NULL;
	lpDocument->get_documentElement(&lpDocElement);

	// toolbar list
	MSXML2::IXMLDOMNodeListPtr lpToolbarList = lpDocElement->getElementsByTagName(_bstr_t("toolbar"));

	MSXML2::IXMLDOMNodePtr lpToolbar = NULL;

	for ( ; (lpToolbar = lpToolbarList->nextNode()) != NULL ; )
	{

		MSXML2::IXMLDOMNodePtr lpCaptionNode = lpToolbar->attributes->getNamedItem("caption");
		CString strCaption = (char*)lpCaptionNode->text;

		OutputDebugString(strCaption);

		// 添加工具条
		IAcadToolbar  *tlbr = NULL;
		hr = tlbrs->Add(CComBSTR(strCaption), &tlbr);

		if FAILED(hr)
			continue;

		Glb_toolbarArray.Add(strCaption);

		// button list
		MSXML2::IXMLDOMNodeListPtr lpButtonList = lpToolbar->GetchildNodes();

		MSXML2::IXMLDOMNodePtr lpButton = NULL;

		for ( ; (lpButton = lpButtonList->nextNode()) != NULL ; )
		{
			MSXML2::IXMLDOMNodePtr lpToolTipNode = lpButton->attributes->getNamedItem("tooltip");
			CString strToolTip = (char*)lpToolTipNode->text;

			MSXML2::IXMLDOMNodePtr lpCommandNode = lpButton->attributes->getNamedItem("command");
			CString strCommand = (char*)lpCommandNode->text;
			strCommand += " ";

			MSXML2::IXMLDOMNodePtr lpIconNode = lpButton->attributes->getNamedItem("icon");
			CString strIcon = (char*)lpIconNode->text;

			OutputDebugStringX("tooltip=%s, command=%s, icon=%s", strToolTip, strCommand, strIcon);

			// 添加工具按钮
			IAcadToolbarItem *button=NULL;
			VARIANT index;
			index.vt = VT_I4;
			index.lVal = 100l;

			VARIANT vtFalse;
			vtFalse.vt = VT_BOOL;
			vtFalse.boolVal = VARIANT_FALSE;

			CString strIconFile = lpPath;
			strIconFile += strIcon;

			if (!PathFileExists(strIconFile))
			{
				strIconFile = lpPath;
				strIconFile += "dist.ico";
			}

			if (!PathFileExists(strIconFile)) continue;

			hr = tlbr->AddToolbarButton(index, CComBSTR(strToolTip), CComBSTR(strToolTip), CComBSTR(strCommand), vtFalse, &button);

			hr = button->SetBitmaps(CComBSTR(strIconFile), CComBSTR(strIconFile));

			button->Release();
		}

		tlbr->Dock(acToolbarDockRight);//acToolbarFloating
		tlbr->Release();
	}

	tlbrs->Release();

	return;
}