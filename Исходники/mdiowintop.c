static LRESULT CALLBACK MyButtonBarWindowProcedure (HWND pmButtonBarWindow, 
					            UINT pmMessage, 
					            WPARAM pmWParam, 
					            LPARAM pmLParam)
{
    BOOL		myIsTextWindow;
    HDC			myDeviceContext;
    PAINTSTRUCT		myPaintStruct;
    RECT		myWindowRect;
    
    switch (pmMessage)
    {
    	case WM_CREATE:
	    myIsTextWindow = (BOOL) 
	    			(((LPCREATESTRUCT) pmLParam) -> lpCreateParams);
    	    return MyCreateButtonBar (pmButtonBarWindow, myIsTextWindow);
    	    
	case WM_DESTROY:
	    MyDispose (pmButtonBarWindow);
	    break;
	    	    
	case WM_SIZE:
	    MyResizeButtonBar (pmButtonBarWindow);
	    return 0;
	    
    	case WM_PAINT:
    	    myDeviceContext = BeginPaint (pmButtonBarWindow, &myPaintStruct);
    	    GetClientRect (pmButtonBarWindow, &myWindowRect);
    	    MoveToEx (myDeviceContext, 0, myWindowRect.bottom - 1, NULL);
    	    LineTo (myDeviceContext, myWindowRect.right, 
    	        myWindowRect.bottom - 1);
    	    EndPaint (pmButtonBarWindow, &myPaintStruct);
    	    return 0;
	    
	case WM_COMMAND:
	    // Pass the command to the parent
	    SetFocus (GetParent (pmButtonBarWindow));
	    if ((pmWParam == MIO_COMMAND_TERMINATE) && MIO_finished)
	    {
		return SendMessage (GetParent (pmButtonBarWindow), WM_COMMAND,
	    			    MIO_COMMAND_CLOSE, pmLParam);
	    }
	    else
	    {
		return SendMessage (GetParent (pmButtonBarWindow), WM_COMMAND,
	    			    pmWParam, pmLParam);
	    }

	case WM_SYSCOLORCHANGE:
	    //
	    // Set the new background colours
	    //
	    
	    // Delete the old background brush
	    if (stBackgroundBrush != NULL)
	    {
	    	DeleteObject (stBackgroundBrush);
	    }
	    
	    // Create the new background brush
	    stBackgroundBrush = CreateSolidBrush (GetSysColor (COLOR_BTNFACE));
	    
	    // Set the window to be redrawn
	    InvalidateRect (pmButtonBarWindow, NULL, TRUE);
	    return 0;
    } // switch

    return DefWindowProc (pmButtonBarWindow, pmMessage, pmWParam, pmLParam);
} // MyButtonBarWindowProcedure