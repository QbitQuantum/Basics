bool CCylinderBoundingWindow::Update(SBoundingShape* shape)
{
	f32 height, radius;
	int err;
	char text[256];
	GetWindowTextA(mHeightTextField, text, 256);
	err = sscanf_s(text, "%f", &height);
	if (err < 1 || err == EOF)
	{
		MessageBoxA(mParentHwnd, "cannot convert height value", "Error", NULL);
		return false;
	}

	GetWindowTextA(mRadiusTextField, text, 256);
	err = sscanf_s(text, "%f", &radius);
	if (err < 1 || err == EOF)
	{
		MessageBoxA(mParentHwnd, "cannot convert radius value", "Error", NULL);
		return false;
	}

	SCylinderBounding* cylinder = (SCylinderBounding*)shape;
	cylinder->Height = height;
	cylinder->Radius = radius;

	return true;
}