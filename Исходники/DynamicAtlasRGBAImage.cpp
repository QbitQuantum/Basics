bool DynamicAtlasRGBAImage::AddImageRect(const Size2U& size,int pitch,const MemoryData& imageData, PixelType pixelType,
								  Rect2U& outRect, bool isFlipY/*=false*/,GraphicsPixelConvertMode mode/*=PixelConvertMode::Normal*/)
{
	RETURN_FALSE_IF(size>mMaxImageSize);
	outRect=mPack.Insert(size,SkylineBinPack::LevelChoiceHeuristic::LevelBottomLeft);
	if (outRect!=Rect2U::Zero)
	{
		outRect.Size-=1;	//should -1 to remove edge
		CopyImage(outRect,imageData,pixelType,pitch,isFlipY,mode);
		return true;
	}

	RETURN_FALSE_IF(mImageSize>=mMaxImageSize);	//is full


	//try to expand
	//1.new a bigger image
	Size2U newImageSize=mImageSize;
	do 
	{
		newImageSize.Width=Math::Min((uint)Math::NextPOT(newImageSize.Width),mMaxImageSize.Width);
		newImageSize.Height=Math::Min((uint)Math::NextPOT(newImageSize.Height),mMaxImageSize.Width);
		mPack.GrowSize(mImageSize);	//not re layout the original rects,maybe do it in the future
		outRect=mPack.Insert(size,SkylineBinPack::LevelChoiceHeuristic::LevelBottomLeft);
		if (outRect!=Rect2U::Zero)
		{
			MemoryData newImageData=MemoryData::Alloc(mImageSize.Area()*BytesPerComponent());
			//2.copy image data to new image

			ImageFactory::CopyImage(newImageData,mPixelType,newImageSize,Rect2U(Point2F::Zero,mImageSize),mImageData, mPixelType,0,false,GraphicsPixelConvertMode::Normal);
			mImageSize=newImageSize;
			mImageData=newImageData;

			//draw new image
			outRect.Size-=1;//should -1 to remove edge
			CopyImage(outRect,imageData,pixelType,pitch,isFlipY,mode);
			return true;
		}

	} while (newImageSize<mMaxImageSize);

	return false;
}