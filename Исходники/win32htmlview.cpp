	Win32HtmlViewRep( Win32HtmlView *view, HWND hw,int style ):hwnd(hw){

		owner=view;
		site.rep=this;
		eventsink.rep=this;
		frame.rep=this;
		
		viewstyle=style;
		emitNavEvent=!!(viewstyle & BBHtmlView::NONAVIGATE);

		currenturl=new BBString("");
		eventurl=new BBString("");

		OleCreate( CLSID_WebBrowser,IID_IOleObject,OLERENDER_DRAW,0,&site,&storage,(void**)&oleObject );

		OleSetContainedObject( oleObject,TRUE);

		oleObject->SetHostNames(L"Web Host",L"Web View");
		oleObject->QueryInterface(IID_IWebBrowser2,(void**)&iBrowser);
		oleObject->QueryInterface(IID_IOleInPlaceObject,(void**)&inPlaceObject );

		oleObject->QueryInterface(IID_IConnectionPointContainer,(void**)&iConnection);
		iConnection->FindConnectionPoint(DIID_DWebBrowserEvents, &iConnectionPoint);
		iConnectionPoint->Advise((LPUNKNOWN)&eventsink, &dwCookie);

		RECT rect;
		::GetClientRect( hwnd,&rect );
		oleObject->DoVerb(OLEIVERB_SHOW,NULL,&site,-1,hwnd,&rect);
		go( "about:blank" );
	}