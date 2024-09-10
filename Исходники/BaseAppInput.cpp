bool BaseAppInput::runFrame(void)
{
	//ideally, we would be using events. However, that tended to result in either segfaults or a hang when I tried it. *sigh*
	//so, we'll fake events on our own
	if (! handleKeyboard(NULL) || ! handleMouse())
	{
		return false;
	}
	
	SDL_Event evt;
	while (SDL_PollEvent(&evt)) //need to make sure it's not null
	{
		if (!processEvent(&evt))
		{
			return false;
		}
	}
	
	frameDone();
	
	return true;
}