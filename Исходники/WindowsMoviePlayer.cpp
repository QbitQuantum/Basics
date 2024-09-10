	virtual void ShutdownModule() override
	{
		if( MovieStreamer.IsValid() )
		{
			MovieStreamer.Reset();

			MFShutdown();
		}
	}