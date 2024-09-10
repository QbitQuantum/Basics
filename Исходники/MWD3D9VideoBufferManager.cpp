VertexBufferPtr D3D9VideoBufferManager::CreateVertexBuffer(
	int size, int stride, USAGE usage, bool cpuAccess, const void * initData)
{
    d_assert (size > 0);

    HRESULT hr;
    DWORD D3DUsage = D3D9Mapping::GetD3DUsage(usage);
    D3DPOOL D3DPool = D3D9Mapping::GetD3DPool(usage);
    IDirect3DVertexBuffer9 * pD3DVB;

    hr = mD3D9Device->CreateVertexBuffer(size, D3DUsage, 0, D3DPool, &pD3DVB, NULL);

    if (FAILED(hr))
    {
        EXCEPTION("D3D Error: CreateVertexBuffer failed, desc: " + D3D9Mapping::GetD3DErrorDescription(hr));
    }

    D3D9VertexBuffer * pVB = new D3D9VertexBuffer(mD3D9Device);

    pVB->mD3D9VertexBuffer = pD3DVB;
    pVB->mSize = size;
	pVB->mStride = stride;
    pVB->mUsage = usage;

    mVertexBuffers.PushBack(pVB);

	if (initData != NULL)
	{
		void * data = pVB->Lock(0, 0, LOCK_DISCARD);
		Memcpy(data, initData, size);
		pVB->Unlock();
	}
	
    return VertexBufferPtr(pVB);
}