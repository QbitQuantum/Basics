//----------------------------------------------------------------------------
//! @brief	  	VMR9フィルタをフィルタグラフへ追加する
//! @param 		pVMR9 : VMR9フィルタ
//----------------------------------------------------------------------------
void tTVPDSMixerVideoOverlay::AddVMR9Filer( CComPtr<IBaseFilter> &pVMR9 )
{
	HRESULT			hr = S_OK;
	if( FAILED(hr = pVMR9.CoCreateInstance(CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC) ) )
		ThrowDShowException(L"Failed to create VMR9 Filter. This component requires DirectX9.", hr);

	if( FAILED(hr = GraphBuilder()->AddFilter( pVMR9, L"Video Mixing Render 9")) )
		ThrowDShowException(L"Failed to call GraphBuilder()->AddFilter( pVMR9, L\"Video Mixing Render 9\").", hr);

	{
		CComPtr<IVMRFilterConfig9>	pConfig;
		if( FAILED(hr = pVMR9.QueryInterface(&pConfig) ) )
			ThrowDShowException(L"Failed to query IVMRFilterConfig9.", hr);

		if( FAILED(hr = pConfig->SetNumberOfStreams(1) ) )
			ThrowDShowException(L"Failed to call IVMRFilterConfig9::SetNumberOfStreams(1).", hr);
		if( FAILED(hr = pConfig->SetRenderingMode(VMR9Mode_Renderless ) ) )
			ThrowDShowException(L"Failed to call IVMRFilterConfig9::SetRenderingMode(VMR9Mode_Renderless).", hr);

		// Negotiate Renderless mode
		if( FAILED(hr = pVMR9.QueryInterface( &m_VMR9SurfAllocNotify ) ) )
			ThrowDShowException(L"Failed to query IVMRSurfaceAllocatorNotify9.", hr);

		CComPtr<IVMRSurfaceAllocator9>	alloc;
		if( FAILED(hr = AllocatorPresenter()->QueryInterface( IID_IVMRSurfaceAllocator9, reinterpret_cast<void**>(&alloc.p) ) ) )
			ThrowDShowException(L"Failed to query IVMRSurfaceAllocator9.", hr);
		if( FAILED(hr = AllocatorNotify()->AdviseSurfaceAllocator( reinterpret_cast<DWORD_PTR>(this), alloc ) ) )
			ThrowDShowException(L"Failed to call IVMRSurfaceAllocatorNotify9::AdviseSurfaceAllocator().", hr);
		if( FAILED(hr = Allocator()->AdviseNotify( AllocatorNotify() ) ) )
			ThrowDShowException(L"Failed to call IVMRSurfaceAllocator9::AdviseNotify().", hr);

		// query monitor config
//		if( FAILED(hr = pVMR9.QueryInterface(&m_VMR9MonitorConfig)) )
//			ThrowDShowException(L"Failed to query IVMRMonitorConfig9.", hr);
	}
}