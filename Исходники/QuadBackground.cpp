void QuadBackground::calculateTextureSize(int imageWidth, int imageHeight, int & _textureWidth, int & _textureHeight)
{
	if (USE_POWER2_TEXTURES)
	{
		int heightLog = ceilf(logbf((float)imageHeight))+1;
		int widthLog = ceilf(logbf((float)imageWidth))+1;

		_textureHeight = (int)pow(2,heightLog);
		_textureWidth = (int)pow(2,widthLog);
	}
	else
	{
		_textureWidth = imageWidth;
		_textureHeight = imageHeight;
	}
}