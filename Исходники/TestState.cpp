void BmpToFont(const std::string &font)
{
	std::string dat = "./" + font + ".DAT";
	std::string bmp = "./" + font + ".BMP";
	SDL_Surface *orig = SDL_LoadBMP(bmp.c_str());

	Surface *s = new Surface(orig->w, orig->h);

	SDL_Color clr[8];
	clr[0].r = 0;
	clr[0].g = 0;
	clr[0].b = 0;
	for (int i = 1; i < 8; ++i)
	{
		clr[i].r = 256-i*32;
		clr[i].g = 256-i*32;
		clr[i].b = 256-i*32;
	}
	s->setPalette(clr, 0, 8);

	SDL_BlitSurface(orig, 0, s->getSurface(), 0);

	std::ofstream out (dat.c_str(), std::ios::out | std::ios::binary);
	for (int y = 0; y < s->getHeight(); ++y)
	{
		for (int x = 0; x < s->getWidth(); ++x)
		{
			char c = s->getPixel(x, y);
			out.write(&c, 1);
		}
	}
	out.close();
}