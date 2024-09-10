// *************************************************************
//		CreateMatrix()
// *************************************************************
Gdiplus::ColorMatrix ImageHelper::CreateMatrix(float contrast, float brightness, float saturation, float hue,
	float colorizeIntensity, OLE_COLOR _colorizeColor, bool setToGrey,
	double transparencyPercent)
{
	QColorMatrix matrix;
	matrix.m[3][3] = static_cast<float>(transparencyPercent);

	if (contrast != 1.0f) {
		matrix.ScaleColors(contrast, MatrixOrderPrepend);
	}

	if (brightness != 0.0f) {
		matrix.TranslateColors(brightness, MatrixOrderAppend);
	}

	if (saturation != 1.0f) {
		matrix.SetSaturation(saturation, MatrixOrderAppend);
	}

	if (hue != 0.0f)  {
		matrix.RotateHue(hue);
	}

	if (colorizeIntensity != 0.0) {
		matrix.Colorize(_colorizeColor, colorizeIntensity, MatrixOrderAppend);
	}

	if (setToGrey) {
		matrix.SetGreyscale(MatrixOrderAppend);
	}

	return matrix;
}