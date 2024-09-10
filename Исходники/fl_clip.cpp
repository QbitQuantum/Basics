// return rectangle surrounding intersection of this rectangle and clip,
int Fl_Device::clip_box(int x, int y, int w, int h, int& X, int& Y, int& W, int& H)
{
    Region r = rstack[rstackptr];
    if (!r) {X = x; Y = y; W = w; H = h; return 0;}
    // Test against the window to get 16-bit values (this is only done if
    // a clip region exists as otherwise it breaks fl_push_no_clip()):
    int ret = 1;
    int dx = x; 
	int dy = y; 
	fl_transform(x,y); 
	dx = x-dx; 
	dy = y-dy;
    if (x < 0) { w += x; x = 0; ret = 2; }
    int t = Fl_Window::current()->w(); 
	if (x+w > t) { w = t-x; ret = 2; }
    if (y < 0) { h += y; y = 0; ret = 2; }
    t = Fl_Window::current()->h(); 
	if (y+h > t) { h = t-y; ret = 2; }
    
	// check for total clip (or for empty rectangle):
    if (w <= 0 || h <= 0) { W = H = 0; return 0; }

#ifndef _WIN32
    switch (XRectInRegion(r, x, y, w, h))
    {
        case 0:                  // completely outside
            W = H = 0;
            return 0;
        case 1:                  // completely inside:
            X = x-dx;
            Y = y-dy;
            W = w; H = h;
            return ret;
        default:                 // partial:
        {
            Region rr = XRectangleRegion(x,y,w,h);
            Region temp = XCreateRegion();
            XIntersectRegion(r, rr, temp);
            XRectangle rect;
            XClipBox(temp, &rect);
            X = rect.x-dx; Y = rect.y-dy; W = rect.width; H = rect.height;
            XDestroyRegion(temp);
            XDestroyRegion(rr);
            return 2;
        }
    }
#else
    // The win32 API makes no distinction between partial and complete
    // intersection, so we have to check for partial intersection ourselves.
    // However, given that the regions may be composite, we have to do
    // some voodoo stuff...
    Region rr = XRectangleRegion(x,y,w,h);
    Region temp = CreateRectRgn(0,0,0,0);
	
    if (CombineRgn(temp, rr, r, RGN_AND) == NULLREGION) {
		// disjoint
        W = H = 0;
        ret = 0;
    }
    else if (EqualRgn(temp, rr)) {
		// complete
        X = x-dx;
        Y = y-dy;
        W = w; H = h;
        // ret = ret
    } else {
		// parital intersection
        RECT rect;
        GetRgnBox(temp, &rect);
        X = rect.left-dx; Y = rect.top-dy;
        W = rect.right - rect.left; H = rect.bottom - rect.top;
        ret = 2;
    }
    DeleteObject(temp);
    DeleteObject(rr);
    return ret;
#endif
}