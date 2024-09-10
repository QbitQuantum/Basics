static
bool Config_SetDefault()
{
	if (ConfigOpenSection("Video-General", &g_configVideoGeneral) != M64ERR_SUCCESS) {
		LOG(LOG_ERROR, "Unable to open Video-General configuration section");
		return false;
	}
	if (ConfigOpenSection("Video-GLideN64", &g_configVideoGliden64) != M64ERR_SUCCESS) {
		LOG(LOG_ERROR, "Unable to open GLideN64 configuration section");
		return false;
	}

	config.resetToDefaults();
	// Set default values for "Video-General" section, if they are not set yet. Taken from RiceVideo
	m64p_error res = ConfigSetDefaultBool(g_configVideoGeneral, "Fullscreen", config.video.fullscreen, "Use fullscreen mode if True, or windowed mode if False ");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultInt(g_configVideoGeneral, "ScreenWidth", config.video.windowedWidth, "Width of output window or fullscreen width");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultInt(g_configVideoGeneral, "ScreenHeight", config.video.windowedHeight, "Height of output window or fullscreen height");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGeneral, "VerticalSync", config.video.verticalSync, "If true, activate the SDL_GL_SWAP_CONTROL attribute");
	assert(res == M64ERR_SUCCESS);

	res = ConfigSetDefaultInt(g_configVideoGliden64, "configVersion", CONFIG_VERSION_CURRENT, "Settings version. Don't touch it.");
	assert(res == M64ERR_SUCCESS);

	res = ConfigSetDefaultInt(g_configVideoGliden64, "MultiSampling", config.video.multisampling, "Enable/Disable MultiSampling (0=off, 2,4,8,16=quality)");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultInt(g_configVideoGliden64, "AspectRatio", config.frameBufferEmulation.aspect, "Screen aspect ratio (0=stretch, 1=force 4:3, 2=force 16:9, 3=adjust)");
	assert(res == M64ERR_SUCCESS);

	//#Texture Settings
	res = ConfigSetDefaultBool(g_configVideoGliden64, "bilinearMode", config.texture.bilinearMode, "Bilinear filtering mode (0=N64 3point, 1=standard)");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "MaxAnisotropy", config.texture.maxAnisotropy, "Max level of Anisotropic Filtering, 0 for off");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultInt(g_configVideoGliden64, "CacheSize", config.texture.maxBytes / uMegabyte, "Size of texture cache in megabytes. Good value is VRAM*3/4");
	assert(res == M64ERR_SUCCESS);
	//#Emulation Settings
	res = ConfigSetDefaultBool(g_configVideoGliden64, "EnableFog", config.generalEmulation.enableFog, "Enable fog emulation.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "EnableNoise", config.generalEmulation.enableNoise, "Enable color noise emulation.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "EnableLOD", config.generalEmulation.enableLOD, "Enable LOD emulation.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "EnableHWLighting", config.generalEmulation.enableHWLighting, "Enable hardware per-pixel lighting.");
	assert(res == M64ERR_SUCCESS);
#ifdef ANDROID
	res = ConfigSetDefaultBool(g_configVideoGliden64, "ForcePolygonOffset", config.generalEmulation.forcePolygonOffset, "If true, use polygon offset values specified below");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultFloat(g_configVideoGliden64, "PolygonOffsetFactor", config.generalEmulation.polygonOffsetFactor, "Specifies a scale factor that is used to create a variable depth offset for each polygon");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultFloat(g_configVideoGliden64, "PolygonOffsetUnits", config.generalEmulation.polygonOffsetUnits, "Is multiplied by an implementation-specific value to create a constant depth offset");
	assert(res == M64ERR_SUCCESS);
#endif
	//#Frame Buffer Settings:"
	res = ConfigSetDefaultBool(g_configVideoGliden64, "EnableFBEmulation", config.frameBufferEmulation.enable, "Enable frame and|or depth buffer emulation.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "EnableCopyColorToRDRAM", config.frameBufferEmulation.copyToRDRAM, "Enable color buffer copy to RDRAM.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "EnableCopyDepthToRDRAM", config.frameBufferEmulation.copyDepthToRDRAM, "Enable depth buffer copy to RDRAM.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "EnableCopyColorFromRDRAM", config.frameBufferEmulation.copyFromRDRAM, "Enable color buffer copy from RDRAM.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "EnableDetectCFB", config.frameBufferEmulation.detectCFB, "Detect CPU writes to frame buffer.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "EnableN64DepthCompare", config.frameBufferEmulation.N64DepthCompare, "Enable N64 depth compare instead of OpenGL standard one. Experimental.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "ValidityCheckMethod", config.frameBufferEmulation.validityCheckMethod, "Method to check validity of auxiliary texture frame buffer (0=write fingerprint to the buffer, 1=fill whole buffer in RDRAM with test value)");
	assert(res == M64ERR_SUCCESS);
	//#Texture filter settings
	res = ConfigSetDefaultInt(g_configVideoGliden64, "txFilterMode", config.textureFilter.txFilterMode, "Texture filter (0=none, 1=Smooth filtering 1, 2=Smooth filtering 2, 3=Smooth filtering 3, 4=Smooth filtering 4, 5=Sharp filtering 1, 6=Sharp filtering 2)");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultInt(g_configVideoGliden64, "txEnhancementMode", config.textureFilter.txEnhancementMode, "Texture Enhancement (0=none, 1=store as is, 2=X2, 3=X2SAI, 4=HQ2X, 5=HQ2XS, 6=LQ2X, 7=LQ2XS, 8=HQ4X, 9=2xBRZ, 10=3xBRZ, 11=4xBRZ, 12=5xBRZ), 13=6xBRZ");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "txFilterIgnoreBG", config.textureFilter.txFilterIgnoreBG, "Don't filter background textures.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultInt(g_configVideoGliden64, "txCacheSize", config.textureFilter.txCacheSize/uMegabyte, "Size of filtered textures cache in megabytes.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "txHiresEnable", config.textureFilter.txHiresEnable, "Use high-resolution texture packs if available.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "txHiresFullAlphaChannel", config.textureFilter.txHiresFullAlphaChannel, "Allow to use alpha channel of high-res texture fully.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "txHresAltCRC", config.textureFilter.txHresAltCRC, "Use alternative method of paletted textures CRC calculation.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "txDump", config.textureFilter.txDump, "Enable dump of loaded N64 textures.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "txCacheCompression", config.textureFilter.txCacheCompression, "Zip textures cache.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "txForce16bpp", config.textureFilter.txForce16bpp, "Force use 16bit texture formats for HD textures.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultBool(g_configVideoGliden64, "txSaveCache", config.textureFilter.txSaveCache, "Save texture cache to hard disk.");
	assert(res == M64ERR_SUCCESS);
	// Convert to multibyte
	char txPath[PLUGIN_PATH_SIZE * 2];
	wcstombs(txPath, config.textureFilter.txPath, PLUGIN_PATH_SIZE * 2);
	res = ConfigSetDefaultString(g_configVideoGliden64, "txPath", txPath, "Path to folder with hi-res texture packs.");
	assert(res == M64ERR_SUCCESS);

	res = ConfigSetDefaultString(g_configVideoGliden64, "fontName", config.font.name.c_str(), "File name of True Type Font for text messages.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultInt(g_configVideoGliden64, "fontSize", config.font.size, "Font size.");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultString(g_configVideoGliden64, "fontColor", "B5E61D", "Font color in RGB format.");
	assert(res == M64ERR_SUCCESS);

	//#Bloom filter settings
	res = ConfigSetDefaultInt(g_configVideoGliden64, "EnableBloom", config.bloomFilter.enable, "Enable bloom filter");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultInt(g_configVideoGliden64, "bloomThresholdLevel", config.bloomFilter.thresholdLevel, "Brightness threshold level for bloom. Values [2, 6]");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultInt(g_configVideoGliden64, "bloomBlendMode", config.bloomFilter.blendMode, "Bloom blend mode (0=Strong, 1=Mild, 2=Light)");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultInt(g_configVideoGliden64, "blurAmount", config.bloomFilter.blurAmount, "Blur radius. Values [2, 10]");
	assert(res == M64ERR_SUCCESS);
	res = ConfigSetDefaultInt(g_configVideoGliden64, "blurStrength", config.bloomFilter.blurStrength, "Blur strength. Values [10, 100]");
	assert(res == M64ERR_SUCCESS);

	return ConfigSaveSection("Video-GLideN64") == M64ERR_SUCCESS;
}