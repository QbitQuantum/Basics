	///////////////////////////////////////////////////////////
	//
	// TRANSFORMATIONS
	//
	// Fit src inside dst
	Rectf rectToFit( Rectf src, Rectf dst )
	{
		float sw = src.getWidth();
		float sh = src.getHeight();
		float sa = (sw / sh);	// aspect ratio
		float dw = dst.getWidth();
		float dh = dst.getHeight();
		float da = (dw / dh);	// aspect ratio
		// different ratio
		if (da > sa)
		{
			float scale = (dh / sh);
			float gap = (dw - (sw * scale)) / 2.0f;
			return Rectf( gap, 0, dw-gap, dh);
		}
		else if (da < sa)
		{
			float scale = (dw / sw);
			float gap = (dh - (sh * scale)) / 2.0f;
			return Rectf( 0, gap, dw, dh-gap );
		}
		// Same ratio
		else
			return dst;
	}