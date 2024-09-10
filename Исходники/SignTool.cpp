VideoBuffer * SignTool::GetIcon(int toolID, int width, int height)
{
	VideoBuffer * newTexture = new VideoBuffer(width, height);
	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
			pixel pc =  x==0||x==width-1||y==0||y==height-1 ? PIXPACK(0xA0A0A0) : PIXPACK(0x000000);
			newTexture->SetPixel(x, y, PIXR(pc), PIXG(pc), PIXB(pc), 255);
		}
	}
	newTexture->AddCharacter((width/2)-5, (height/2)-5, 0xE021, 32, 64, 128, 255);
	newTexture->BlendCharacter((width/2)-5, (height/2)-5, 0xE020, 255, 255, 255, 255);
	return newTexture;
}