	//--------------------------------------------------------------------------------
	void UICharacterLogin::setPanelValue( Char16* frontServerName, Char* ip, I32 port)
	{
		IText* text = getLayout()->getText("Text_cha");
		std::wstring ipStr;
		Char16 temp[2048] ={0};
		MGStrOp::toString(ip,ipStr);

		MGStrOp::sprintf(temp,2048,
			L"ÕËºÅÃû%s£¬\tIP%s,\nPort%d,\n",
			frontServerName,ipStr.c_str(),port);

		if (text)
		{
			text->getWidget()->setCaption(temp);
		}
	}