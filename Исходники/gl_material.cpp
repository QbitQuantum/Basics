const FHardwareTexture *FGLTexture::Bind(int texunit, int clampmode, int translation, FTexture *hirescheck)
{
	int usebright = false;
	bool alphatrans = false;

	if (translation <= 0) translation = -translation;
	else
	{
		alphatrans = (gl.legacyMode && DWORD(translation) == TRANSLATION(TRANSLATION_Standard, 8));
		translation = GLTranslationPalette::GetInternalTranslation(translation);
	}

	bool needmipmap = (clampmode <= CLAMP_XY);

	FHardwareTexture *hwtex = CreateHwTexture();

	if (hwtex)
	{
		// Texture has become invalid
		if ((!tex->bHasCanvas && (!tex->bWarped || gl.legacyMode)) && tex->CheckModified())
		{
			Clean(true);
			hwtex = CreateHwTexture();
		}

		// Bind it to the system.
		if (!hwtex->Bind(texunit, translation, needmipmap))
		{
			
			int w=0, h=0;

			// Create this texture
			unsigned char * buffer = NULL;
			
			if (!tex->bHasCanvas)
			{
				buffer = CreateTexBuffer(translation, w, h, hirescheck, true, alphatrans);
				if (tex->bWarped && gl.legacyMode && w*h <= 256*256)	// do not software-warp larger textures, especially on the old systems that still need this fallback.
				{
					// need to do software warping
					FWarpTexture *wt = static_cast<FWarpTexture*>(tex);
					unsigned char *warpbuffer = new unsigned char[w*h*4];
					WarpBuffer((DWORD*)warpbuffer, (const DWORD*)buffer, w, h, wt->WidthOffsetMultiplier, wt->HeightOffsetMultiplier, r_FrameTime, wt->Speed, tex->bWarped);
					delete[] buffer;
					buffer = warpbuffer;
					wt->GenTime = r_FrameTime;
				}
				tex->ProcessData(buffer, w, h, false);
			}
			if (!hwtex->CreateTexture(buffer, w, h, texunit, needmipmap, translation, "FGLTexture.Bind")) 
			{
				// could not create texture
				delete[] buffer;
				return NULL;
			}
			delete[] buffer;
		}
		if (tex->bHasCanvas) static_cast<FCanvasTexture*>(tex)->NeedUpdate();
		if (translation != lastTranslation) lastSampler = 254;
		if (lastSampler != clampmode)
			lastSampler = GLRenderer->mSamplerManager->Bind(texunit, clampmode, lastSampler);
		lastTranslation = translation;
		return hwtex; 
	}
	return NULL;
}