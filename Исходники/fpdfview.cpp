DLLEXPORT void STDCALL FPDFBitmap_FillRect(FPDF_BITMAP bitmap, int left, int top, int width, int height, FPDF_DWORD color)
{
	if (bitmap == NULL) return;
#ifdef _SKIA_SUPPORT_
	CFX_SkiaDevice device;
#else
	CFX_FxgeDevice device;
#endif
	device.Attach((CFX_DIBitmap*)bitmap);
	if (!((CFX_DIBitmap*)bitmap)->HasAlpha()) color |= 0xFF000000;
	FX_RECT rect(left, top, left+width, top+height);
	device.FillRect(&rect, color);
}