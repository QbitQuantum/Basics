bool UIShowDeskBand(bool t)
{
	CLSID CLSID_OVDeskBand ={0x6d5d9154, 0xb557, 0x4509, {0x82, 0x9e, 0x94, 0xb8, 0xbf, 0x96, 0x2e, 0x5b}};
	static HRESULT  bandID=0;
	bool ret=false;
	int i =0;
	
	
	murmur("hIMEWND:%x, AncestorWND:%x, TopWindow:%x, ForegroundWindow:%x, ShellWindow:%x "
				,hIMEWnd, GetAncestor(hIMEWnd,GA_ROOTOWNER), GetTopWindow(NULL), GetForegroundWindow(), GetShellWindow());
	
	

	//CLSID CLSIDDeskBand = {0x46b3d3ef, 0x71a, 0x4b7e, {0x8a, 0xa2, 0xe5, 0x60, 0x81, 0xd, 0xab, 0x35}};
	
	// only for vista
	/*
	ITrayDeskBand * spTrayDeskBand=0; 
	if(SUCCEEDED(CoCreateInstance(CLSID_TrayDeskBand, NULL, CLSCTX_LOCAL_SERVER,
									IID_ITrayDeskBand, (void**)&spTrayDeskBand)))
	{
		if(t) spTrayDeskBand->ShowDeskBand(CLSID_OVDeskBand);
		else spTrayDeskBand->HideDeskBand(CLSID_OVDeskBand);
	}
	*/
	CComPtr <IUnknown>    spBandService;  
	if(!spBandSite) 
	{
		if(SUCCEEDED(spBandService.CoCreateInstance(CLSID_TrayBandSiteService,   NULL)))
		{
			//HWND aWnd = GetAncestor(hIMEWnd, GA_ROOTOWNER);
			//if(aWnd) BringWindowToTop(aWnd); 
			murmur("Create IBandsite interface succeed"); 
			spBandService->QueryInterface(&spBandSite);
		}
		else 
		{
			murmur("Create IBandsite interface failed");
			
			spBand = NULL;
			spBandSite = NULL;
			//WaitForSingleObject(NULL, 3000);
			//SendMessage(hIMEWnd, WM_IME_NOTIFY, IMN_OPENSTATUSWINDOW, 0);
		
		}
	}
	
	
	
	if(spBandSite && !spBand ) 
	{
		if(SUCCEEDED(CoCreateInstance(CLSID_OVDeskBand,   
				NULL,   CLSCTX_INPROC,   IID_IUnknown,   (void**)&spBand)))
		{
	
	//	CComPtr<IObjectWithSite>   spSite;  
	//    if(SUCCEEDED(spBand->QueryInterface(&spSite))   )   
	//	{
	//		spSite->SetSite(spBandSite);  
	//	}
	//	else spBand = NULL;
		}
		else spBand = NULL;
		
	}
	
    //if(SUCCEEDED(spBandService.CoCreateInstance(CLSID_TrayBandSiteService,   NULL))   
	// 				  &&   SUCCEEDED(spBandService->QueryInterface(&spBandSite))   )  
	if( spBand && spBandSite)
    {  			
        	if(t) 
			{
			if(!((int)bandID >0))
			  {
				bandID = spBandSite->AddBand(spBand);  
				murmur("\tBandID:%d",bandID);
				if( (int)bandID >0 ) 
				{
					murmur("Create deskband succeeded."); 

					//spBand  =   NULL;  
					//spBandSite   =   NULL;   
					ret = true;  
				}
				else
				{
					murmur("Create deskband failed."); 
					spBand->ShowDW(0);  
					spBand  =   NULL; 
					spBandSite   =   NULL;   
					bandID =0; 
				}
			  }
			else
			{
				murmur("\tBandID:%d",bandID);
				murmur("Deskband created."); 
			}


				
			}
			else if((int)bandID >0)
			{
				
				
				//HWND aWnd = GetAncestor(hIMEWnd, GA_ROOTOWNER);
				//if(aWnd) BringWindowToTop(aWnd);
			    if(SUCCEEDED( spBandSite->RemoveBand(bandID))) 
				{
					murmur("\tBandID:%d",bandID);
					murmur("Remove deskband succeeded.");  
					
					spBand  =   NULL; 
					spBandSite   =   NULL;   
					bandID =0;
					
					//CoUninitialize();
					ret = true;
				}
				else
				{ 
					murmur("Remove deskband failed.");
					//spBand->CloseDW(0); 
					//spBand=NULL;
					//spBandSite = NULL;   
					//bandID =0;
					
					//HANDLE hEvent = CreateEvent(NULL,FALSE,FALSE,_T("OVE")); 
					//WaitForSingleObject(hEvent, 500);
					 
					//SendMessage(hIMEWnd, WM_IME_NOTIFY, IMN_CLOSESTATUSWINDOW, 0);
				}
				
			}
			else
			{
					murmur("Deskband was not created.");
					//spBand->CloseDW(0); 
					spBand=NULL;
					spBandSite = NULL;   
				
			}			  
            
                    
         
    }              
	

	//}
	//while(!ret && i++<3);
	murmur("::hIMEWND:%x, AncestorWND:%x, TopWindow:%x, ForegroundWindow:%x, ShellWindow:%x "
				,hIMEWnd, GetAncestor(hIMEWnd,GA_ROOTOWNER), GetTopWindow(NULL), GetForegroundWindow(), GetShellWindow());

    
	return ret;
	
}