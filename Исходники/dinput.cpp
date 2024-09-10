// Public functions
bool DInput::Initialise( HINSTANCE h_instance, HWND hwnd ) {
	ZeroMemory( keyboard_keys_, sizeof( keyboard_keys_ ) );
	ZeroMemory( prev_keyboard_keys_, sizeof( prev_keyboard_keys_ ) );

	HRESULT result = DirectInput8Create( h_instance, direct_input_VERSION, IID_IDirectInput8, ( void** )&direct_input_, 0 );

	if( FAILED( result ) ) {
		return false;
	}

	result = direct_input_->CreateDevice( GUID_SysKeyboard, &keyboard_device_, 0 );

	if( FAILED( result ) ) {
		return false;
	}

	result = keyboard_device_->SetDataFormat( &c_dfDIKeyboard );

	if( FAILED( result ) ) {
		return false;
	}

	result = keyboard_device_->SetCooperativeLevel( hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	if( FAILED( result ) ) {
		return false;
	}

	result = keyboard_device_->Acquire();

	if( FAILED( result ) ) {
		return false;
	}

	mousePosX_ = mousePosY_ = mouseWheel_ = 0;

	result = direct_input_->CreateDevice( GUID_SysMouse, &mouse_device_, 0 );

	if( FAILED( result ) ) {
		return false;
	}

	result = mouse_device_->SetDataFormat( &c_dfDIMouse );

	if( FAILED( result ) ) {
		return false;
	}

	result = mouse_device_->SetCooperativeLevel( hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	if( FAILED( result ) ) {
		return false;
	}

	result = mouse_device_->Acquire();

	if( FAILED( result ) ) {
		return false;
	}

	return true;
}