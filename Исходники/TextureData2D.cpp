	void TextureData2D :: Upload ( int target )
	{
		glTexImage2D ( target,
			           0,
					   GetInternalFormat ( ),
					   Width,
					   Height,
					   0,
					   GetPixelFormat ( ),
					   GL_FLOAT,
					   Pixels );
	}