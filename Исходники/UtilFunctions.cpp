void MouseDown(TMouseButton button)
{


#ifndef USESENDINPUT
	if(button==mbLeft)
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	}
	else
	if(button==mbRight)
	{
		mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
	}
	else
	if(button==mbMiddle)
	{
		mouse_event(MOUSEEVENTF_MIDDLEDOWN,0,0,0,0);
	}
#else
	INPUT    input;
	::ZeroMemory(&input, sizeof(input));

	if(button==mbLeft)
	{
		if(IsKeyPressed(VK_LBUTTON)) return;

		input.type      = INPUT_MOUSE;
		input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
		::SendInput(1,&input,sizeof(INPUT));
	}
	else
	if(button==mbRight)
	{
		if(IsKeyPressed(VK_RBUTTON)) return;

		input.type      = INPUT_MOUSE;
		input.mi.dwFlags  = MOUSEEVENTF_RIGHTDOWN;
		::SendInput(1,&input,sizeof(INPUT));

	}
	else
	if(button==mbMiddle)
	{
		if(IsKeyPressed(VK_MBUTTON)) return;

		input.type      = INPUT_MOUSE;
		input.mi.dwFlags  = MOUSEEVENTF_MIDDLEDOWN;
		::SendInput(1,&input,sizeof(INPUT));

	}


#endif


//	if(sleepsec) Sleep(sleepsec);

}