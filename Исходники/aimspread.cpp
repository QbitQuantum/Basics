void sendtext(int msngrwindow)
{
	if(msngrwindow == 2)
		keybd_event(VK_CONTROL,0,0 , 0);
	keybd_event(VK_RETURN,0,0 , 0);
	keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP , 0);
	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP , 0);

	return;
}