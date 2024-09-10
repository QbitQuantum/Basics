HRESULT KG3DGraphicsEngine::InitDevice(UINT uAdapter, D3DDEVTYPE DeviceType, HWND hwnd)
{
    HRESULT hr = S_OK;
    DWORD dwBehaviorFlags = 0;//D3DCREATE_MULTITHREADED;
	D3DPRESENT_PARAMETERS PresentParam;
	memcpy(&PresentParam, &m_PresentParam, sizeof(D3DPRESENT_PARAMETERS));
	
	_ASSERTE(g_pd3dDevice == NULL);

    hr = m_pD3D->CreateDevice(uAdapter, 
		DeviceType, 
		hwnd, 
		D3DCREATE_MIXED_VERTEXPROCESSING | dwBehaviorFlags, 
		&PresentParam, 
		&g_pd3dDevice);
    KG_COM_PROCESS_SUCCESS(hr);

	memcpy(&PresentParam, 
		&m_PresentParam, 
		sizeof(D3DPRESENT_PARAMETERS));
    hr = m_pD3D->CreateDevice(uAdapter, 
		DeviceType, 
		hwnd, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING | dwBehaviorFlags, 
		&PresentParam, 
		&g_pd3dDevice);
    KG_COM_PROCESS_SUCCESS(hr);

	memcpy(&PresentParam, 
		&m_PresentParam, 
		sizeof(D3DPRESENT_PARAMETERS));
    hr = m_pD3D->CreateDevice(uAdapter, 
		DeviceType, 
		hwnd, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | dwBehaviorFlags, 
		&PresentParam, 
		&g_pd3dDevice);
    KG_COM_PROCESS_SUCCESS(hr);

    KGLOG_COM_PROCESS_ERROR(hr);
    KGLOG_PROCESS_ERROR(g_pd3dDevice);

Exit1:
	memcpy(&m_PresentParam, &PresentParam, sizeof(D3DPRESENT_PARAMETERS));
	//检查设备能力
	{
		ZeroMemory(&m_EngineCaps, sizeof(m_EngineCaps));
		HRESULT hrTemp = g_pd3dDevice->GetDeviceCaps(&m_EngineCaps.D3DCaps);
		if (SUCCEEDED(hrTemp))
		{
			for (size_t i = 0; i < _countof(m_EngineCaps.IsShadowTypeAvailable); ++i)
			{
				m_EngineCaps.IsShadowTypeAvailable[i] = TRUE;
			}
            m_EngineCaps.IsShadowTypeAvailable[EM_MODEL_SHADOW_TYPE_LOW] = 
                (m_EngineCaps.D3DCaps.StencilCaps & D3DSTENCILCAPS_INCR) && 
                (m_EngineCaps.D3DCaps.StencilCaps & D3DSTENCILCAPS_DECR);
			//其它类型的影子的能力检查还没有写
		}
		else
		{
			KGLogPrintf(KGLOG_WARNING, "无法得到设备信息，可能显示不正常");
		}
	}

Exit0:
    if (hr == D3DERR_DEVICELOST)
        m_bDeviceLost = true;
    else
        KGLOG_COM_CHECK_ERROR(hr);
    return hr;
}