/**
  Sets the size of the component objects based on the present size of the container window.\n
  Calculates the present size of the container control and also the number of component objects.\n
  Sets the component object dimensions accordingly.\n
*/	
void CCtlContainer::SizeChanged() 
	{
	// set the size of the children
	TRect rect = Rect() ;
	TSize size = rect.Size() ;
	TPoint tl = rect.iTl ;
	TInt childCount = CountComponentControls() ;
	if ( childCount > 0 )
		{
		size.iWidth = size.iWidth/childCount ;
		size.iHeight = size.iHeight/childCount ;
		CCoeControl* child ;
		for ( TInt ii = 0; ii < childCount ; ++ii )
			{
			child = ComponentControl( ii ) ;
			child->SetRect( TRect( tl, size ) ) ;
			tl.iX += size.iWidth ;
			tl.iY += size.iHeight ;
			}
		}
	}