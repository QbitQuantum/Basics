void
TkMacUpdateClipRgn(
    TkWindow *winPtr)
{
    RgnHandle rgn;
    int x, y;
    TkWindow *win2Ptr;

    if (winPtr == NULL) {
	return;
    }
    
    if (winPtr->privatePtr->flags & TK_CLIP_INVALID) {
	rgn = winPtr->privatePtr->aboveClipRgn;
	if (tmpRgn == NULL) {
	    tmpRgn = NewRgn();
	}
	
	/* 
	 * Start with a region defined by the window bounds.  
	 */

        x = winPtr->privatePtr->xOff;
        y = winPtr->privatePtr->yOff;
        SetRectRgn(rgn, (short) x, (short) y,
	    (short) (winPtr->changes.width  + x), 
	    (short) (winPtr->changes.height + y));
	    
	/* 
	 * Clip away the area of any windows that may obscure this
	 * window.  
	 * For a non-toplevel window, first, clip to the parents visable
	 * clip region.
	 * Second, clip away any siblings that are higher in the
	 * stacking order.
	 * For an embedded toplevel, just clip to the container's visible
	 * clip region.  Remember, we only allow one contained window 
	 * in a frame, and don't support any other widgets in the frame either.
	 * This is not currently enforced, however.
	 */
	
	if (!Tk_IsTopLevel(winPtr)) { 
	    TkMacUpdateClipRgn(winPtr->parentPtr);
	    SectRgn(rgn, 
		    winPtr->parentPtr->privatePtr->aboveClipRgn, rgn);
				
	    win2Ptr = winPtr->nextPtr;
	    while (win2Ptr != NULL) {
		if (Tk_IsTopLevel(win2Ptr) || !Tk_IsMapped(win2Ptr)) {
		    win2Ptr = win2Ptr->nextPtr;
		    continue;
		}
		x = win2Ptr->privatePtr->xOff;
		y = win2Ptr->privatePtr->yOff;
		SetRectRgn(tmpRgn, (short) x, (short) y,
			(short) (win2Ptr->changes.width  + x), 
			(short) (win2Ptr->changes.height + y));
		DiffRgn(rgn, tmpRgn, rgn);
							  
		win2Ptr = win2Ptr->nextPtr;
	    }
	} else if (Tk_IsEmbedded(winPtr)) {
            TkWindow *contWinPtr;
        
	    contWinPtr = TkpGetOtherWindow(winPtr);
    	     
    	    if (contWinPtr != NULL) {
 	        TkMacUpdateClipRgn(contWinPtr);
	        SectRgn(rgn, 
		        contWinPtr->privatePtr->aboveClipRgn, rgn);
   	    } else if (gMacEmbedHandler != NULL) {
   	        gMacEmbedHandler->getClipProc((Tk_Window) winPtr, tmpRgn);
   	        SectRgn(rgn, tmpRgn, rgn);
   	    }
	    
	    /*
	     * NOTE: Here we should handle out of process embedding.
	     */
		    
	}
	
	/* 
	 * The final clip region is the aboveClip region (or visable
	 * region) minus all the children of this window.
	 * Alternatively, if the window is a container, we must also 
	 * subtract the region of the embedded window.
	 */
	 
	rgn = winPtr->privatePtr->clipRgn;
	CopyRgn(winPtr->privatePtr->aboveClipRgn, rgn);
		
	win2Ptr = winPtr->childList;
	while (win2Ptr != NULL) {
	    if (Tk_IsTopLevel(win2Ptr) || !Tk_IsMapped(win2Ptr)) {
		win2Ptr = win2Ptr->nextPtr;
		continue;
	    }
	    x = win2Ptr->privatePtr->xOff;
	    y = win2Ptr->privatePtr->yOff;
	    SetRectRgn(tmpRgn, (short) x, (short) y,
		    (short) (win2Ptr->changes.width  + x), 
		    (short) (win2Ptr->changes.height + y));
	    DiffRgn(rgn, tmpRgn, rgn);
							  
	    win2Ptr = win2Ptr->nextPtr;
	}
	
	if (Tk_IsContainer(winPtr)) {
	    win2Ptr = TkpGetOtherWindow(winPtr);
	    if (win2Ptr != NULL) {
		if (Tk_IsMapped(win2Ptr)) {
		    x = win2Ptr->privatePtr->xOff;
		    y = win2Ptr->privatePtr->yOff;
		    SetRectRgn(tmpRgn, (short) x, (short) y,
			    (short) (win2Ptr->changes.width  + x), 
			    (short) (win2Ptr->changes.height + y));
		    DiffRgn(rgn, tmpRgn, rgn);
		}
	    } 
	    
	    /*
	     * NOTE: Here we should handle out of process embedding.
	     */
		    
	}
		
	winPtr->privatePtr->flags &= ~TK_CLIP_INVALID;
    }
}