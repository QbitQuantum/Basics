PVideoFrame __stdcall AutoTraceFilter::GetFrame(int n, IScriptEnvironment* env) {
	// Grab the child frame
	PVideoFrame childFrame = child->GetFrame(n, env);
	// Create the bitmap - AutoTrace always wants a 24-bpp bitmap for some dumb reason
	at_bitmap_type *bitmap;
	bitmap = at_bitmap_new(srcWidth, srcHeight, 3);
	size_t bitmap_size = srcWidth * srcHeight * 3;
	// Pull the bitmap data
	// We can just blt lines
	const BYTE* srcBitmap = childFrame->GetReadPtr();
	int pitch = childFrame->GetPitch();
	int rowSize = childFrame->GetRowSize();
	for (int y = 0; y < srcHeight; y++) {
		// Note that R and B are swapped in this. It doesn't really matter.
		memcpy_s(bitmap->bitmap + ((srcHeight - y - 1) * rowSize), bitmap_size, srcBitmap + (y * pitch), rowSize);
	}
	// This does the actual tracing:
	at_splines_type* splines = at_splines_new(bitmap, fitting_opts, exception_handler, NULL);
	// Now create the new frame. First, blank out the old frame
	graphics->Clear(*backgroundColor);
	at_real tx = ((at_real)destWidth) / ((at_real)srcWidth);
	at_real ty = ((at_real)destHeight) / ((at_real)srcHeight);
	for (unsigned int i = 0; i < splines->length; i++) {
		at_spline_list_type spline_list = splines->data[i];
		Gdiplus::GraphicsPath path;
		for (unsigned int j = 0; j < spline_list.length; j++) {
			at_spline_type* spline = &(spline_list.data[j]);
			if (spline->degree == AT_LINEARTYPE) {
				path.AddLine((Gdiplus::REAL)(spline->v[0].x * tx), (Gdiplus::REAL)(spline->v[0].y * ty),
					(Gdiplus::REAL)(spline->v[3].x * tx), (Gdiplus::REAL)(spline->v[3].y * ty));
			} else {
				path.AddBezier(
					(Gdiplus::REAL)(spline->v[0].x * tx), (Gdiplus::REAL)(spline->v[0].y * ty),
					(Gdiplus::REAL)(spline->v[1].x * tx), (Gdiplus::REAL)(spline->v[1].y * ty),
					(Gdiplus::REAL)(spline->v[2].x * tx), (Gdiplus::REAL)(spline->v[2].y * ty),
					(Gdiplus::REAL)(spline->v[3].x * tx), (Gdiplus::REAL)(spline->v[3].y * ty));
			}
		}
		path.CloseFigure();
		// Red and blue are swapped here, so swap them back.
		Gdiplus::Color color(spline_list.color.b, spline_list.color.g, spline_list.color.r);
		Gdiplus::SolidBrush brush(color);
		graphics->FillPath(&brush, &path);
	}
	at_splines_free(splines);
	at_bitmap_free(bitmap);
	// Now we need to create our result frame
	PVideoFrame outputFrame = env->NewVideoFrame(vi);
	BYTE* outputData = outputFrame->GetWritePtr();
	env->BitBlt(outputData, outputFrame->GetPitch(), renderedFrameData, renderedFramePitch, destWidth*4, destHeight);
	return outputFrame;
}