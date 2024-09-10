BOOL InitDDraw()
{
	DDSURFACEDESC ddsd;
	HRESULT ddrval;

	DirectDrawCreate(NULL, &lpDD, NULL);//产生一个DDRAW对象。
	/*第一个参数是要创建的驱动类型，设为NULL，表示使用当前的显示驱动
	第三个参数用于今后与COM对象兼容，目前都设为NULL*/

	lpDD->SetCooperativeLevel (hWnd, DDSCL_NORMAL);//设置协作级别

	ZeroMemory( &ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	/*主页面的大小和像素格式都是由当前的显示模式决定的，
	所以不能指定，否则发生错误*/
	ddsd.ddsCaps .dwCaps = DDSCAPS_PRIMARYSURFACE;
	ddrval = lpDD->CreateSurface (&ddsd, &lpDDSPrimary, NULL);
	/*第三个参数也是用于与COM对象兼容，目前只能设为NULL*/
	if(ddrval != DD_OK)
	{
		return FALSE;
	}
	
	ZeroMemory( &ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS| DDSD_HEIGHT| DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwHeight = 600;
	ddsd.dwWidth = 800;
	/*页面的大小可以和实际图片大小不一样，但会产生失真*/

	RectTemp.left = 0;
	RectTemp.top = 0;
	RectTemp.right = ddsd.dwWidth;
	RectTemp.bottom = ddsd.dwHeight;
	

	lpDD->CreateSurface (&ddsd, &lpDDSTemp, NULL);
	if(ddrval != DD_OK)
	{
		return FALSE;
	}

	DDReLoadBitmap( lpDDSTemp, "gameover.bmp");

	return TRUE;

}