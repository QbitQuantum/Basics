graphics::Effect *graphics::DX10Render::createEffect(core::Allocator &allocator, core::Blob &blob)
{
	// TODO: Investigate effectpools and their opengl equivalent.
	graphics::DX10Effect *effect = NULL;
	ID3D10Effect *d3dEffect;
	// TODO: Investigate if theres anyway to supply a custom allocator to D3D.
	HRESULT result = D3D10CreateEffectFromMemory(const_cast<void*>(blob.getPtr()), static_cast<SIZE_T>(blob.getSize()), 0, this->device, NULL, &d3dEffect);
	if(SUCCEEDED(result))
	{

		//effect = new (allocator.allocate(sizeof(graphics::DX10Effect))) graphics::DX10Effect(VortexBase::engine, *d3dEffect);
	}

	return effect;
}