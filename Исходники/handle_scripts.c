int refresh_gamepads(HWND hwnd)
{
	int test=FALSE;
	int i;
	LPDIRECTINPUT8 dinp;
	SendMessage(hwnd,CB_RESETCONTENT,0,0);
	if(test){
		DIDEVICEINSTANCE di;
		sprintf(di.tszInstanceName,"adaptoid");
		for(i=0;i<4;i++){
			di.guidInstance.Data1=rand();
			enum_gamepads(&di,hwnd);
		}
		printf("press key\n");
//		getkey();
	}
	else
	if(DirectInput8Create(GetModuleHandle(0),DIRECTINPUT_VERSION,&IID_IDirectInput8,(void *)&dinp,0)==DI_OK){
			IDirectInput8_EnumDevices(dinp, DI8DEVCLASS_GAMECTRL, enum_gamepads,
                      hwnd, DIEDFL_ATTACHEDONLY);
	}
	SendMessage(hwnd,CB_SETCURSEL,0,0);
	return TRUE;
}