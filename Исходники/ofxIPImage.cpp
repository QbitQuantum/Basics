LRESULT CALLBACK ofxIPImage::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
	static CREATESTRUCT   *cs;
	static HWND	id,connected;
	
	ofxIPImage* camera = (ofxIPImage*) GetWindowLongPtr(hwnd,GWLP_USERDATA);
	if (camera!=NULL)
	{
		if (!camera->isSettedDefaultSettings)
		{
			camera->isSettedDefaultSettings = true;
			int firstValue, secondValue, minValue, maxValue;
			bool isEnabled,isAuto;
			camera->getCameraFeature(BASE_ID,&firstValue,&secondValue,&isAuto,&isEnabled,&minValue,&maxValue);
			SendMessage(GetDlgItem(hwnd, 0), TBM_SETPOS, TRUE, firstValue);
			string id1 = ofToString(firstValue);
			cout<<"valueof id:"<<id1<<endl;
			SetWindowTextA(id,id1.c_str());

			camera->getCameraFeature(BASE_CONNECTED,&firstValue,&secondValue,&isAuto,&isEnabled,&minValue,&maxValue);
			SendMessage(GetDlgItem(hwnd, 1), TBM_SETPOS, TRUE, firstValue);
			SetWindowTextA(connected,firstValue ? "Connected" : "Not Connected");

					
			
		}
	}

	switch (iMsg) 
    {
		case WM_CREATE:
			{
				CreateWindow("STATIC", "Client ID:", SS_LEFT | WS_CHILD | WS_VISIBLE, 
                                    10, 10, 140, 20, hwnd, NULL, NULL, NULL);
				id = CreateWindow("static", " ",SS_LEFT | WS_CHILD | WS_VISIBLE,
										70, 10, 145, 25,hwnd,(HMENU)0, NULL, NULL);
				CreateWindow("STATIC", "Connection Status:", SS_LEFT | WS_CHILD | WS_VISIBLE, 
                                    10, 30, 140, 20, hwnd, NULL, NULL, NULL);
				connected = CreateWindow("static", " ",SS_LEFT | WS_CHILD | WS_VISIBLE,
										135, 30, 145, 25,hwnd,(HMENU)1, NULL, NULL);
				
				
			}
			break;
		case WM_CLOSE :
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY :
			PostQuitMessage(0);
			break;
   }
   return DefWindowProc(hwnd, iMsg, wParam, lParam);
}