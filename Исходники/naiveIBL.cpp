void CChildView::OnSrtpEnvironmentbrdf()
{
	CWaitCursor wait;//在函数执行过程中使鼠标图标变成等待图标
	int newX = 256, newY = 256;
	CImage tmpimg;
	tmpimg.Create(newX, newY, 24, 0);
	float NoV, roughness;
	float* res = new float[2];
	for (int x = 0; x < newX; x++){
		NoV = x*1.0f / newX;
		for (int y = 0; y < newY; y++){
			roughness = y*2.0f / newY;
			IntegrateBRDF(res, roughness, NoV);
			tmpimg.SetPixelRGB(x, y, (byte)(res[0] * 255), (byte)(res[1] * 255), 0);
		}
	}
	delete[] res;
	imgOriginal.Destroy();
	imgOriginal.Create(newX, newY, tmpimg.GetBPP());//根据新的大小建立CImage，GetBPP是获取其大小
	for (int x = 0; x < newX; x++){
		for (int y = 0; y < newY; y++){
			imgOriginal.SetPixel(x, y, tmpimg.GetPixel(x, y));
		}
	}
	tmpimg.Destroy();
	//刷新显示图像
	Invalidate();
	UpdateWindow();
}