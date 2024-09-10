HRESULT myIDirect3DDevice9::Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil)
{
	if (GetAsyncKeyState(VK_F4))
	{
		OutputDebugString(va("clear called from %08x\n", (DWORD)_ReturnAddress()));
	}

    return(m_pIDirect3DDevice9->Clear(Count,pRects,Flags,Color,Z,Stencil));
}