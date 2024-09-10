		if(alignmentVert == ALIGN_MIDDLE)
			voffset = (lineheight >> 1) * (1-textDynNum);

		int left = this->GetLeft();
		int top  = this->GetTop() + voffset;

		for(int i=0; i < textDynNum; ++i)
			fontSystem[currentSize]->drawText(left, top+i*lineheight, textDyn[i], c, style);
	}
	else
	{
		if(textDynNum == 0)
		{
			textDynNum = 1;
			textDyn[0] = wcsdup(text);
			int len = wcslen(textDyn[0]);

			while(fontSystem[currentSize]->getWidth(textDyn[0]) > maxWidth)
				textDyn[0][--len] = 0;
		}

		if(textScroll == SCROLL_HORIZONTAL)
		{
			if(fontSystem[currentSize]->getWidth(text) > maxWidth && (FrameTimer % textScrollDelay == 0))
			{
				if(textScrollInitialDelay)
				{
					--textScrollInitialDelay;
				}
				else