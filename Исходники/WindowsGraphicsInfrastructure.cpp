std::unique_ptr< WindowsAdapter > CreateWindowsAdapter( const WindowsAdapterCapabilities& capabilities ) noexcept {
	ComPtr< IDXGIFactory1 > factory;
	auto hresult = CreateDXGIFactory1( __uuidof( IDXGIFactory1 ), reinterpret_cast< void** >( &factory ) );
	if ( FAILED( hresult ) ) {
		return nullptr;
	}
	int id = 0;
	auto adapter = CreateAdapter( factory, id );
	while ( adapter != nullptr ) {
		// check capabilities
		if ( adapter->CheckCapabilities( capabilities ) ) {
			return adapter;
		}
		// next adapter
		id += 1;
		adapter = CreateAdapter( factory, id );
	}
	return nullptr;
}