void RWindows::Update(const TRegion& aRgn,const TSize& aSize)
	{
	if(aRgn.CheckError())
		UpdateRect(TRect(aSize),aSize);
	else
		for(TInt count=0;count<aRgn.Count();count++)
			UpdateRect(aRgn[count],aSize);
	}