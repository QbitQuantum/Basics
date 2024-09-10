static void keyboard_update(void)
{
	static SDL_keysym keysym;
	static XKEYBOARD_STROKE keystroke;
	
	if( 0 > XInputGetKeystroke(&keystroke) )
		return;

	if (keystroke.ucKeyCode == 0)
		return;

	if ( keystroke.ucFlags & XKEYBOARD_KEYUP ) {
		SDL_PrivateKeyboard(SDL_RELEASED, TranslateKey(keystroke,&keysym, 1));
	} else {
		SDL_PrivateKeyboard(SDL_PRESSED,  TranslateKey(keystroke,&keysym, 0));
	}
}