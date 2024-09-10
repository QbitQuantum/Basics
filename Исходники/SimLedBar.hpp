	~SimLedBar()
	{
		//Free loaded images
		offTexture_.free();
		greenTexture_.free();
		orangeTexture_.free();
		redTexture_.free();
	}