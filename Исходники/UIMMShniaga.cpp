void CUIMMShniaga::CreateList(xr_vector<CUIStatic*>& lst, CUIXml& xml_doc, LPCSTR path){
	CGameFont* pF;
	u32	color;
	float button_height				= xml_doc.ReadAttribFlt("button", 0, "h");
	R_ASSERT						(button_height);

	CUIXmlInit::InitFont			(xml_doc, path, 0, color, pF);
	R_ASSERT						(pF);

	int nodes_num					= xml_doc.GetNodesNum(path, 0, "btn");

	XML_NODE* tab_node				= xml_doc.NavigateToNode(path,0);
	xml_doc.SetLocalRoot			(tab_node);

	CUIStatic* st;

	for (int i = 0; i < nodes_num; ++i)
	{		
		st							= new CUIStatic();
		st->SetWndPos				(Fvector2().set(0,0));
		st->SetWndSize				(Fvector2().set(m_view->GetDesiredChildWidth(), button_height));
		st->SetTextComplexMode		(false);
		st->SetTextST				(xml_doc.ReadAttrib	("btn", i, "caption"));
		if (pF)
			st->SetFont				(pF);

		float font_height			= st->GetFont()->GetHeight();
		UI()->ClientToScreenScaledHeight(font_height);

		st->SetTextY				( (button_height-font_height)/2.0f );
		st->SetTextColor			(color);
		st->SetTextAlignment		(CGameFont::alCenter);
		st->SetWindowName			(xml_doc.ReadAttrib("btn", i, "name"));
		st->SetMessageTarget		(this);


		lst.push_back(st);
	}
	xml_doc.SetLocalRoot(xml_doc.GetRoot());

}