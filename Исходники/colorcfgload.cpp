	void	ColorCfgLoad::Init()
	{
		_mapColor.clear();
		_mapName.clear();
		_mapExt.clear();
		_mapMask.clear();

		_DefaultColor = ColorEntry(7,0);
		_mapColor[Tolower("Default")] 	= ColorEntry(7,0);   // 색지정안된 파일 기본색상
		_mapColor[Tolower("MCD")]     	= ColorEntry(15,4);
		_mapColor[Tolower("MCDLine")] 	= ColorEntry(15,4);
		_mapColor[Tolower("MCDstat")] 	= ColorEntry(1,15);
		_mapColor[Tolower("Dir")]     	= ColorEntry(9,0);
		_mapColor[Tolower("Drive")]   	= ColorEntry(3,0);   // 메인창 드라이브 색
		_mapColor[Tolower("Line")]    	= ColorEntry(6,0);   // 메인창 선 색
		_mapColor[Tolower("Func")]    	= ColorEntry(15,6);  // 펑션키 보통
		_mapColor[Tolower("FuncA")]   	= ColorEntry(11,6);  // 펑션키 강조
		_mapColor[Tolower("Stat")]    	= ColorEntry(0,7);   // 상태선 보통
		_mapColor[Tolower("StatA")]   	= ColorEntry(15,7);  // 상태선 강조
		_mapColor[Tolower("Help")]    	= ColorEntry(11,6);  // 도움말
		_mapColor[Tolower("QCD")]     	= ColorEntry(15,4);  // 빨리찾기 메인	
		_mapColor[Tolower("Dialog")]  	= ColorEntry(15,12); // 대화상자 색
		_mapColor[Tolower("SelectBox")]	= ColorEntry(11,6); // 대화상자 색
		_mapColor[Tolower("Back")]    	= ColorEntry(0,0);
		_mapColor[Tolower("Edit")]		= ColorEntry(7,4);	 // 에디터 화면
		_mapColor[Tolower("EditInfo")]	= ColorEntry(2,4);	// 에디터 정보 보통
		_mapColor[Tolower("EditInfoA")] = ColorEntry(10,4);	// 에디터 정보 강조
	}