NS_IMETHODIMP nsRenderingContextPh :: GetClipRect( nsRect &aRect, PRBool &aClipValid ) 
{
	PRInt32 x, y, w, h;
	
	if ( !mClipRegion )
		return NS_ERROR_FAILURE;
	
	if( !mClipRegion->IsEmpty() ) {
		mClipRegion->GetBoundingBox( &x, &y, &w, &h );
		aRect.SetRect( x, y, w, h );
		aClipValid = PR_TRUE;
	}
	else {
		aRect.SetRect(0,0,0,0);
		aClipValid = PR_FALSE;
	}
	return NS_OK;
}