	void strokeLineV(SDL_Surface *surf, uint8_t grey,
	                 int x, int y, int length, int width)
	{
		fillRect(surf, grey, x-width/2, y, width, length);
	}