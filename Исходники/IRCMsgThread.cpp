void IRCMsgThread::SetUserColor(std::wstring User,std::wstring Color){ //already lowercase
	//std::map<std::wstring,unsigned int> UserColorMap
	unsigned int iColor;
	std::wregex color_pattern(L"^#[0-9a-fA-F]{6}$");
	//std::wsmatch base_match;
	if(std::regex_match(Color, color_pattern)){
		int iErrno=swscanf_s(Color.substr(1).c_str(),L"%x",&iColor);
	}
	else {
		iColor=1<<24;
		if(Color.compare(L"red")==0)				iColor=0x00FF0000;
		else if(Color.compare(L"blue")==0)			iColor=0x000000FF;
		else if(Color.compare(L"green")==0)			iColor=0x00008000;
		else if(Color.compare(L"firebrick")==0)		iColor=0x00B22222;
		else if(Color.compare(L"coral")==0)			iColor=0x00FF7F50;
		else if(Color.compare(L"yellowgreen")==0)	iColor=0x009ACD32;
		else if(Color.compare(L"orangered")==0)		iColor=0x00FF4500;
		else if(Color.compare(L"seagreen")==0)		iColor=0x002E8B57;
		else if(Color.compare(L"goldenrod")==0)		iColor=0x00D2691E;
		else if(Color.compare(L"cadetblue")==0)		iColor=0x005F9EA0;
		else if(Color.compare(L"dodgerblue")==0)	iColor=0x001E90FF;
		else if(Color.compare(L"hotpink")==0)		iColor=0x00FF69B4;
		else if(Color.compare(L"blueviolet")==0)	iColor=0x008A2BE2;
		else if(Color.compare(L"springgreen")==0)	iColor=0x0000FF7F;
		else if(Color.compare(L"black")==0)			iColor=0x00000000;
		else if(Color.compare(L"gray")==0)			iColor=0x00808080;
		else if(Color.compare(L"darkred")==0)		iColor=0x008B0000;
		else if(Color.compare(L"midnightblue")==0)	iColor=0x00191970;
		else if(Color.compare(L"deeppink")==0)		iColor=0x00FF1493;
	}
	//onDebugMsg(L"SetUserColor: %ls, %ls, 0X%08X\n",User.c_str(),Color.c_str(),iColor);
		std::pair<std::map<std::wstring,unsigned int>::iterator,bool> ret=UserColorMap.insert( std::pair<std::wstring,unsigned int>(User,iColor|0xFF000000) );
		if (ret.second==false) ret.first->second=iColor|0xFF000000;
}