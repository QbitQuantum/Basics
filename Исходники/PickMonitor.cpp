OSErr SetupPickMonitorPane(ControlRef inPane, DisplayIDType inDefaultMonitor)
{
	GDHandle dev = GetDeviceList();
	OSErr err = noErr;
	
	// make the default monitor the selected device
	if (inDefaultMonitor)
		DMGetGDeviceByDisplayID(inDefaultMonitor, &sSelectedDevice, true);
	else
		sSelectedDevice = GetMainDevice();

	// build the list of monitors
	sNumMonitors = 0;
	while (dev && sNumMonitors < kMaxMonitors)
	{
		if (TestDeviceAttribute(dev, screenDevice) && TestDeviceAttribute(dev, screenActive))
		{
			sMonitors[sNumMonitors].device = dev;
			sMonitors[sNumMonitors].origRect = (**dev).gdRect;
			sMonitors[sNumMonitors].isMain = (dev == GetMainDevice());
			sNumMonitors++;
		}
		dev = GetNextDevice(dev);
	}

	// calculate scaled rects
	if (sNumMonitors)
	{
		Rect origPaneRect, paneRect;
		Rect origGrayRect, grayRect, scaledGrayRect;
		float srcAspect, dstAspect, scale;
		int i;
		
		GetControlBounds(inPane, &origPaneRect);
		paneRect = origPaneRect;
		OffsetRect(&paneRect, -paneRect.left, -paneRect.top);
		
		GetRegionBounds(GetGrayRgn(), &origGrayRect);
		grayRect = origGrayRect;
		OffsetRect(&grayRect, -grayRect.left, -grayRect.top);
		
		srcAspect = (float)grayRect.right / (float)grayRect.bottom;
		dstAspect = (float)paneRect.right / (float)paneRect.bottom;
		
		scaledGrayRect = paneRect;
		
		if (srcAspect < dstAspect)
		{
			scaledGrayRect.right = (float)paneRect.bottom * srcAspect;
			scale = (float)scaledGrayRect.right / grayRect.right;
		}
		else
		{
			scaledGrayRect.bottom = (float)paneRect.right / srcAspect;
			scale = (float)scaledGrayRect.bottom / grayRect.bottom;
		}
		
		for (i = 0; i < sNumMonitors; i++)
		{
			Rect r = sMonitors[i].origRect;
			Rect r2 = r;
			
			// normalize rect and scale
			OffsetRect(&r, -r.left, -r.top);
			r.bottom = (float)r.bottom * scale;
			r.right = (float)r.right * scale;
			
			// offset rect wrt gray region
			OffsetRect(&r, (float)(r2.left - origGrayRect.left) * scale, 
							(float)(r2.top - origGrayRect.top) * scale);

			sMonitors[i].scaledRect = r;
		}
		
		// center scaledGrayRect in the pane
		OffsetRect(&scaledGrayRect, (paneRect.right - scaledGrayRect.right) / 2,
					(paneRect.bottom - scaledGrayRect.bottom) / 2);

		// offset monitors to match
		for (i = 0; i < sNumMonitors; i++)
			OffsetRect(&sMonitors[i].scaledRect, scaledGrayRect.left, scaledGrayRect.top);
	}
	else
		return paramErr;
		
	// setup the procs for the pick monitor user pane
	err = SetupUserPaneProcs(inPane, drawProc, hitTestProc, trackingProc);
	return err;
}