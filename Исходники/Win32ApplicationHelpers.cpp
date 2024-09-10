	HINSTANCE GetInstance( void* addressOfItemInModule ) {
		HINSTANCE	instance( nullptr );

		if( !addressOfItemInModule ) {
			addressOfItemInModule = reinterpret_cast<void*>( &GetInstance );
		}

		GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, static_cast<LPWSTR>(addressOfItemInModule), &instance );

		return instance;
	}