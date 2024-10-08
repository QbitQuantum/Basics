VideoBuffer *DecorationTool::GetIcon(int toolID, int width, int height)
{
	VideoBuffer * newTexture = new VideoBuffer(width, height);
	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
			//if (toolID == DECO_LIGH)
			//	vid_buf[WINDOWW*(y+j)+(x+i)] = PIXRGB(PIXR(pc)-10*j, PIXG(pc)-10*j, PIXB(pc)-10*j);
			//else if (toolID == DECO_DARK)
			//	vid_buf[WINDOWW*(y+j)+(x+i)] = PIXRGB(PIXR(pc)+10*j, PIXG(pc)+10*j, PIXB(pc)+10*j);
			if (toolID == DECO_SMUDGE)
				newTexture->SetPixel(x, y, 0, 255-5*x, 5*x, 255);
			else if (toolID == DECO_DRAW || toolID == DECO_CLEAR)
				newTexture->SetPixel(x, y, Red, Green, Blue, Alpha);
			else
				newTexture->SetPixel(x, y, 50, 50, 50, 255);
		}
	}
	if (toolID == DECO_CLEAR)
	{
		int reverseRed = (Red+127)%256;
		int reverseGreen = (Green+127)%256;
		int reverseBlue = (Blue+127)%256;
		for (int y=4; y<12; y++)
		{
			newTexture->SetPixel(y+5, y-1, reverseRed, reverseGreen, reverseBlue, 255);
			newTexture->SetPixel(y+6, y-1, reverseRed, reverseGreen, reverseBlue, 255);
			newTexture->SetPixel(20-y, y-1, reverseRed, reverseGreen, reverseBlue, 255);
			newTexture->SetPixel(21-y, y-1, reverseRed, reverseGreen, reverseBlue, 255);
		}
	}
	else if (toolID == DECO_ADD)
		newTexture->AddCharacter(11, 4, '+', Red, Green, Blue, 255);
	else if (toolID == DECO_SUBTRACT)
		newTexture->AddCharacter(11, 4, '-', Red, Green, Blue, 255);
	else if (toolID == DECO_MULTIPLY)
		newTexture->AddCharacter(11, 3, 'x', Red, Green, Blue, 255);
	else if (toolID == DECO_DIVIDE)
		newTexture->AddCharacter(11, 4, '/', Red, Green, Blue, 255);
	return newTexture;
}