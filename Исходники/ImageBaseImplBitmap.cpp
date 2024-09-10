BOOL CImageBaseImplBitmap::TransformColor(const CImageTransformParam* pParam, LONG color, LONG& transformColor)
{
	transformColor = color;

	if (color == -1)
		return TRUE;

	if (pParam->enTransformType != TRANSFORM_TYPE_COLORIZE)
		return FALSE;

	BOOL bSuc = FALSE;

#ifdef GDIPVER
#if GDIPVER >= 0x0110
	static Bitmap bitmap(1, 1, PixelFormat24bppRGB);
	Color clr(GetRValue(color), GetGValue(color), GetBValue(color));
	bitmap.SetPixel(0, 0, clr);
	HueSaturationLightness hsl;
	HueSaturationLightnessParams hslParam;
	int temp = pParam->hue;
	hslParam.hueLevel = (temp - 128) * 360 / 256;
	temp = pParam->sat;
	hslParam.saturationLevel = (temp - 128) * 200 / 256;
	hslParam.lightnessLevel = (INT)((pParam->blend - 0.5) * 200);
	hsl.SetParameters(&hslParam);
	bSuc = (bitmap.ApplyEffect(&hsl, NULL) == Ok);
	if (bSuc) {
		bitmap.GetPixel(0, 0, &clr);
		transformColor = RGB(clr.GetR(), clr.GetG(), clr.GetB());
	}
#endif
#endif

	return bSuc;
}