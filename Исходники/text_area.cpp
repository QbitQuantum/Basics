bool	Text_area::Init(int x, int y, int w, int h, const char* text)
{
	Window*		screen;
	SDL_Surface*	message;

	if (Interface::Init(x, y, w, h))
		return 1;
	screen = screen->GetInstance();
	message = TTF_RenderText_Blended(screen->Get_font(), text, this->__color);
	if (SDL_BlitSurface(message, 0, this->_surface, 0) == -1)
	{
		SDL_FreeSurface(message);
		return 1;
	}
	SDL_FreeSurface(message);
	this->__rect_message.x = message->w;
	this->__rect_message.y = 0;
	this->__rect_message.w = w - message->w;
	this->__rect_message.h = message->h;
	this->clear_message();
	return 0;
}