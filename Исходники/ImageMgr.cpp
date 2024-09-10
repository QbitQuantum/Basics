Image* ImageMgr::GetImage()
{
	unsigned int height = GetHeight();
	unsigned int width = GetWidth();
	Image *data = new Image(width, height);

	Sprite2D *spr = GetSprite2D();

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			data->SetPixel(x,y, spr->GetPixel(x,y));
		}
	}

	core->GetVideoDriver()->FreeSprite(spr);

	return data;
}