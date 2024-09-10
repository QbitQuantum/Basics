jint naSetup(JNIEnv *pEnv, jobject pObj, int pWidth, int pHeight) {
	width = pWidth;
	height = pHeight;
	//create a bitmap as the buffer for frameRGBA
	bitmap = createBitmap(pEnv, pWidth, pHeight);
	if (AndroidBitmap_lockPixels(pEnv, bitmap, &buffer) < 0)
		return -1;
	//get the scaling context
	sws_ctx = sws_getContext (
	        codecCtx->width,
	        codecCtx->height,
	        codecCtx->pix_fmt,
	        pWidth,
	        pHeight,
	        AV_PIX_FMT_RGBA,
	        SWS_BILINEAR,
	        NULL,
	        NULL,
	        NULL
	);
	// Assign appropriate parts of bitmap to image planes in pFrameRGBA
	// Note that pFrameRGBA is an AVFrame, but AVFrame is a superset
	// of AVPicture
	avpicture_fill((AVPicture *)frameRGBA, buffer, AV_PIX_FMT_RGBA,
			pWidth, pHeight);
	return 0;
}