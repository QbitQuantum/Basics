void Blob2D::resize(short destLeft, short destTop, short destWidth, short destHeight)
{
	if( width == 0 && height == 0)
	{
		size_t siz = Bitmap::size(destWidth,destHeight);
		if( alloc_size < siz )
		{
			if(ptr)
				mem_del(ptr);
			ptr = (Bitmap *)mem_add((alloc_size = siz + DEFAULT_BLOB2D_INC));
		}
		memset(ptr, BACKGROUND_COLOR, siz);
		ptr->init(destWidth, destHeight);
	}
	else if( destWidth == 0 && destHeight == 0 )
	{
		err_when(!ptr);
		ptr->init(destWidth, destHeight);
	}
	else if( left_edge == destLeft && top_edge == destTop && width == destWidth )
	{
		if( destHeight == height )
			return;		// unchange

		size_t siz = Bitmap::size(destWidth,destHeight);
		if( alloc_size < siz )
		{
			ptr = (Bitmap *)mem_resize(ptr, (alloc_size = siz + DEFAULT_BLOB2D_INC));
		}

		if( destHeight > height && destWidth > 0 )
		{
			int y2 = top_edge+height;	// must keep the old instant
			height = destHeight;			// as height must be change to make fill_area correct

			// extend, then fill the new with the background color
			fill_area(destLeft, top_edge+height, destLeft+destWidth-1, destTop+destHeight-1, BACKGROUND_COLOR, 0);
		}
	}
	else if( left_edge <= destLeft && top_edge <= destTop &&
		left_edge+width >= destLeft+destWidth && top_edge+height >= destTop+destHeight)
	{
		// clipping
		unsigned char *src = ptr->get_ptr(destLeft-left_edge, destTop-top_edge);
		int srcPitch = ptr->get_pitch();
		ptr->init(destWidth, destHeight);
		unsigned char *dest = ptr->get_ptr();
		int destPitch = ptr->get_pitch();

		for(int y = 0; y < destHeight; ++y, src += srcPitch, dest += destPitch )
			memmove(dest, src, destWidth);

		// ptr = (Bitmap *)mem_resize(ptr, ptr->size());
	}
	else
	{
		// general resize, new another buffer
		// copy range, intersection of two area :
		short copyLeft, copyTop, copyWidth, copyHeight;
		copyLeft = MAX(destLeft, left_edge);
		copyTop = MAX(destTop, top_edge);
		copyWidth = MIN(destLeft + destWidth, left_edge + width) - copyLeft;
		copyHeight = MIN(destTop + destHeight, top_edge + height) - copyTop;

		{
			size_t siz = Bitmap::size(destWidth, destHeight);
			Bitmap *newPtr = (Bitmap *)mem_add(siz + DEFAULT_BLOB2D_INC);
			memset(newPtr, BACKGROUND_COLOR, siz);
			newPtr->init(destWidth, destHeight);

			if( copyWidth > 0 && copyHeight > 0 )
			{
				int yCount = 0;
				unsigned char *src = ptr->get_ptr(copyLeft-left_edge, yCount+copyTop-top_edge );
				unsigned char *dest = newPtr->get_ptr(copyLeft-destLeft, yCount+copyTop-destTop );

				for( ; yCount < copyHeight; ++yCount, src += ptr->get_pitch(), dest += ptr->get_pitch() )
				{
					// unsigned char *src = (yCount+copyTop-top_edge)*width + copyLeft-left_edge;
					// unsigned char *dest = (yCount+copyTop-destTop)*destWdith + copyLeft-destLeft;
					memcpy(dest, src, copyWidth);
				}
			}

			// assign to the newPtr now
			left_edge = destLeft;
			top_edge = destTop;
			width = destWidth;
			height = destHeight;
			if(ptr)
				mem_del(ptr);
			ptr = newPtr;
		}

		// fill rest area with background color
		if( top_edge < copyTop && width > 0)
		{
			fill_area(left_edge, top_edge, left_edge+width-1, copyTop, BACKGROUND_COLOR, 0 );
		}

		// fill bottom
		if( top_edge+height > copyTop+copyHeight && width > 0)
		{
			fill_area(left_edge, copyTop+copyHeight, left_edge+width-1, top_edge+height-1, BACKGROUND_COLOR, 0 );
		}

		// fill left
		if( left_edge < copyLeft && destHeight > 0)
		{
			fill_area(left_edge, copyTop, copyLeft-1, copyTop+copyHeight-1,
				BACKGROUND_COLOR, 0);
		}

		// fill right
		if( left_edge+width > copyLeft+copyWidth && destHeight > 0 )
		{
			fill_area(copyLeft+copyWidth, copyTop, left_edge+width, copyTop+copyHeight-1,
				BACKGROUND_COLOR, 0);
		}
	}

	left_edge = destLeft;
	top_edge = destTop;
	width = destWidth;
	height = destHeight;
}