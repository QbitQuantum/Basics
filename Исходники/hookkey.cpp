static LRESULT CALLBACK hookkeyproc(UINT nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode < 0)
	{ /* pass it on */
	 CallNextHookEx(hookKey, nCode, wParam, lParam);
	 return 0;
	} /* pass it on */
     


		DWORD keyflags = lParam;
		DWORD transitionFLAG = 0x80000000;
		DWORD repeatFLAG = 0x40000000;

		DWORD val = keyflags & transitionFLAG;

			

		if (wParam==VK_SHIFT) 
		{
			if (val==0)
				shiftDown = 1;
			else
				shiftDown = 0;
		}

		if (wParam==VK_MENU) 
		{
			if (val==0)
				altDown = 1;
			else
				altDown = 0;
		}

		if (wParam==VK_CONTROL) 
		{
			if (val==0)
				ctrlDown = 1;
			else
				ctrlDown = 0;
		}


		DWORD specialKeys = ctrlDown * 4 + shiftDown * 2 + altDown * 1;


	
		//Can this code prevent too many messages from being sent to vscap	and cause it to crash ?		
		unsigned long currentKeyTime = timeGetTime();
		unsigned long difftime = currentKeyTime - oldKeyTime;
		
		//ver 1.8
		if (difftime>150) {				
		
			//Repeating keys..
			if ((previousKey == wParam) && (difftime<300))
				return CallNextHookEx(hookKey, nCode, wParam, lParam);   		
			
			previousKey = wParam;
			
			//if (lParam>0) {
				
				
				//ShowWindow( hWndServerKey, SW_SHOW); 
			
				//PostMessage(hWndServerKey, WM_USER_KEYSTART , wParam, lParam);
				PostMessage(hWndServerKey, WM_USER_KEYSTART , wParam, specialKeys);
				oldKeyTime = currentKeyTime;
			//}

		}
			  
	
		 
	 
     return CallNextHookEx(hookKey, nCode, wParam, lParam);    
    
} 