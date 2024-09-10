/*
RectanglesDrawEventHandler : Handles the draw events for the "Rectangles" window.

Parameter DescriptionsinHandler : A reference to the current handler call chain. This is passed to your handler so that you can call CallNextEventHandler if you need to.
inEvent : The event that triggered this call.
inUserData : The application-specific data you passed in to InstallEventHandler.
*/
OSStatus RectanglesDrawEventHandler (EventHandlerCallRef inHandler, EventRef inEvent, void* inUserData) {
	OSStatus status = eventNotHandledErr;
	CGContextRef context;
    CGRect r;
	
	//CallNextEventHandler in order to make sure the default handling of the inEvent 
	// (drawing the white background) happens
	status = CallNextEventHandler( inHandler, inEvent );
	require_noerr(status, CantCallNextEventHandler);
	
	// Get the CGContextRef
	status = GetEventParameter (inEvent, 
								kEventParamCGContextRef, 
								typeCGContextRef, 
								NULL, 
								sizeof (CGContextRef),
								NULL,
								&context);
	require_noerr(status, CantGetEventParameter);
	
	/* Set the stroke color to black. */
    CGContextSetRGBStrokeColor(context, 0, 0, 0, 1);
	
    r.size.height = 210;
    r.origin.x = 20;
    r.origin.y = 20;
    r.size.width = 210;
    frameRect(context, r);
	
    r.size.height = 145;
    r.origin.x = 75;
    r.origin.y = 55;
    r.size.width = 100;
    frameRect(context, r);

    /* Set the fill color to green. */
    CGContextSetRGBFillColor(context, 0, 1, 0, 1);
	
    r.size.height = 210;
    r.origin.x = 270;
    r.origin.y = 20;
    r.size.width = 210;
    paintRect(context, r);
	
    /* Set the fill color to yellow. */
    CGContextSetRGBFillColor(context, 1, 1, 0, 1);
	
    r.size.height = 145;
    r.origin.x = 325;
    r.origin.y = 55;
    r.size.width = 100;
    paintRect(context, r);
	
CantCallNextEventHandler:
CantGetEventParameter:
		
		return status;
}