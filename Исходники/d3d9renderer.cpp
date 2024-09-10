/*************************************************************************
	method to do work of constructor
*************************************************************************/
void DirectX9Renderer::constructor_impl(LPDIRECT3DDEVICE9 device, const Size& display_size)
{
	d_device        = device;
	d_queueing      = true;
	d_currTexture   = 0;
	d_buffer        = 0;
	d_bufferPos     = 0;

	// initialise renderer display area
	d_display_area.d_left	= 0;
	d_display_area.d_top	= 0;
	d_display_area.setSize(display_size);

	// Create a vertex buffer
	if (FAILED(d_device->CreateVertexBuffer(
		(VERTEXBUFFER_CAPACITY * sizeof(QuadVertex)), 
		D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY, 
		VERTEX_FVF, 
		D3DPOOL_DEFAULT, 
		&d_buffer,
		0)))
	{
		// Ideally, this would have been a RendererException, but we can't use that until the System object is created
		// and that requires a Renderer passed to the constructor, so we throw this instead.
		throw std::exception("Creation of VertexBuffer for Renderer object failed");
	}

	// get the maximum available texture size.
	D3DCAPS9	devCaps;
	if (FAILED(device->GetDeviceCaps(&devCaps)))
	{
		// release vertex buffer
		d_buffer->Release();
		throw std::exception("Unable to retrieve device capabilities from Direct3DDevice9.");
	}

	// set max texture size the the smaller of max width and max height.
	d_maxTextureSize = ceguimin(devCaps.MaxTextureWidth, devCaps.MaxTextureHeight);

	d_device->AddRef();

    // set ID string
    d_identifierString = "CEGUI::DirectX81Renderer - Official Direct3D 9 based renderer module for CEGUI";
}