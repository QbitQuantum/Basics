CSEdDesktop::CSEdDesktop()
	: CGUIDesktop()
{
	try{
		assert(!SEdDesktop);
		SEdDesktop=this;

		RemoveFromTrash();
		MsgAcceptConsume(MsgMouseL|MsgMouseM|MsgMouseR);
		// MsgSetProduce(MsgAll);

		CGUIWindowPanel* panel = new CGUIWindowPanel(0,sy-STD_PANEL_HEIGHT-STD_PANEL_SHIFT,styleSet->Get("Panel"),this,true,false,0,0);
													//0,-STD_PANEL_SHIFT (pridani nahoru)
		push=false;

		iconDefaultHandler = new CSEdDesktopIconHandler();
		iconDefaultHandler->icons = new typeID[4];		// zadat velikost pole dle poctu icon (polozek typeID)

		SEdOpenedFiles = new CSEdOpenedFiles();

		AddStartMenu();

		InitDefaultIcons();

		iconDefaultHandler->ShowFileBrowser();

		AddToTrash();
	}
	catch(CExc c)
	{
		mainGUI->LogError(c);

		// vypis informace o chybe na obrazovce jako DebugMessage (prozatimni reseni)
		__time64_t ltime;
		_time64( &ltime );
		DebugMessage(0,"%s : %2d:%2d - %s",_ctime64( &ltime ), c.errnum, c.param, c.errstr);

		desktop=0;
		throw CExc(eGUI, E_INTERNAL,"CSEdDesktop::CSEdDesktop> Fatal error - cannot creat DESKTOP");
	}
}