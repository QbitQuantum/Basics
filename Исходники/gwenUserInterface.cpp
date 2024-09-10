	MyTestMenuBar(Gwen::Controls::Base* pParent)
		:Gwen::Controls::MenuStrip(pParent)
	{
//		Gwen::Controls::MenuStrip* menu = new Gwen::Controls::MenuStrip( pParent );
		{
			Gwen::Controls::MenuItem* pRoot = AddItem( L"File" );
		
			pRoot = AddItem( L"View" );
//			Gwen::Event::Handler* handler =	GWEN_MCALL(&MyTestMenuBar::MenuItemSelect );
			pRoot->GetMenu()->AddItem( L"Profiler");//,,m_profileWindow,(Gwen::Event::Handler::Function)&MyProfileWindow::MenuItemSelect);

/*			pRoot->GetMenu()->AddItem( L"New", L"test16.png", GWEN_MCALL( ThisClass::MenuItemSelect ) );
			pRoot->GetMenu()->AddItem( L"Load", L"test16.png", GWEN_MCALL( ThisClass::MenuItemSelect ) );
			pRoot->GetMenu()->AddItem( L"Save", GWEN_MCALL( ThisClass::MenuItemSelect ) );
			pRoot->GetMenu()->AddItem( L"Save As..", GWEN_MCALL( ThisClass::MenuItemSelect ) );
			pRoot->GetMenu()->AddItem( L"Quit", GWEN_MCALL( ThisClass::MenuItemSelect ) );
			*/
		}
	}