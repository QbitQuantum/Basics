void setWindowTrackingRgn(int windowIndex) {
		
	Rect rgnRect;
	RgnHandle rgn = NewRgn();
	MouseTrackingRegionID id;
	windowDescriptorBlock *windowBlock = windowBlockFromIndex(windowIndex);
	
	if (!windowBlock) 
		return;
		
	if (windowBlock->windowTrackingRef) {
		GetWindowBounds(windowBlock->handle, kWindowContentRgn, &rgnRect);	
		SetRectRgn( rgn, rgnRect.left, rgnRect.top, rgnRect.right, rgnRect.bottom );
		ChangeMouseTrackingRegion(windowBlock->windowTrackingRef,rgn, NULL);
		DisposeRgn( rgn );	
		return;
	}

	GetWindowBounds(windowBlock->handle, kWindowContentRgn, &rgnRect);	
	SetRectRgn( rgn, rgnRect.left, rgnRect.top, rgnRect.right, rgnRect.bottom );
		
	id.signature = 'FAST';
	id.id = windowIndex;
		
	OSStatus err = CreateMouseTrackingRegion(windowBlock->handle, rgn, NULL, kMouseTrackingOptionsGlobalClip,
						id, NULL, NULL, &windowBlock->windowTrackingRef);
	if ( noErr == err ) {
		RetainMouseTrackingRegion( windowBlock->windowTrackingRef);
		err = SetMouseTrackingRegionEnabled( windowBlock->windowTrackingRef, TRUE );
	}
		
	DisposeRgn( rgn );	
}