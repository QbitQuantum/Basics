int fbx_write(fbx_struct *fb, int srcX_, int srcY_, int dstX_, int dstY_,
	int width_, int height_)
{
	int srcX, srcY, dstX, dstY, width, height;
	#ifdef _WIN32
	BITMAPINFO bmi;  fbx_gc gc;
	#endif

	if(!fb) _throw("Invalid argument");

	srcX=srcX_>=0? srcX_:0;  srcY=srcY_>=0? srcY_:0;
	dstX=dstX_>=0? dstX_:0;  dstY=dstY_>=0? dstY_:0;
	width=width_>0? width_:fb->width;
	height=height_>0? height_:fb->height;

	if(width>fb->width) width=fb->width;
	if(height>fb->height) height=fb->height;
	if(srcX+width>fb->width) width=fb->width-srcX;
	if(srcY+height>fb->height) height=fb->height-srcY;

	#ifdef _WIN32

	if(!fb->wh || fb->width<=0 || fb->height<=0 || !fb->bits)
		_throw("Not initialized");
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize=sizeof(bmi);
	bmi.bmiHeader.biWidth=fb->width;
	bmi.bmiHeader.biHeight=-fb->height;
	bmi.bmiHeader.biPlanes=1;
	bmi.bmiHeader.biBitCount=fbx_ps[fb->format]*8;
	bmi.bmiHeader.biCompression=BI_RGB;
	_w32(gc=GetDC(fb->wh));
	_w32(SetDIBitsToDevice(gc, dstX, dstY, width, height, srcX, 0, 0, height,
		&fb->bits[srcY*fb->pitch], &bmi, DIB_RGB_COLORS));
	_w32(ReleaseDC(fb->wh, gc));
	return 0;

	#else

	if(!fb->pm || !fb->shm)
		if(fbx_awrite(fb, srcX, srcY, dstX, dstY, width, height)==-1) return -1;
	if(fb->pm)
	{
		XCopyArea(fb->wh.dpy, fb->pm, fb->wh.d, fb->xgc, srcX, srcY, width,
			height, dstX, dstY);
	}
	XFlush(fb->wh.dpy);
	XSync(fb->wh.dpy, False);
	return 0;

	#endif

	finally:
	return -1;
}