nf_system_info_t nf_system_info()
{
	float ppi_x = 0.0f, ppi_y = 0.0f;

	// instead of doing full initialization, let's just create a d2d1 factory
	if(!ctx.reference_counter)
	{
		HRESULT hr = 0;
		if(FAILED(hr = D2D1CreateFactory(
						D2D1_FACTORY_TYPE_SINGLE_THREADED,
						__uuidof(ID2D1Factory1),
						NULL,
						(void**)&ctx.d2d_factory)))
		{
			NF_ERROR("can't create d2d1 factory\n");
			ctx.d2d_factory = NULL;
		}
	}
	ctx.d2d_factory->GetDesktopDpi(&ppi_x, &ppi_y);
	if(!ctx.reference_counter && ctx.d2d_factory)
	{
		ctx.d2d_factory->Release();
		ctx.d2d_factory = NULL;
	}

	nf_system_info_t ret;
	ret.bitmap = NF_BITMAP_B8G8R8A8_UNORM_PMA;
	ret.max_width = NF_MAX_WIDTH;
	ret.max_height = NF_MAX_HEIGHT;
	ret.ppi_x = ppi_x;
	ret.ppi_y = ppi_y;
	return ret;
}