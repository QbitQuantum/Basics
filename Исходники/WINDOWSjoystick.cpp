bool joystick_load(int id)
{
	JOYINFO joyinfo; 
	UINT wNumDevs; 
	BOOL bDevAttached; 
 
    if((wNumDevs = joyGetNumDevs()) == 0) 
        return false; 
		
    if (joySetCapture(enigma::hWnd, JOYSTICKID1 + id, NULL, FALSE)) 
    { 
        MessageBeep(MB_ICONEXCLAMATION); 
        MessageBox(enigma::hWnd, "Couldn't capture the joystick.", NULL, 
            MB_OK | MB_ICONEXCLAMATION); 
        return false;
    } 
	
	bDevAttached = joyGetPos(JOYSTICKID1 + id, &joyinfo) != JOYERR_UNPLUGGED; 
    if (!bDevAttached) 
        return false;
		
	return true;
}