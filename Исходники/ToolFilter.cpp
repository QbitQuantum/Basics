Rect ToolFilter::applyFilter(ToolFilter::Info *fi, Rect *clip, bool once)
{
	Core::self->getGui()->setCursor(CURSOR_WAIT);

	int w = (int)( floor(fi->matrix.mxw / 2.0) );
	int h = (int)( floor(fi->matrix.mxh / 2.0) );

	int exw = fi->matrix.mxw + 1;
	int exh = fi->matrix.mxh + 1;

	UINT *src0, *bmp0;
	BitmapData srcData, bmpData;

	Bitmap *src = fi->bmpSource;
	Rect srcRect(0,0,src->GetWidth(),src->GetHeight());

	if( clip == NULL ){
		clip = &srcRect;
	}
	else {
		int maxx = max(clip->X - exw,0);
		int maxy = max(clip->Y - exh,0);
		int ext = 2;

		srcRect = Rect(
			maxx,
			maxy,
			min(clip->Width + ext * exw,(int)src->GetWidth() - maxx),
			min(clip->Height + ext * exh,(int)src->GetHeight() - maxy)
			);
	}

	int bmpWidth = clip->Width;
	int bmpHeight = clip->Height;
	if( fi->smooth == true ){
		bmpWidth += 4 * exw;
		bmpHeight += 4 * exh;
	}

	Bitmap *bmp = new Bitmap(
		bmpWidth,
		bmpHeight,
		src->GetPixelFormat()
		);
	Rect bmpRect(0,0,bmp->GetWidth(),bmp->GetHeight());

	src->LockBits(
			&srcRect,
			ImageLockModeRead,
			src->GetPixelFormat(),
			&srcData
			);
	bmp->LockBits(
			&bmpRect,
			ImageLockModeWrite,
			bmp->GetPixelFormat(),
			&bmpData
			);
	src0 = (UINT *)srcData.Scan0;
	bmp0 = (UINT *)bmpData.Scan0;

	int srcWidth = srcData.Width;
	int srcHeight = srcData.Height;

	for( int x = 0; x < bmpWidth; x++ ){
		for( int y = 0; y < bmpHeight; y++ ){
			bmp0[y * bmpData.Stride / 4 + x] = ToolFilter::filterPixel(fi,&srcData,x,y,w,h); 
		}
	}
	if( fi->edgeTrace == true && fi->filterValue > 0 ){
		ToolFilter::Matrix oldMatrix = fi->matrix;

		fi->matrix = ToolFilter::allocMatrixEdgetrace(fi->filterValue,1);
		for( int x = 0; x < bmpWidth; x++ ){
			for( int y = 0; y < bmpHeight; y++ ){
				bmp0[y * bmpData.Stride / 4 + x] += ToolFilter::filterPixel(fi,&srcData,x,y,w,h); 
			}
		}
		fi->matrix = ToolFilter::allocMatrixEdgetrace(fi->filterValue,2);
		for( int x = 0; x < bmpWidth; x++ ){
			for( int y = 0; y < bmpHeight; y++ ){
				bmp0[y * bmpData.Stride / 4 + x] += ToolFilter::filterPixel(fi,&srcData,x,y,w,h); 
			}
		}

		fi->matrix = oldMatrix;
	}
	src->UnlockBits(&srcData);
	bmp->UnlockBits(&bmpData);

	fi->bmpEffect = bmp;

	int refils = 0;
	switch(fi->filterId){
		case ID_FILTER_SHARPEN:
			if( fi->filterValue > SHARPENMAX/2 )
				refils = fi->filterValue - SHARPENMAX/2;
			break;
		case ID_FILTER_GAUSSIANBLUR:
			if( fi->filterValue > GAUSSMAX )
				refils = fi->filterValue - GAUSSMAX;
			break;
	}
	Bitmap *source = fi->bmpSource;

	if( refils > 0 && once == false ){
		for(int i = 0; i < refils; i++ ){
			fi->bmpSource = fi->bmpEffect;
			fi->bmpEffect = NULL;

			ToolFilter::applyFilter(fi,NULL,true);

			delete fi->bmpSource;
		}
	}
	fi->bmpSource = source;

	Rect gridClip(clip->X,clip->Y,clip->Width,clip->Height);

	clip->X -= exw;
	clip->Y -= exh;

	Core::self->getGui()->setCursor();

	return gridClip;
}