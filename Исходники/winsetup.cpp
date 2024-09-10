String screengrab(String filename)
{
	if(filename=="" || filename == " () ")
	{
		filename.sprintf("%s_%5.5d_.png",(const char*)screengrabprefix,screengrabcount);		
		screengrabcount++;
	}
	if(!IsOneOf('.',filename)) 
		filename << ".png";
	HRESULT hr;
	// get display dimensions
	// this will be the dimensions of the front buffer
	D3DDISPLAYMODE mode;
	if (FAILED(hr=g_pd3dDevice->GetDisplayMode(0,&mode)))
	{
		return "fail getdisplaymode";
	}
	// create the image surface to store the front buffer image
	// note that call to GetFrontBuffer will always convert format to A8R8G8B8
	static LPDIRECT3DSURFACE9 surf=NULL;
	if (!surf && FAILED(hr=g_pd3dDevice->CreateOffscreenPlainSurface(mode.Width,mode.Height,
		D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&surf,NULL)))
	{
		return "fail createimagesurface";
	}
 	// Next, this surface is passed to the GetFrontBuffer() method of the device, which will copy the entire screen into our image buffer:
	// read the front buffer into the image surface
	if (FAILED(hr=g_pd3dDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&surf))) 
	{
		surf->Release();
		return "fail getfrontbuffer";
	}
	//Finally, we call D3DXSaveSurfaceToFile() to create the BMP file, and release the temporary image surface:
	// write the entire surface to the requested file
	hr=D3DXSaveSurfaceToFile(filename,D3DXIFF_PNG,surf,NULL,NULL);
	// release the image surface
	// surf->Release();
	// return status of save operation to caller
	return (hr==D3D_OK)? filename + " exported!" : "something failed";
}