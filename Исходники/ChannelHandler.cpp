void ChannelHandler::DrawChannellist()
{
	if(g_pDrawingHandler == 0)
	{
		new DrawingHandler();
	}
	if(g_pDrawingHandler != 0)
	{
		//let's box this shit first
		//a black box with a nice fine white surrounding
		RECT *rect = new RECT;
		rect->left = 0;
		rect->right = this->leftbarsize;
		rect->top = 0;
		rect->bottom = this->height;

		HDC channelListDC = g_pDrawingHandler->getChannelListHDC();
		g_pDrawingHandler->SetChannelListRect(rect);


		BitBlt(channelListDC,rect->left-5,rect->top-5,rect->right - rect->left + 10,rect->bottom - rect->top + 10,NULL,0,0,WHITENESS);
		BitBlt(channelListDC,rect->left,rect->top,rect->right - rect->left,rect->bottom - rect->top,NULL,0,0,BLACKNESS);
		ExtFloodFill(channelListDC,(rect->left+rect->right)/2,(rect->top+rect->bottom)/2,RGB(0,0,0),FLOODFILLSURFACE);

		int TextSize = 18;
		RECT *temprect = new RECT;
		temprect->left = rect->left;
		temprect->right = rect->right;
		temprect->top = rect->top;
		temprect->bottom = rect->top+TextSize;


		char tempChar[200];

		if(this->ChannelList->begin() != this->ChannelList->end())
		{
			for (std::list<MessageBoxCF *>::iterator tempIter = ChannelList->begin(); tempIter != ChannelList->end(); tempIter++)
			{
				strncpy(tempChar,(*tempIter)->GetName().c_str(),200);
				snprintf(tempChar,200,"%s %i",tempChar,(*tempIter)->GetUnread());
			
				// new draw
				DrawText(channelListDC,tempChar,-1,temprect,DT_WORDBREAK + DT_CALCRECT);
				DrawText(channelListDC,tempChar,-1,temprect,DT_WORDBREAK);
				temprect->top = temprect->bottom;
				temprect->right = rect->right;
	/*
				// old draw
				DrawText(g_pBackbufferDC,tempChar,-1,temprect,DT_SINGLELINE + DT_VCENTER + DT_NOCLIP);
				temprect->top += TextSize;
				temprect->bottom += TextSize;
	*/			
			}
		}
		delete(temprect);
		delete(rect);
	}
}