static void
SDLGL_CaptureOutput(AG_DriverSDLGL *sgl)
{
	char path[AG_PATHNAME_MAX];
	AG_DriverSw *dsw = (AG_DriverSw *)sgl;
	AG_Surface *s;

	Snprintf(path, sizeof(path), sgl->outPath, sgl->outFrame);
	glReadPixels(0, 0, dsw->w, dsw->h, GL_RGBA, GL_UNSIGNED_BYTE,
	    sgl->outBuf);

	if (AG_PackedPixelFlip(sgl->outBuf, dsw->h, dsw->w*4) == -1) {
		goto fail_disable;
	}
	s = AG_SurfaceFromPixelsRGBA(sgl->outBuf,
	    dsw->w, dsw->h, 32,
	    0x000000ff, 0x0000ff00, 0x00ff0000, 0);
	if (s == NULL)
		goto fail;

	switch (sgl->outMode) {
	case AG_SDLGL_OUT_JPEG:
		if (AG_SurfaceExportJPEG(s, path) == -1) {
			goto fail;
		}
		break;
	case AG_SDLGL_OUT_PNG:
		if (AG_SurfaceExportPNG(s, path) == -1) {
			goto fail;
		}
		break;
	}

	if (++sgl->outFrame == sgl->outLast) {
		Verbose("Reached last frame; terminating\n");
		AG_Terminate(0);
	}
	AG_SurfaceFree(s);
	return;
fail:
	AG_SurfaceFree(s);
fail_disable:
	AG_Verbose("%s; disabling capture\n", AG_GetError());
	sgl->outMode = AG_SDLGL_OUT_NONE;
}