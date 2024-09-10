void CSliderControl::ShrinkRects(TRect aRect,TInt aDir)
	{
	SetExtent(aRect.iTl,aRect.Size());
	CCoeControlArray::TCursor cursor = Components().Begin();
	CCoeControl* ctrl = NULL;
	TInt i=0;
	TRect r;
	while ((ctrl = cursor.Control<CCoeControl>()) != NULL)
	    {
		if (aDir==EDirectionHorizontal)
			{
			TInt w=aRect.Size().iWidth/Components().Count();
			TInt h=aRect.Size().iHeight;
			r=TRect(i*w,0,(i+1)*w,aRect.Height());
			}
		else if (aDir==EDirectionVertical)
			{
			TInt w=aRect.Size().iWidth;
			TInt h=aRect.Size().iHeight/Components().Count();
			r=TRect(0,h*i,aRect.Width(),h*(i+1));
			}		
		ctrl->SetRect(r);
	    cursor.Next();
	    i++;
	    }
	}