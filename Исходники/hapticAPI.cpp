void hapticAPI::mouseRenderLeftButton(){
	INPUT input[1];
	ZeroMemory(input, 1*sizeof(INPUT));

	input[0].type = INPUT_MOUSE;
	input[0].mi.dwExtraInfo = GetMessageExtraInfo();
	input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;

	SendInput(1, input, sizeof(INPUT));

	/*
	typedef struct tagINPUT {
		DWORD type;		= INPUT_MOUSE:		The event is a mouse event. Use the mi structure of the union.
						= INPUT_KEYBOARD:	The event is a keyboard event. Use the ki structure of the union.
						= INPUT_HARDWARE:	The event is a hardware event. Use the hi structure of the union

		union {
			MOUSEINPUT    mouse;
			KEYBDINPUT    ki;
			HARDWAREINPUT hi;
		};
	} INPUT
					typedef struct tagMOUSEINPUT {
								  LONG      dx;
								  LONG      dy;
								  DWORD     mouseData;
								  DWORD     dwFlags;
								  DWORD     time;
								  ULONG_PTR dwExtraInfo;
					} MOUSEINPUT


					INPUT input

					//input.type = INPUT_MOUSE;
					//input.mi.dx = ;  //coordinate assolute o incrementali rispetto all'ultima posizione, depending on dwFlags
					//input.mi.dy = ;  //coordinate assolute o incrementali rispetto all'ultima posizione, depending on dwFlags
					//input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP;
					//input.mi.dwExtraInfo = GetMessageExtraInfo();

	*/
}